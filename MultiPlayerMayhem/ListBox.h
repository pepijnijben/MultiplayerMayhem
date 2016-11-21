#pragma once
#include <iostream>
#include "GameObject.h"

using namespace std;
using namespace sf;

class ListBox : public GameObject
{
private:
	vector<GameObject *> m_gameObjects;
	vector<string> m_listItems;
	RectangleShape m_background;
	Font m_font;
public:
	ListBox(Vector2f pos, Vector2f size)
	{
		m_position = pos;
		m_background.setPosition(m_position);
		m_background.setSize(size);

		m_background.setFillColor(Color(0, 0, 0, 0));
		m_background.setOutlineColor(Color::White);
		m_background.setOutlineThickness(2);

		// Load font
		if (!m_font.loadFromFile("fonts/calibri.ttf"))
		{
			cout << "Unable to load fonts/calibri.tff" << endl;
		}
	};
	~ListBox()
	{
		for (vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
			delete *i;
		}
		m_gameObjects.clear();
	};

	void Render(sf::RenderWindow & r) override
	{
		r.draw(m_background);

		for (auto& obj : m_gameObjects)
		{
			obj->Render(r);
		}

		int i = 0;
		for (auto & item : m_listItems)
		{
			Text title = Text(item, m_font, 25);
			title.setPosition(Vector2f(m_position.x + 10, m_position.y + (i * 25)));
			title.setStyle(sf::Text::Regular);
			title.setFillColor(Color::White);

			r.draw(title);
			i++;
		}
	};
	void Update(float deltaTime) override
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}
	};

	void AddRow(string s)
	{
		//m_gameObjects.push_back(new ListItem());
		m_listItems.push_back(s);
	}
};