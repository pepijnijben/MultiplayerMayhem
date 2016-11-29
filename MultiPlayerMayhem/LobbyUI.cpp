#include "LobbyUI.h"
#include "Button.h"
#include "SceneManager.h"
#include "Net.h"

void OnSetupButton(Button * caller)
{
	if (caller->GetTitle() == "Player 1")
	{
		Net::IsPlayer1 = true;
	}
	else
	{
		Net::IsPlayer1 = false;
	}

	SceneManager::GetInstance()->SwitchTo("GAME");
}

void OnCreateRoom(Button * caller)
{
	APIHandler::GetInstance()->createRoom();
}

LobbyUI::LobbyUI() 
{
	//Button * p1 = new Button(Vector2f(400, 250), "Player 1");
	//Button * p2 = new Button(Vector2f(400, 350), "Player 2");
	//p1->AddOnMouseDown(OnSetupButton);
	//p2->AddOnMouseDown(OnSetupButton);
	//m_gameObjects.push_back(p1);
	//m_gameObjects.push_back(p2);

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
		//cout << m_roomVector[m_rooms->CurrentSelected()].name << endl;
		APIHandler::GetInstance()->joinRoom(m_roomVector[m_rooms->CurrentSelected()].id);
	}
}
