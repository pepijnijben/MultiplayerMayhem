#include "Button.h"
#include <iostream>

Button::Button(Vector2f pos, string title)
{
	m_position = pos;
	m_isVisible = true;
	m_isActive = true;

	// Load font
	if (!m_font.loadFromFile("fonts/calibri.ttf"))
	{
		cout << "Unable to load fonts/calibri.tff" << endl;
	}

	// Setup title
	m_title = Text(title.c_str(), m_font, 30);
	m_title.setPosition(m_position);
	m_title.setStyle(sf::Text::Regular);
	m_title.setOrigin((m_title.getGlobalBounds().width / 2) + 3, m_title.getGlobalBounds().height + 1);
	m_title.setFillColor(Color::Black);

	m_size = Vector2f(m_title.getGlobalBounds().width + 20, m_title.getGlobalBounds().height + 20);

	// Setup background
	m_background.setSize(m_size);
	m_background.setOrigin(m_size.x / 2, m_size.y / 2);
	m_background.setFillColor(Color::White);
	m_background.setOutlineColor(Color(100, 100, 100));
	m_background.setOutlineThickness(3.0f);
	m_background.setPosition(m_position);
}

void Button::Render(sf::RenderWindow & r)
{
	if (m_isVisible)
	{
		r.draw(m_background);
		r.draw(m_title);
	}

	m_mousePosition = sf::Mouse::getPosition(r);
}

void Button::Update(float deltaTime)
{
	if (m_isActive && m_isVisible)
	{
		bool mouseInButton = m_mousePosition.x >= m_position.x - m_size.x / 2
			&& m_mousePosition.x <= m_position.x + m_size.x / 2
			&& m_mousePosition.y >= m_position.y - m_size.y / 2
			&& m_mousePosition.y <= m_position.y + m_size.y / 2;

		if (mouseInButton)
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				if (!m_isPressed)
				{
					for(auto && cb : m_onMouseDown)
					{
						cb(this);
					}
				}
				m_isPressed = true;
			}
			else
			{
				m_isPressed = false;
			}
		}
		else
		{
			m_isPressed = false;
		}
	}
}
