#pragma once
#include <SFML/Graphics.hpp>

/*Base class for all in game objects*/
class GameObject
{
protected:
	sf::Vector2f m_position;
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void Render(sf::RenderWindow & r) = 0;
	virtual void Update(float deltaTime) = 0;

	sf::Vector2f GetPosition() { return m_position; }
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
};
