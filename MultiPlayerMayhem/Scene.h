#pragma once
#include "GameObject.h"

using namespace std;
using namespace sf;

class Scene
{
public:
	Scene(string title);
	virtual void Enter();
	virtual void Exit();
	virtual void Destroy();
	virtual string GetTitle();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(RenderWindow & r) = 0;
protected:
	string m_title;
	vector<GameObject *> m_gameObjects;
};