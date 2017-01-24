#pragma once
#include <SFML/Graphics.hpp>

/*Base class for all in game objects*/
class GameObject
{
protected:
	sf::Vector2f m_position;

	bool GameObject::circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2)
	{
		//compare the distance to combined radii
		int dx = x2 - x1;
		int dy = y2 - y1;
		int radii = radius1 + radius2;

		return ((dx * dx) + (dy * dy) < radii * radii);
	}
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void Render(sf::RenderWindow & r) = 0;
	virtual void Update(float deltaTime) = 0;

	sf::Vector2f GetPosition() const { return m_position; }
	virtual void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
	{
		return (start + percent*(end - start));
	}
};
