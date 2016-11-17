#include "GameScene.h"
#include "Player.h"
#include "GameUI.h"

bool GameScene::IsStarted = false;

GameScene::GameScene() : Scene("GAME")
{
	m_gameObjects.push_back(new Player);
	ui = new GameUI(Vector2f(0, 0));
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

	if (s != "")
	{
		cout << "Received message: " << s << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		net.Send();
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
	// TODO: Add in stuff that has to start when the gamescene is entered
}
