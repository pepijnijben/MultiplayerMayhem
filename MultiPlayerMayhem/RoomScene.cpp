#include "RoomScene.h"
#include "ThreadPool.h"

void OnStartButton(Button * caller)
{
	SceneManager::GetInstance()->SwitchTo("GAME");
}

void OnBackButton(Button * caller)
{
	if (APIHandler::GetInstance()->IsHost())
	{
		APIHandler::GetInstance()->removeRoom();
	}

	SceneManager::GetInstance()->SwitchTo("LOBBY");
}

void RoomScene::updateRoomList()
{
	vector<NetPlayer> players = APIHandler::GetInstance()->getRoomPlayers();
	mutexRooms.lock();
	m_pInRoom->CleanList();
	for (auto & item : players)
	{
		m_pInRoom->AddRow(item.name);
	}
	mutexRooms.unlock();
}

void RoomScene::InitUI()
{
	Button * back = new Button(Vector2f(500, 100), "Back");
	back->AddOnMouseDown(OnBackButton);

	m_startGame = new Button(Vector2f(500, 50), "Start");
	m_startGame->AddOnMouseDown(OnStartButton);
	m_pInRoom = new ListBox(Vector2f(25, 25), Vector2f(150, 485));

	m_gameObjects.push_back(m_startGame);
	m_gameObjects.push_back(back);
	m_gameObjects.push_back(m_pInRoom);
}

void RoomScene::UpdateUI(float deltaTime)
{
	m_currentTime += deltaTime;

	if (m_currentTime >= m_updateListsTime)
	{
		ThreadPool::GetInstance()->AddJob(bind(&RoomScene::updateRoomList, this));
		ThreadPool::GetInstance()->AddJob(bind(&APIHandler::checkInPlayer, APIHandler::GetInstance()));
		m_currentTime = 0.0f;
	}
}

RoomScene::RoomScene() : Scene("ROOM")
{
	m_net = Net::GetInstance();
	InitUI();
}

void RoomScene::Update(float deltaTime)
{
	mutexRooms.lock();
	for (auto & obj : m_gameObjects)
	{
		obj->Update(deltaTime);
	}
	mutexRooms.unlock();

	UpdateUI(deltaTime);

	vector<string> messages = m_net->Receive();

	for (auto & s : messages)
	{
		if (s != "")
		{
			vector<string> values = DeserializeMessage(s);
			
			if (values[0] == "GAME")
			{
				if (values[1] == "STARTED")
				{
					SceneManager::GetInstance()->SwitchTo("GAME");
				}
			}
		}
	}
}

void RoomScene::Render(RenderWindow & r)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Render(r);
	}
}

void RoomScene::Destroy()
{
	Scene::Destroy();
}

void RoomScene::Enter()
{
	if (!APIHandler::GetInstance()->IsHost())
	{
		m_startGame->SetActive(false);
	}
}

vector<string> RoomScene::DeserializeMessage(string message)
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