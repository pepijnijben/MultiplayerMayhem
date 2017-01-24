#pragma once
#include <iostream>
#include "GameObject.h"
#include <functional>

using namespace std;
using namespace sf;

class ListBox : public GameObject
{
private:
	vector<GameObject *> m_gameObjects;
	vector<string> m_listItems;
	RectangleShape m_background;
	vector<RectangleShape> m_listBackground;
	Font m_font;

	Vector2i m_mousePosition;
	float m_isPressed;
	int m_currentSelected = -1;
	vector<function<void(int)>> m_onMouseDown;

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

		for(auto & item : m_listBackground)
		{
			r.draw(item);
		}

		int i = 0;
		for (auto & item : m_listItems)
		{
			Text title = Text(item, m_font, 25);
			title.setPosition(Vector2f(m_position.x + 10, m_position.y + (i * 35)));
			title.setStyle(sf::Text::Regular);
			title.setFillColor(Color::White);

			r.draw(title);
			i++;
		}

		m_mousePosition = sf::Mouse::getPosition(r);
	};
	void Update(float deltaTime) override
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}

		// Check if hover over one of the things
		int id = 0;
		for (auto& obj : m_listBackground)
		{
			Vector2f size = obj.getSize();
			Vector2f pos = obj.getPosition();

			bool mouseInButton = m_mousePosition.x >= pos.x
				&& m_mousePosition.x <= pos.x + size.x
				&& m_mousePosition.y >= pos.y
				&& m_mousePosition.y <= pos.y + size.y;

			Color temp;

			if (mouseInButton)
			{
				temp = Color(200, 200, 200, 255);

				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					m_isPressed = true;
					m_currentSelected = id;
				}
				else
				{
					m_isPressed = false;
				}
			}
			else
			{
				temp = id % 2 ? Color(100, 100, 100, 128) : Color(200, 200, 200, 128);
			}
			
			obj.setFillColor(temp);
			id++;
		}

		if (!Mouse::isButtonPressed(Mouse::Button::Left))
		{
			m_currentSelected = -1;
			m_isPressed = false;
		}
	};

	void AddRow(string s)
	{
		//m_gameObjects.push_back(new ListItem());
		m_listItems.push_back(s);

		RectangleShape rs;
		rs.setSize(Vector2f(m_background.getSize().x, 35));
		rs.setPosition(m_background.getPosition().x, m_background.getPosition().y + (m_listBackground.size() * 35));

		if (m_listBackground.size() % 2 == 1)
		{
			rs.setFillColor(Color(100, 100, 100, 128));
		}
		else
		{
			rs.setFillColor(Color(200, 200, 200, 128));
		}

		m_listBackground.push_back(rs);
	}

	void CleanList()
	{
		m_listItems.clear();
		m_listBackground.clear();
	}

	bool IsPressed() const { return m_isPressed; }
	void IsPressed(bool val) { m_isPressed = val; }
	int CurrentSelected() const { return m_currentSelected; }

	template<typename Function>
	void AddOnMouseDown(Function && cb) { m_onMouseDown.push_back(forward<Function>(cb)); };
};