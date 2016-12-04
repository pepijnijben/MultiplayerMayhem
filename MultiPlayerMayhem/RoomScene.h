#pragma once
#include "SceneManager.h"
#include "ListBox.h"
#include "APIHandler.h"
#include "Net.h"
#include "Button.h"

class RoomScene : public Scene
{
private:
	ListBox * m_pInRoom;
	Net * m_net;
	Button * m_startGame;

	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;

	void InitUI();
	void UpdateUI(float);
	vector<string> DeserializeMessage(string message);
public:
	RoomScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};
