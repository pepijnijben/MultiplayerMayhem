#include "GameUI.h"
#include "Button.h"
#include <iostream>

void OnStartButton(Button* caller)
{
	cout << "Button pressed" << endl;
	caller->SetVisible(false);
}

GameUI::GameUI(Vector2f size) : UICanvas(size)
{
	Button * button1 = new Button(Vector2f(400, 300), Vector2f(105, 25), "Start!");
	m_gameObjects.push_back(button1);

	button1->AddOnMouseDown(OnStartButton);
}

GameUI::~GameUI()
{
	UICanvas::~UICanvas();
}
