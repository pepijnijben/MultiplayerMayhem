#include "UICanvas.h"

UICanvas::UICanvas(Vector2f size)
{
	m_size = size;
}

UICanvas::~UICanvas()
{
	for (vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
		delete *i;
	}
	m_gameObjects.clear();
}

void UICanvas::Render(sf::RenderWindow & r)
{
	for(auto& obj : m_gameObjects)
	{
		obj->Render(r);
	}
}

void UICanvas::Update(float deltaTime)
{
	for (auto& obj : m_gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void UICanvas::SetSize(Vector2f size)
{
	m_size = size;
}

Vector2f UICanvas::GetSize()
{
	return m_size;
}
