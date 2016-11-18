#include "GameScene.h"
#include "GameUI.h"

bool GameScene::IsStarted = false;

GameScene::GameScene() : Scene("GAME")
{
	m_player = new Player();
	m_gameObjects.push_back(m_player);

	m_enemy = new Enemy();
	m_gameObjects.push_back(m_enemy);

	ui = new GameUI();
}

void GameScene::Update(float deltaTime)
{
	if (IsStarted)
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}
	}

	ui->Update(deltaTime);

	// Send and Receive messages
	string s = net.Receive();
	net.Send(m_player->Serialize());

	if (s != "")
	{
		//cout << "Received message: " << s << endl;
		m_enemy->Deserialize(s);
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		net.Send("This is a test message");
	}
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
	net.Init();
}
