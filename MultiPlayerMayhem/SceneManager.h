#pragma once
#include "Scene.h"
using namespace std;
using namespace sf;

class SceneManager
{
private:
	Scene* m_currentScene;
	vector<Scene *> m_scenes;

	static SceneManager * instance;
public:
	SceneManager();
	static SceneManager * GetInstance();
	
	void Update(float deltaTime);
	void Render(RenderWindow & r);

	void SwitchTo(string scene);
	void Destroy();

	const Scene * GetCurrentScene();
	void AddScene(Scene * newScene);
};