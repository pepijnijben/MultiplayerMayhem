#pragma once
#include "SceneManager.h"
#include "LobbyUI.h"

class LobbyScene : public Scene
{
private:
	LobbyUI * ui;
	bool m_receivedPing;
public:
	LobbyScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};