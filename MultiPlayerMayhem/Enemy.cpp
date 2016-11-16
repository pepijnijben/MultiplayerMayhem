#include "Enemy.h"

Enemy::Enemy()
{
	m_shape.setRadius(3.0f);
	m_shape.setFillColor(Color(255, 0, 0));
	m_shape.setOrigin(3.0f, 3.0f);
}

Enemy::~Enemy()
{
}

void Enemy::Render(RenderWindow & r)
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

void Enemy::Update(float deltaTime)
{
	m_shape.setPosition(m_position);
}

void Enemy::SetPosition(Vector2f pos)
{
	m_position = pos;
	m_tail.push_back(pos);
}

void Enemy::Deserialize(string message)
{
	// TODO: Deserialize message and set position
}