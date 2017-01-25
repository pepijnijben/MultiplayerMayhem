#include "SettingsScene.h"
#include "ThreadPool.h"

void OnBackButtonSettings(Button * caller)
{
	SceneManager::GetInstance()->SwitchTo("LOBBY");
}

void OnNetButton(Button * caller)
{
	if (caller->GetTitle() == "ClientPrediction")
	{
		Settings::getInstance()->NetSolution = NetworkSolution::ClientPredictionExtrapolation;
	}
	else
	{
		Settings::getInstance()->NetSolution = NetworkSolution::Interpolation;
	}
}

void OnPointButton(Button * caller)
{
	Settings::getInstance()->WinningScore = stoi(caller->GetTitle());
}

void OnLatencyButton(Button * caller)
{
	Settings::getInstance()->Latency = stoi(caller->GetTitle());
}

void SettingsScene::UpdateUI(float deltaTime)
{
	if (settings->NetSolution == NetworkSolution::Interpolation)
	{
		b1->SetActive(true);
		b2->SetActive(false);
	}
	else
	{
		b1->SetActive(false);
		b2->SetActive(true);
	}

	for (auto& b : m_pointButtons)
	{
		if (b->GetTitle() == to_string(settings->WinningScore))
		{
			b->SetActive(false);
		}
		else
		{
			b->SetActive(true);
		}
	}

	for (auto& b : m_latencyButtons)
	{
		if (b->GetTitle() == to_string(settings->Latency))
		{
			b->SetActive(false);
		}
		else
		{
			b->SetActive(true);
		}
	}

	m_currentTime += deltaTime;

	if (m_currentTime >= m_updateListsTime)
	{
		ThreadPool::GetInstance()->AddJob(bind(&APIHandler::checkInPlayer, APIHandler::GetInstance()));
		m_currentTime = 0.0f;
	}
}

SettingsScene::SettingsScene() : Scene("SETTINGS")
{
	settings = Settings::getInstance();

	b1 = new Button(Vector2f(200, 100), "ClientPrediction");
	b2 = new Button(Vector2f(200, 170), "  Interpolation  ");

	b1->AddOnMouseDown(OnNetButton);
	b2->AddOnMouseDown(OnNetButton);


	for (int i = 0; i < 5; i++)
	{
		Button * b = new Button(Vector2f(100 + (75 * i), 400), to_string((i + 1) * 20));
		b->AddOnMouseDown(OnPointButton);
		m_pointButtons.push_back(b);
		m_gameObjects.push_back(b);
	}

	m_gameObjects.push_back(b1);
	m_gameObjects.push_back(b2);

	int values[4] = { 0, 50, 125, 250 };
	for (int i = 0; i < 4; i++)
	{
		Button * b = new Button(Vector2f(100 + (75 * i), 500), to_string(values[i]));
		b->AddOnMouseDown(OnLatencyButton);

		m_latencyButtons.push_back(b);
		m_gameObjects.push_back(b);
	}

	Button * back = new Button(Vector2f(750, 565), "Back");
	back->AddOnMouseDown(OnBackButtonSettings);

	m_gameObjects.push_back(back);
}

void SettingsScene::Update(float deltaTime)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Update(deltaTime);
	}

	UpdateUI(deltaTime);
}

void SettingsScene::Render(RenderWindow & r)
{
	for (auto & obj : m_gameObjects)
	{
		obj->Render(r);
	}
}

void SettingsScene::Destroy()
{
	Scene::Destroy();
}

void SettingsScene::Enter()
{
}
