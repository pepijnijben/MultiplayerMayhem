#include "LobbyScene.h"
#include "APIHandler.h"

LobbyScene::LobbyScene() : Scene("LOBBY")
{
	srand(time(NULL));
	APIHandler::GetInstance()->newPlayer("p" + to_string(rand() % 5000 ), 8080);
	ui = new LobbyUI();
}

void LobbyScene::Update(float deltaTime)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Update(deltaTime);
	}

	ui->Update(deltaTime);
}

void LobbyScene::Render(RenderWindow & r)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Render(r);
	}

	ui->Render(r);
}

void LobbyScene::Destroy()
{
	Scene::Destroy();
}

void LobbyScene::Enter()
{
}
