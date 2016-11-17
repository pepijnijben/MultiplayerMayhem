#pragma once
#include "SceneManager.h"
#include "Net.h"
#include "Button.h"
#include "GameUI.h"

class GameScene : public Scene
{
private:
	Net net;
	GameUI * ui;
public:
	GameScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;

	static bool IsStarted;
};
