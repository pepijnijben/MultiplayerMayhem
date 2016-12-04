#include "Game.h"
#include "Player.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "RoomScene.h"

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
	SceneManager::GetInstance()->AddScene(new GameScene);
	SceneManager::GetInstance()->AddScene(new LobbyScene);
	SceneManager::GetInstance()->AddScene(new RoomScene);

	SceneManager::GetInstance()->SwitchTo("LOBBY");
	Font m_font;

	return true;
}

void Game::destroy()
{
	SceneManager::GetInstance()->Destroy();
}

void Game::update(float deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);
}

void Game::render()
{
	// Clear the window
	window->clear();

	SceneManager::GetInstance()->Render(*window);

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
		render();

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
