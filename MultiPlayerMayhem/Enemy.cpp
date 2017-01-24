#include "Enemy.h"
#include "BasicTypes.h"
#include <iostream>

Enemy::Enemy()
{
	settings = Settings::getInstance();

	m_isAlive = true;
	m_shape.setRadius(3.0f);

	int r = rand() % cols_left.size();
	Color c = cols_left[r];
	cols_left.erase(cols_left.begin() + r);

	m_shape.setFillColor(c);
	m_shape.setOrigin(3.0f, 3.0f);

	m_lines.push_back(vector<Line>());
	Score = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Render(RenderWindow & r)
{
	CircleShape temp;


	for (auto& lines : m_lines)
	{
		for (auto & line : lines)
		{
			r.draw(line);
		}
	}
	for (auto& obj : m_tail)
	{
		temp = CircleShape(m_shape);
		temp.setPosition(obj);
		//temp.setFillColor(sf::Color::White);
		r.draw(temp);
	}

	if (m_tail.size() > 0 && !stopDrawing)
	{
		r.draw(Line(m_tail[m_tail.size() - 1], m_position, m_shape.getFillColor()));
	}

	r.draw(m_shape);
}

void Enemy::Update(float deltaTime)
{
	GameTime += deltaTime;

	if (m_isAlive)
	{
		// Update player position
		if (settings->NetSolution == NetworkSolution::Interpolation) // Interpolation
		{
			if (m_snapshots.size() > 1)
			{
				for (int i = m_snapshots.size() - 1; i > 0; i--)
				{
					if (m_snapshots[i - 1].Time < GameTime - 0.1f && m_snapshots[i].Time >= GameTime - 0.1f)
					{
						float percentage = ((GameTime - 0.1f) - m_snapshots[i - 1].Time) / (m_snapshots[i].Time - m_snapshots[i - 1].Time);
						m_position = Lerp(m_snapshots[i - 1].Position, m_snapshots[i].Position, percentage);
						break;
					}
						
					if (m_snapshots[i].Time < GameTime - 0.1f)
					{
						m_position += m_velocity * deltaTime;
					}
				} // End loop snapshots
			}
		}
		else if (fraction < 1) // ClientPrediction
		{
			fraction += (1.0f / 4.0f);
			m_position = Lerp(m_position, m_desPosition, fraction);
		} 
		else
		{
			m_position += m_velocity * deltaTime;
		}

		// Draw stuff
		m_shape.setPosition(m_position);

		if (currentTick % 10 == 0)
		{
			if (!stopDrawing && (m_tail.size() == 0 || !(m_tail[m_tail.size() - 1].x == m_position.x && m_tail[m_tail.size() - 1].y == m_position.y)))
			{
				if (m_tail.size() > 0)
				{
					m_lines.at(m_lines.size() - 1).push_back(Line(m_tail.at(m_tail.size() - 1), m_position, m_shape.getFillColor()));
				}

				m_tail.push_back(m_position);
			}
		}

		currentTick++;
	}
}

void Enemy::Deserialize(vector<string> token, bool reset)
{
	if (token.at(2) == "DEAD")
	{
		m_isAlive = false;
	}
	else if (token.at(2) == "SCORE")
	{
		int points = stoi(token.at(3));
		Score += points;
	}
	else if (token.size() >= 7)
	{
		if (reset)
		{
			ResetEnemy();
		}

		// Get message info
		float x = stof(token.at(2));
		float y = stof(token.at(3));

		float velX = stof(token.at(5));
		float velY = stof(token.at(6));

		bool tempDrawing = stoi(token.at(4));

		// Check if we need to start a new line
		if (stopDrawing && !tempDrawing)
		{
			m_lines.push_back(vector<Line>());

			if (!(m_tail[m_tail.size() - 1].x == x && m_tail[m_tail.size() - 1].y == y))
			{
				m_tail.push_back(m_position);
			}
		}

		stopDrawing = tempDrawing;
		m_velocity = Vector2f(velX, velY);

		// Interpolation
		if (settings->NetSolution == NetworkSolution::Interpolation)
		{
			//m_snapshots.push_back(Snapshot(stof(token.at(7)), Vector2f(x, y), Vector2f(velX, velY)));
			m_snapshots.push_back(Snapshot(GameTime, Vector2f(x, y), Vector2f(velX, velY)));

			for (int i = m_snapshots.size() - 1; i >= 0; i--)
			{
				if (m_snapshots[i].Time < GameTime - 0.1f)
				{
					m_snapshots.erase(m_snapshots.begin() + i);
				}
			}
		}
		else // ClientPrediction
		{
			// Set destination
			if (m_tail.size() > 0)
			{
				m_desPosition = Vector2f(x, y) + ((m_velocity * 4.0f) * 0.02f);
				fraction = 0;
				//m_position = Vector2f(x, y);
			}
		}

		// When no begin add the begin part of the enemy
		if (m_tail.size() <= 0)
		{
			m_position = Vector2f(x, y);
			m_shape.setPosition(Vector2f(x, y));
			m_tail.push_back(m_position);
		}
	}
}

bool Enemy::CollidedWith(Vector2f pos)
{
	float radius = m_shape.getRadius();

	for (auto& obj : m_tail)
	{
		if (circlesColliding(pos.x, pos.y, radius, obj.x, obj.y, radius))
		{
			return true;
		}
	}

	return false;
}

bool Enemy::CollidedWithItself()
{
	float radius = m_shape.getRadius();

	for (int i = m_tail.size() - 5; i >= 0; i--)
	{
		if (circlesColliding(m_position.x, m_position.y, radius, m_tail[i].x, m_tail[i].y, radius))
		{
			cout << "WITH ENEMY SELF! " << m_tail.size() << endl;
			cout << "(" << m_position.x << ", " << m_position.y << ") (" << m_tail[i].x << ", " << m_tail[i].y << ")" << endl;
			return true;
		}
	}

	return false;
}

void Enemy::ResetEnemy()
{
	m_isAlive = true;
	stopDrawing = false;
	currentTick = 0;
	fraction = 1;

	m_snapshots.clear();
	m_snapshots.shrink_to_fit();
	m_tail.clear();
	m_tail.shrink_to_fit();
	m_lines.clear();
	m_lines.shrink_to_fit();

	m_lines.push_back(vector<Line>());
}
