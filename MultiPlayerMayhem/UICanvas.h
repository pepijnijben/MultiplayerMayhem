#pragma once
#include "GameObject.h"

using namespace sf;
using namespace std;

class UICanvas : public GameObject
{
protected:
	Vector2f m_size;
	vector<GameObject *> m_gameObjects;
public:
	UICanvas(Vector2f size);
	~UICanvas();

	void Render(sf::RenderWindow & r) override;
	void Update(float deltaTime) override;

	virtual void SetSize(Vector2f size);
	Vector2f GetSize();
};