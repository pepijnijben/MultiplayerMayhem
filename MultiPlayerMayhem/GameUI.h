#pragma once
#include "UICanvas.h"
#include "Button.h"
#include "Player.h"
#include "Enemy.h"

class GameUI : public UICanvas
{
private:
	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;

	Player * m_player;
	vector<Enemy*> m_enemys;

	Font m_font;
public:
	GameUI();
	~GameUI();
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow & r) override;
	void SetEnemies(vector<Enemy*> e) { m_enemys = e; };
	void SetPlayer(Player * p) { m_player = p; };
	string Counter = "";
	string lastWinner = "";
};