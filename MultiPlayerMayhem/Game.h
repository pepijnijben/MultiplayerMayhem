#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Net.h";

class Game
{
private:
	sf::RenderWindow * window;

public:
	static bool quit;
	static bool pause;

	Game();
	~Game();

	bool init();
	void destroy();

	void update(float deltaTime);
	void render();
	void loop();
};