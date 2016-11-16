#include "Scene.h"

Scene::Scene(string title) :m_title(title)
{
}

void Scene::Enter()
{
}

void Scene::Exit()
{
}

void Scene::Destroy()
{
	for (vector<GameObject*>::iterator i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
		delete *i;
	}
	m_gameObjects.clear();
}

string Scene::GetTitle()
{
	return m_title;
}
