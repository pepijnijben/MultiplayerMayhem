#pragma once
#include <SFML/System/Vector2.hpp>

class Snapshot
{
public:
	float Time;
	sf::Vector2f Position;
	sf::Vector2f Velocity;

	Snapshot(float t, sf::Vector2f p, sf::Vector2f v)
	{
		Time = t;
		Position = p;
		Velocity = v;
	}
};
