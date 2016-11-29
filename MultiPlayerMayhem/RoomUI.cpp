#include "RoomUI.h"

RoomUI::RoomUI()
{
}

RoomUI::~RoomUI()
{
	UICanvas::~UICanvas();
}

void RoomUI::Update(float deltaTime)
{
	UICanvas::Update(deltaTime);

	m_currentTime += deltaTime;
}
