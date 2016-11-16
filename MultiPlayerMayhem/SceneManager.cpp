#include "SceneManager.h"
#include <iostream>

SceneManager * SceneManager::instance = 0;

SceneManager::SceneManager() : m_currentScene(nullptr)
{
}

SceneManager * SceneManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::Update(float deltaTime)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Update(deltaTime);
	}
}

void SceneManager::Render(RenderWindow & r)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Render(r);
	}
}

void SceneManager::SwitchTo(string scene)
{
	bool sceneFound = false;
	int i = 0;
	Scene* nextScene = nullptr;

	//checks if the scene is there, if it isn't, do nothing
	while (i < m_scenes.size() && !sceneFound)
	{
		if (m_scenes.at(i)->GetTitle() == scene)
		{
			sceneFound = true;
			nextScene = m_scenes.at(i);
		}
		i++;
	}

	if (sceneFound)
	{
		if (m_currentScene != nullptr)
		{
			//exit the old scene 
			m_currentScene->Exit();
		}

		//enter the new scene
		m_currentScene = nextScene;
		m_currentScene->Enter();

		cout << "Switched to scene " << m_currentScene->GetTitle() << endl;
	}
	else
	{
		cout << "Scene " << scene << " not found!" << endl;
	}
}

void SceneManager::Destroy()
{
	for (Scene*& scene : m_scenes)
	{
		scene->Destroy();
	}
}

const Scene * SceneManager::GetCurrentScene()
{
	return m_currentScene;
}

void SceneManager::AddScene(Scene * newScene)
{
	m_scenes.push_back(newScene);
}
