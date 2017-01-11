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

	Text title = Text(to_string(GameTime), m_font, 25);
	title.setPosition(Vector2f(100,100));
	title.setStyle(sf::Text::Regular);
	title.setFillColor(Color::White);

	r.draw(title);
}