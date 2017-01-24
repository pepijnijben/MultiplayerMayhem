#include "LobbyUI.h"
#include "Button.h"
#include "SceneManager.h"
#include "Net.h"
#include "ThreadPool.h"

void OnCreateRoom(Button * caller)
{
	if (APIHandler::GetInstance()->createRoom())
	{
		APIHandler::HOST = true;
		SceneManager::GetInstance()->SwitchTo("ROOM");
	}
}

void LobbyUI::updateLobbyList()
{
	vector<NetPlayer> players = APIHandler::GetInstance()->getPlayers();
	mutexLobby.lock();
	m_pInLobby->CleanList();
	for (auto & item : players)
	{
		m_pInLobby->AddRow(item.name);
	}
	mutexLobby.unlock();
}

void LobbyUI::updateRoomList()
{
	m_roomVector = APIHandler::GetInstance()->getRooms();
	mutexRooms.lock();
	m_rooms->CleanList();
	for (auto & item : m_roomVector)
	{
		m_rooms->AddRow(item.name);
	}
	mutexRooms.unlock();
}

LobbyUI::LobbyUI()
{
	// Create room button
	Button * createRoom = new Button(Vector2f(100, 555), "Create Room");
	createRoom->AddOnMouseDown(OnCreateRoom);

	// ListBoxes
	m_pInLobby = new ListBox(Vector2f(25, 25), Vector2f(150, 485));
	m_rooms = new ListBox(Vector2f(200, 25), Vector2f(575, 550));

	m_gameObjects.push_back(createRoom);
	m_gameObjects.push_back(m_pInLobby);
	m_gameObjects.push_back(m_rooms);
}

LobbyUI::~LobbyUI()
{
	UICanvas::~UICanvas();
}

void LobbyUI::Update(float deltaTime)
{
	mutexLobby.lock();
	mutexRooms.lock();
	UICanvas::Update(deltaTime);
	mutexLobby.unlock();
	mutexRooms.unlock();

	m_currentTime += deltaTime;

	if (m_currentTime >= m_updateListsTime)
	{
		ThreadPool::GetInstance()->AddJob(bind(&LobbyUI::updateLobbyList, this));
		ThreadPool::GetInstance()->AddJob(bind(&LobbyUI::updateRoomList, this));

		ThreadPool::GetInstance()->AddJob(bind(&APIHandler::checkInPlayer, APIHandler::GetInstance()));

		m_currentTime = 0.0f;
	}

	if (m_rooms->IsPressed())
	{
		if (APIHandler::GetInstance()->joinRoom(m_roomVector[m_rooms->CurrentSelected()].id))
		{
			m_rooms->IsPressed(false);
			SceneManager::GetInstance()->SwitchTo("ROOM");
		}
	}
}
