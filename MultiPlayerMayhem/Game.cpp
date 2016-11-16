#include "Game.h"
#include "Player.h"

const int MAX_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / MAX_FPS;

bool Game::quit = false;

Game::Game()
{
	init();
}

Game::~Game()
{
}

bool Game::init()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "MultiPlayerMayhem", sf::Style::Default, settings);
	gameObjects.push_back(new Player);

	return true;
}

void Game::destroy()
{
}

void Game::update(float deltaTime)
{
	for (auto& obj : gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Game::render()
{
	// Clear the window
	window->clear();

	for (auto& obj : gameObjects)
	{
		obj->Render(*window);
	}

	// Show the window
	window->display();
}

void Game::loop()
{

	sf::Clock clock;
	float deltaTime = 0;

	while (!Game::quit)
	{
		// Input handler
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Game::quit = true;
				window->close();
			}
		}

		update(deltaTime);

		// Send and Receive messages
		string s = net.Receive();

		if (s != "")
		{
			cout << "Received message: " << s << endl;
		}

		render();

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			net.Send();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			Game::quit = true;
		}

		while (clock.getElapsedTime() <= sf::milliseconds(SCREEN_TICKS_PER_FRAME))
		{
			sf::sleep(sf::milliseconds(1));
		}

		deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
	}
}
