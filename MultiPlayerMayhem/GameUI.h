#pragma once
#include "UICanvas.h"

class GameUI : public UICanvas
{
private:
	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;
public:
	GameUI();
	~GameUI();
	void Update(float deltaTime) override;
};