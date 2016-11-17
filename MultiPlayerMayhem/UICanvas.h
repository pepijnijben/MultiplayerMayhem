#pragma once
#include "GameObject.h"

using namespace sf;
using namespace std;

class UICanvas : public GameObject
{
protected:
	vector<GameObject *> m_gameObjects;
public:
	UICanvas();
	~UICanvas();

	void Render(sf::RenderWindow & r) override;
	void Update(float deltaTime) override;
};