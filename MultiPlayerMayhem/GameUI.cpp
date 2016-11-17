#include "GameUI.h"
#include "Button.h"
#include "GameScene.h"
#include <iostream>

void OnStartButton(Button * caller)
{
	GameScene::IsStarted = true;
	caller->SetVisible(false);
}

GameUI::GameUI()
{
	Button * button1 = new Button(Vector2f(400, 300), "Start!");
	m_gameObjects.push_back(button1);

	button1->AddOnMouseDown(OnStartButton);
}

GameUI::~GameUI()
{
	UICanvas::~UICanvas();
}
