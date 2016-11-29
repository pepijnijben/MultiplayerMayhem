#pragma once
#include "UICanvas.h"
#include "ListBox.h"
#include "APIHandler.h"

class RoomUI : public UICanvas
{
private:
	ListBox * m_pInLobby;
	ListBox * m_rooms;

	vector<Room> m_roomVector;

	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;
public:
	RoomUI();
	~RoomUI();

	void Update(float deltaTime) override;
};