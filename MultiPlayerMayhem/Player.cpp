#include "Player.h"
#include <iostream>

Player::Player()
{
	m_shape.setRadius(3.0f);
	m_shape.setFillColor(Color(0, 0, 255));
	m_shape.setOrigin(5.0f, 5.0f);
	m_position.x = 400.0f;
	m_position.y = 300.0f;

	// Random direction calculation
	srand(time(NULL));
	if (rand() % 2 == 0)
	{
		m_velocity.x = rand() % 2 ? MAX_VELOCITY : -MAX_VELOCITY;
		m_velocity.y = (rand() % (int)(MAX_VELOCITY * 2)) - MAX_VELOCITY;
	}
	else
	{
		m_velocity.x = (rand() % (int)(MAX_VELOCITY * 2)) - MAX_VELOCITY;
		m_velocity.y = rand() % 2 ? MAX_VELOCITY : -MAX_VELOCITY;
	}
}

Player::~Player()
{
}

void Player::Render(RenderWindow & r)
{
	CircleShape temp;

	for (auto& obj : m_tail)
	{
		temp = CircleShape(m_shape);
		temp.setPosition(obj);

		r.draw(temp);
	}
	r.draw(m_shape);
}

void Player::Update(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (m_velocity.x >= 0 && m_velocity.y < MAX_VELOCITY) // go to down and right
		{
			if (m_velocity.x >= MAX_VELOCITY)
			{
				m_velocity.y += TURN_RATE;
			}
			else
			{
				m_velocity.x += TURN_RATE;
			}
		} 
		else if (m_velocity.x > -MAX_VELOCITY && m_velocity.y >= MAX_VELOCITY) // go to down and left
		{
			m_velocity.x -= TURN_RATE;
		}
		else if (m_velocity.y > -MAX_VELOCITY && m_velocity.x <= -MAX_VELOCITY) // go to left and up
		{
			m_velocity.y -= TURN_RATE;
		}
		else if (m_velocity.y >= -MAX_VELOCITY && m_velocity.x < 0)
		{
			m_velocity.x += TURN_RATE;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (m_velocity.y <= -MAX_VELOCITY && m_velocity.x > -MAX_VELOCITY) // Left UP
		{
			m_velocity.x -= TURN_RATE;
		} 
		else if (m_velocity.y < MAX_VELOCITY && m_velocity.x <= -MAX_VELOCITY) // Left bottom
		{
			m_velocity.y += TURN_RATE;
		}
		else if (m_velocity.y >= MAX_VELOCITY && m_velocity.x < MAX_VELOCITY) // right bottom
		{
			m_velocity.x += TURN_RATE;
		}
		else if (m_velocity.y > -MAX_VELOCITY && m_velocity.x >= MAX_VELOCITY) // RIGHT TOP
		{
			m_velocity.y -= TURN_RATE;
		}
	}

	m_tail.push_back(Vector2f(m_position));
	m_position += m_velocity * deltaTime;
	m_shape.setPosition(GetPosition());
}

Vector2f Player::normalize(const Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return Vector2f(source.x / length, source.y / length);
	else
		return source;
}