#include "GameUI.h"
#include "APIHandler.h"
#include <iostream>
#include "ThreadPool.h"

GameUI::GameUI()
{
	// Load font
	if (!m_font.loadFromFile("fonts/calibri.ttf"))
	{
		cout << "Unable to load fonts/calibri.tff" << endl;
	}
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

void GameUI::Render(sf::RenderWindow & r)
{
	UICanvas::Render(r);

	Text title = Text(Counter, m_font, 50);
	title.setPosition(Vector2f(375,275));
	title.setStyle(sf::Text::Bold);
	title.setFillColor(Color::White);

	r.draw(title);
}