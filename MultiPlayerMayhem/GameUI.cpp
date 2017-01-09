#include "GameUI.h"
#include "APIHandler.h"
#include <iostream>

GameUI::GameUI()
{
}

GameUI::~GameUI()
{
	UICanvas::~UICanvas();
}

void GameUI::Update(float deltaTime)
{
	UICanvas::Update(deltaTime);

	if (m_currentTime >= m_updateListsTime)
	{
		APIHandler::GetInstance()->checkInPlayer();
		m_currentTime = 0.0f;
	}
}
