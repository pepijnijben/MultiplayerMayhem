#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Net.h";

class Game
{
private:
	sf::RenderWindow * window;
	std::vector<GameObject*> gameObjects;
	Net net;

public:
	static bool quit;
	Game();
	~Game();

	bool init();
	void destroy();

	void update(float deltaTime);
	void render();
	void loop();

	//void onEvent(EventListener::Event);
};