#include "LobbyUI.h"
#include "Button.h"
#include "SceneManager.h"
#include "Net.h"
#include "APIHandler.h"

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


LobbyUI::LobbyUI() 
{
	Button * p1 = new Button(Vector2f(400, 250), "Player 1");
	Button * p2 = new Button(Vector2f(400, 350), "Player 2");
	
	m_pInLobby = new ListBox(Vector2f(25, 25), Vector2f(100, 200));

	for (auto & item : APIHandler::GetInstance()->getPlayers())
	{
		m_pInLobby->AddRow(item.name);
	}

	p1->AddOnMouseDown(OnSetupButton);
	p2->AddOnMouseDown(OnSetupButton);

	m_gameObjects.push_back(p1);
	m_gameObjects.push_back(p2);
	m_gameObjects.push_back(m_pInLobby);
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

		APIHandler::GetInstance()->checkInPlayer();

		m_currentTime = 0.0f;
	}
}
