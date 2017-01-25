#pragma once
#include "SceneManager.h"
#include "Button.h"
#include "Settings.h"
#include "APIHandler.h"

class SettingsScene : public Scene
{
private:
	Settings * settings;

	Button * b1;
	Button * b2;

	vector<Button *> m_pointButtons;
	vector<Button *> m_latencyButtons;

	float m_currentTime = 0.0f;
	float m_updateListsTime = 1.0f;
	void UpdateUI(float);
public:
	SettingsScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};