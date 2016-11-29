#pragma once
#include "UICanvas.h"
#include "ListBox.h"

class LobbyUI : public UICanvas
{
private:
	ListBox * m_pInLobby;

	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;
public:
	LobbyUI();
	~LobbyUI();

	void Update(float deltaTime) override;
};