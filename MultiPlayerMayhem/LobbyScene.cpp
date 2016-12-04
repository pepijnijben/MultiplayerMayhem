#include "LobbyScene.h"
#include "APIHandler.h"
#include "Net.h"

LobbyScene::LobbyScene() : Scene("LOBBY")
{
	int port = Net::GetInstance()->GetLocalPort();
	srand(time(NULL));
	APIHandler::GetInstance()->newPlayer("p" + to_string(rand() % 5000), port);
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
	Net::GetInstance()->SetRemotePlayers(vector<NetPlayer>());
}
