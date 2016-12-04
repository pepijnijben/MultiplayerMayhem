#include "LobbyUI.h"
#include "Button.h"
#include "SceneManager.h"
#include "Net.h"

void OnCreateRoom(Button * caller)
{
	APIHandler::GetInstance()->createRoom();
	SceneManager::GetInstance()->SwitchTo("ROOM");
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
	UICanvas::Update(deltaTime);

	m_currentTime += deltaTime;

	if (m_currentTime >= m_updateListsTime)
	{
		m_pInLobby->CleanList();

		for (auto & item : APIHandler::GetInstance()->getPlayers())
		{
			m_pInLobby->AddRow(item.name);
		}

		m_rooms->CleanList();
		m_roomVector = APIHandler::GetInstance()->getRooms();
		for (auto & item : m_roomVector)
		{
			m_rooms->AddRow(item.name);
		}

		APIHandler::GetInstance()->checkInPlayer();

		m_currentTime = 0.0f;
	}

	if (m_rooms->IsPressed())
	{
		APIHandler::GetInstance()->joinRoom(m_roomVector[m_rooms->CurrentSelected()].id);
		SceneManager::GetInstance()->SwitchTo("ROOM");
	}
}
