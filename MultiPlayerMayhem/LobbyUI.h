#pragma once
#include "UICanvas.h"
#include "ListBox.h"

class LobbyUI : public UICanvas
{
private:
	ListBox * m_pInLobby;
public:
	LobbyUI();
	~LobbyUI();
};