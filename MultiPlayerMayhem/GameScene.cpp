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

			if (values[0] == "ENEMY")
			{
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
