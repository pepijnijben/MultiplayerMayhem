#include "GameScene.h"
#include "GameUI.h"

bool GameScene::IsStarted = false;

void GameScene::ResetRound()
{
	for (auto & enemy : m_enemys)
	{
		enemy->ResetEnemy();
	}

	m_player->ResetPlayer();
}

GameScene::GameScene() : Scene("GAME")
{
	currentTime = 0.0f;
	net = Net::GetInstance();

	m_player = new Player();
	m_gameObjects.push_back(m_player);

	ui = new GameUI();
}

void GameScene::Update(float deltaTime)
{
	currentTime += deltaTime;

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
				if (values[1] == "STARTED" && !IsStarted)
				{
					net->Send("GAME;STARTED;");
					IsStarted = true;
				}
				else if (values[1] == "RESET")
				{
					ResetRound();
				}
				else if (values[1] == "TIME")
				{
					if (values[2] == m_player->Name)
					{
						currentTime = stof(values[3]);
					}
				} 
				else if (values[1] == "PING")
				{
					if (values[2] == m_player->Name)
					{
						ostringstream ss;
						ss << "GAME;PINGRETURNED;" << m_player->Name << ";" << values[3] << ";";
						net->Send(ss.str());
					}
				}
				else if (m_isHost && values[1] == "PINGRETURNED")
				{
					m_pingmsg[values[2]][stoi(values[3]) + 10] = currentTime;

					if (m_pingmsg[values[2]].size() >= 20)
					{
						float totalSum = 0;
						for (int i = 0; i < 10; i++)
						{
							totalSum += m_pingmsg[values[2]][i + 10] - m_pingmsg[values[2]][i];
						}

						ostringstream ss;
						ss << "GAME;TIME;" << values[2] << ";" << currentTime + (totalSum / 10.0f) << ";";
						net->Send(ss.str());

						m_pingmsg.erase(values[2]);
					}
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

			// Check if player is outside of the bounds
			if (m_player->GetPosition().x > 800 || m_player->GetPosition().x < 0 || m_player->GetPosition().y < 0 || m_player->GetPosition().y > 600)
			{
				ss << "PLAYER;" << m_player->Name << ";DEAD;";
				net->Send(ss.str());
				m_player->IsAlive(false);
			}

			int playersAlive = m_player->IsAlive() ? 1 : 0;
			// Checkcollisions
			for (auto& e1 : m_enemys)
			{
				// Check if local player collided with e1
				if (m_player->IsAlive() && e1->CollidedWith(m_player->GetPosition()))
				{
					ss.str("");
					ss.clear();
					ss << "PLAYER;" << m_player->Name << ";DEAD;";
					net->Send(ss.str());
					m_player->IsAlive(false);
				}
				if (e1->IsAlive() && m_player->CollidedWith(e1->GetPosition()))
				{
					ss.str("");
					ss.clear();
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
							ss.str("");
							ss.clear();
							ss << "PLAYER;" << e1->Name << ";DEAD;";
							net->Send(ss.str());
							e1->IsAlive(false);
							break;
						}
					}
				}

				if (e1->IsAlive())
				{
					// Check if player is outside of the bounds
					if (e1->GetPosition().x > 800 || e1->GetPosition().x < 0 || e1->GetPosition().y < 0 || e1->GetPosition().y > 600)
					{
						ss.str("");
						ss.clear();
						ss << "PLAYER;" << e1->Name << ";DEAD;";
						net->Send(ss.str());
						e1->IsAlive(false);
					}
					else
					{
						playersAlive++;
					}
				}

			} // End checkcollisions

			// Round is over cuz one player won!
			if (playersAlive <= 1)
			{
				ss.str("");
				ss.clear();

				ss << "GAME;RESET;";
				net->Send(ss.str());

				ResetRound();
			}
		} // End Authoritive host
	} // End IsStarted
	else
	{
		if (m_pingmsg.size() <= 0)
		{
			net->Send("GAME;STARTED;");
			IsStarted = true;
		}
	}

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

	if (m_isHost)
	{
		cout << "Im the host" << endl;
		net->Send("GAME;STARTED;");
		for (auto & enemy : enemys)
		{
			Enemy * m_enemy = new Enemy();
			m_enemy->Name = enemy.name;
			m_gameObjects.push_back(m_enemy);
			m_enemys.push_back(m_enemy);

			m_pingmsg[enemy.name] = map<int, float>();
		
			for (int i = 0; i < 10; i++)
			{
				ostringstream ss;
				ss << "GAME;PING;" << enemy.name << ";" << i << ";";
				m_pingmsg[enemy.name][i] = currentTime;
				net->Send(ss.str());
			}
		}
	}

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
