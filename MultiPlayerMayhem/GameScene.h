#pragma once
#include "SceneManager.h"
#include "Net.h"

class GameScene : public Scene
{
private:
	Net net;
public:
	GameScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};