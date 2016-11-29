#pragma once
#include "SceneManager.h"
#include "RoomUI.h"

class RoomScene : public Scene
{
private:
	RoomUI * ui;
public:
	RoomScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};
