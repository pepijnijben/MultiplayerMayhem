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

	RectangleShape block = RectangleShape(Vector2f(195, 600));
	block.setFillColor(sf::Color(25, 27, 24));
	block.setPosition(0, 0);

	r.draw(block);

	block = RectangleShape(Vector2f(40, 45));
	block.setFillColor(m_player->GetColor());
	block.setPosition(140, 0);

	r.draw(block);

	Text text = Text(Counter, m_font, 50);
	text.setPosition(Vector2f(375,275));
	text.setStyle(sf::Text::Bold);
	text.setFillColor(Color::White);

	r.draw(text);

	block = RectangleShape(Vector2f(5, 20));
	block.setFillColor(m_player->GetColor());
	block.setPosition(10, 100);

	text = Text(m_player->Name + " (YOU)", m_font, 16);
	text.setPosition(Vector2f(20, 100));
	text.setFillColor(Color::White);

	r.draw(block);
	r.draw(text);

	text.setString(std::to_string(m_player->Score));
	text.setStyle(sf::Text::Bold);
	text.setPosition(160, 100);
	r.draw(text);

	int i = 1;
	for (auto& e : m_enemys)
	{
		block.setFillColor(e->GetColor());
		block.setPosition(10, 100 + i * 25);
		text.setString(e->Name);
		text.setStyle(sf::Text::Regular);
		text.setPosition(Vector2f(20, 100 + i * 25));

		r.draw(block);
		r.draw(text);

		text.setString(std::to_string(e->Score));
		text.setStyle(sf::Text::Bold);
		text.setPosition(160, 100 + i * 25);
		r.draw(text);

		i++;
	}
	
	RectangleShape gameField = RectangleShape(Vector2f(600, 590));
	gameField.setPosition(Vector2f(195, 5));
	gameField.setOutlineColor(sf::Color::White);
	gameField.setFillColor(Color(0, 0, 0, 0));
	gameField.setOutlineThickness(2);

	r.draw(gameField);

	text = Text("60", m_font, 30);
	text.setPosition(Vector2f(145, 7));
	text.setStyle(sf::Text::Bold);
	text.setFillColor(Color::White);

	r.draw(text);

	text = Text("FIRST TO REACH", m_font, 16);
	text.setPosition(Vector2f(20, 20));
	text.setFillColor(Color::White);

	r.draw(text);
}