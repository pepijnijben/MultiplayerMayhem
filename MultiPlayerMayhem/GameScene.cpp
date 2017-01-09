#include "GameScene.h"
#include "GameUI.h"

bool GameScene::IsStarted = false;

GameScene::GameScene() : Scene("GAME")
{
	net = Net::GetInstance();

	m_player = new Player();
	m_gameObjects.push_back(m_player);

	ui = new GameUI();
}

void GameScene::Update(float deltaTime)
{
	// Send and Receive messages
	vector<string> messages = net->Receive();
	net->Send(m_player->Serialize());

	for (auto & s : messages)
	{
		if (s != "")
		{
			vector<string> values = DeserializeMessage(s);

			if (values[0] == "PLAYER")
			{
				if (m_player->Name == values[1])
				{
					m_player->Deserialize(values);
				}

				for (auto & enemy : m_enemys)
				{
					if (enemy->Name == values[1])
					{
						enemy->Deserialize(values);
						break;
					}
				}
			}
			else if (values[0] == "GAME")
			{
				if (values[1] == "STARTED")
				{
					net->Send("GAME;STARTED;");
					IsStarted = true;
				}
			}
		}
	}

	if (IsStarted)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}

		// Authoritive host part
		if (m_isHost)
		{
			ostringstream ss;
			// Checkcollisions
			for (auto& e1 : m_enemys)
			{
				// Check if local player collided with e1
				if (m_player->IsAlive() && e1->CollidedWith(m_player->GetPosition()))
				{
					// localplayer to dead and send everyone the message he is dead
					cout << m_player->Name << " Collided with " << e1->Name << endl;
					ss << "PLAYER;" << m_player->Name << ";DEAD;";
					net->Send(ss.str());
					m_player->IsAlive(false);
				}
				if (e1->IsAlive() && m_player->CollidedWith(e1->GetPosition()))
				{
					// e1 is dead and send everyone the message he is dead
					cout << e1->Name << " Collided with " << m_player->Name << endl;
					ss << "PLAYER;" << e1->Name << ";DEAD;";
					net->Send(ss.str());
					e1->IsAlive(false);
				}

				// Check against all other enemies
				for (auto& e2 : m_enemys)
				{
					if (e1->IsAlive() && e1->Name != e2->Name)
					{
						// if e1 collided with e2 he is dead
						if (e2->CollidedWith(e1->GetPosition()))
						{
							// Set e1 to dead and send e1 message that he is dead
							cout << e1->Name << " Collided with " << e2->Name << endl;
							ss << "PLAYER;" << e1->Name << ";DEAD;";
							net->Send(ss.str());
							e1->IsAlive(false);
							break;
						}
					}
				}
			} // End checkcollisions
		} // End Authoritive host
	} // End IsStarted

	ui->Update(deltaTime);
}

void GameScene::Render(RenderWindow & r)
{
	for (auto& obj : m_gameObjects)
	{
		obj->Render(r);
	}

	ui->Render(r);
}

void GameScene::Destroy()
{
	// Takes care of destroying all the m_gameObjects
	Scene::Destroy();
}

void GameScene::Enter()
{
	m_isHost = APIHandler::GetInstance()->IsHost();
	m_player->ResetPlayer();
	m_player->Name = APIHandler::GetInstance()->GetName();
	vector<NetPlayer> enemys = APIHandler::GetInstance()->getRoomOtherPlayers();
	net->SetRemotePlayers(enemys);

	for (auto & enemy : enemys)
	{
		Enemy * m_enemy = new Enemy();
		m_enemy->Name = enemy.name;
		m_gameObjects.push_back(m_enemy);
		m_enemys.push_back(m_enemy);
	}

	net->Send("GAME;STARTED;");
}

vector<string> GameScene::DeserializeMessage(string message)
{
	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;

	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	return token;
}
