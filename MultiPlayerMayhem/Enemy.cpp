#include "Enemy.h"
#include <iostream>

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
	//m_shape.setPosition(m_position);
}

void Enemy::SetPosition(Vector2f pos)
{
	m_position = pos;
	m_tail.push_back(pos);
}

void Enemy::Deserialize(string message)
{
	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;
	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	if (token.size() >= 2)
	{
		float x = stof(token.at(0));
		float y = stof(token.at(1));

		SetPosition(Vector2f(x, y));
	}
}