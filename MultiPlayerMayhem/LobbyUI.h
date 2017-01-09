#pragma once
#include "UICanvas.h"
#include "ListBox.h"
#include "APIHandler.h"
#include "SFML/System.hpp"

class LobbyUI : public UICanvas
{
private:
	ListBox * m_pInLobby;
	ListBox * m_rooms;

	sf::Mutex mutexLobby;
	sf::Mutex mutexRooms;

	void updateLobbyList();
	void updateRoomList();

	vector<Room> m_roomVector;

	float m_updateListsTime = 1.0f;
	float m_currentTime = 0.0f;
public:
	LobbyUI();
	~LobbyUI();

	void Update(float deltaTime) override;
};
