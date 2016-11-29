#include "RoomScene.h"
#include "Button.h"

RoomScene::RoomScene() : Scene("ROOM")
{
	Button * StartGame = new Button(Vector2f(500, 50), "Start");

	if (!APIHandler::GetInstance()->IsHost())
	{
		StartGame->SetActive(false);
	}

	m_gameObjects.push_back(StartGame);
}

void RoomScene::Update(float deltaTime)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Update(deltaTime);
	}

	ui->Update(deltaTime);
}

void RoomScene::Render(RenderWindow & r)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Render(r);
	}

	ui->Render(r);
}

void RoomScene::Destroy()
{
	Scene::Destroy();
}

void RoomScene::Enter()
{
}