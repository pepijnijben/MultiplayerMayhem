#include "GameUI.h"
#include "APIHandler.h"
#include <iostream>
#include "ThreadPool.h"

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
		ThreadPool::GetInstance()->AddJob(bind(&APIHandler::checkInPlayer, APIHandler::GetInstance()));
		m_currentTime = 0.0f;
	}
}
