#include "GameScene.h"
#include "fstream"

bool GameScene::IsStarted = false;

void GameScene::ResetRound()
{
	m_deadPlayers.clear();
	m_deadPlayers.shrink_to_fit();

	for (auto & enemy : m_enemys)
	{
		enemy->ResetEnemy();
	}

	// Add values to csv vector
	data.push_back(net->PackagesSend);
	data.push_back(net->PackagesReceived);
	data.push_back(net->BytesSend);
	data.push_back(net->BytesReceived);
	data.push_back(roundTime);

	net->BytesReceived = 0;
	net->BytesSend = 0;
	net->PackagesReceived = 0;
	net->PackagesSend = 0;
	roundTime = 0.0f;
	
	m_player->ResetPlayer();
	net->Send(m_player->Serialize());
	m_counter->Start();
}

void GameScene::HandleMessages()
{
	// Send and Receive messages
	vector<string> messages = net->Receive();

	if (m_player->IsAlive())
	{
		net->Send(m_player->Serialize());
	}

	for (auto & s : messages)
	{
		if (s != "")
		{
			vector<string> values = DeserializeMessage(s);

			if (values[0] == "PLAYER")
			{
				if (m_player->Name == values[1])
				{
					m_player->Deserialize(values);
				}

				for (auto & enemy : m_enemys)
				{
					if (enemy->Name == values[1])
					{
						enemy->Deserialize(values, !m_counter->IsFinnished());
						break;
					}
				}
			}
			else if (values[0] == "GAME")
			{
				if (values[1] == "STARTED" && !IsStarted)
				{
					IsStarted = true;
					m_counter->SetStartTime(3.0f - (currentTime - stof(values[2])));
					m_counter->Start();
				}
				else if (values[1] == "RESET")
				{
					m_counter->SetStartTime(3.0f - (currentTime - stof(values[2])));
					ResetRound();
				}
				else if (values[1] == "SCENE")
				{
					// Save data to csv!
					ofstream myfile;
					time_t now = time(0);

					ostringstream ss;
					ss << "data-" << now << ".csv";
					myfile.open(ss.str());
					myfile << "PackageSend,PackageReceived,ByteSend,ByteReceived,roundTime\n";

					for (int i = 0; i < data.size(); i += 4)
					{
						myfile << data[i] << "," << data[i + 1] << "," << data[i + 2] << "," << data[i + 3] << "\n";
					}

					SceneManager::GetInstance()->SwitchTo(values[2]);
				}
				else if (values[1] == "TIME")
				{
					if (m_isHost)
					{
						for (int i = 0; i < 10; i++)
						{
							ostringstream ss;
							ss << "GAME;PING;" << values[2] << ";" << i << ";";
							m_pingmsg[values[2]][i] = currentTime;
							net->Send(ss.str(), values[2]);
						}

						net->Send(m_player->Serialize(true), values[2]);
					}
					else if (values[2] == m_player->Name)
					{
						currentTime = stof(values[3]);

						for (auto & enemy : m_enemys)
						{
							enemy->GameTime = currentTime;
						}
					}
				}
				else if (values[1] == "PING")
				{
					if (values[2] == m_player->Name)
					{
						ostringstream ss;
						ss << "GAME;PINGRETURNED;" << m_player->Name << ";" << values[3] << ";";
						net->Send(ss.str());
					}
				}
				else if (m_isHost && values[1] == "PINGRETURNED")
				{
					m_pingmsg[values[2]][stoi(values[3]) + 10] = currentTime;

					if (m_pingmsg[values[2]].size() >= 20)
					{
						float totalSum = 0;
						for (int i = 0; i < 10; i++)
						{
							totalSum += m_pingmsg[values[2]][i + 10] - m_pingmsg[values[2]][i];
						}

						ostringstream ss;
						ss << "GAME;TIME;" << values[2] << ";" << currentTime + ((totalSum / 10.0f) * 0.5f) << ";";
						net->Send(ss.str(), values[2]);
						
						m_pingmsg.erase(values[2]);
					}
				}
			}
		}
	}
}

void GameScene::HostOperations(float deltaTime)
{
	if (IsStarted && m_counter->IsFinnished())
	{
		for (auto& obj : m_gameObjects)
		{
			obj->Update(deltaTime);
		}

		// Authoritive host part
		if (m_isHost)
		{
			ostringstream ss;

			// Check if player is outside of the bounds
			if (m_player->IsAlive() && (m_player->GetPosition().x > 795 || m_player->GetPosition().x < 195 
				|| m_player->GetPosition().y < 5 || m_player->GetPosition().y > 595 
				|| m_player->CollidedWithItself()))
			{
				ss << "PLAYER;" << m_player->Name << ";DEAD;";
				net->Send(ss.str());
				m_player->IsAlive(false);
			}

			int playersAlive = m_player->IsAlive() ? 1 : 0;
			m_winner = m_player->IsAlive() ? m_player->Name : "";
			// Checkcollisions
			for (auto& e1 : m_enemys)
			{
				// Check if local player collided with e1
				if (m_player->IsAlive() && e1->CollidedWith(m_player->GetPosition()))
				{
					ss.str("");
					ss.clear();
					ss << "PLAYER;" << m_player->Name << ";DEAD;";
					net->Send(ss.str());
					m_player->IsAlive(false);
					m_deadPlayers.push_back(m_player->Name);
				}
				if (e1->IsAlive() && (m_player->CollidedWith(e1->GetPosition()) || e1->CollidedWithItself()))
				{
					ss.str("");
					ss.clear();
					ss << "PLAYER;" << e1->Name << ";DEAD;";
					net->Send(ss.str());
					e1->IsAlive(false);
					m_deadPlayers.push_back(e1->Name);
				}

				// Check against all other enemies
				for (auto& e2 : m_enemys)
				{
					if (e1->IsAlive() && e1->Name != e2->Name)
					{
						// if e1 collided with e2 he is dead
						if (e2->CollidedWith(e1->GetPosition()))
						{
							ss.str("");
							ss.clear();
							ss << "PLAYER;" << e1->Name << ";DEAD;";
							net->Send(ss.str());
							e1->IsAlive(false);
							m_deadPlayers.push_back(e1->Name);
							break;
						}
					}
				}

				if (e1->IsAlive())
				{
					// Check if player is outside of the bounds
					if (e1->GetPosition().x > 795 || e1->GetPosition().x < 195 || e1->GetPosition().y < 5 || e1->GetPosition().y > 595)
					{
						ss.str("");
						ss.clear();
						ss << "PLAYER;" << e1->Name << ";DEAD;";
						net->Send(ss.str());
						e1->IsAlive(false);
						m_deadPlayers.push_back(e1->Name);
					}
					else
					{
						m_winner = e1->Name;
						playersAlive++;
					}
				}

			} // End checkcollisions

			  // Round is over cuz one player won!
			if (playersAlive <= 1)
			{
				int highestScore = 0;
				ss.str("");
				ss.clear();

				ss << "GAME;RESET;" << currentTime << ";";
				net->Send(ss.str());

				// Send all losing players there points
				for (int i = 0; i < m_deadPlayers.size(); i++)
				{
					ss.str("");
					ss.clear();
					int points = ((i + 1) * 2) - 1;

					ss << "PLAYER;" << m_deadPlayers[i] << ";SCORE;" << points << ";";

					if (m_deadPlayers[i] == m_player->Name)
					{
						m_player->Score += points;
						highestScore = highestScore < m_player->Score ? m_player->Score : highestScore;
					}
					else
					{
						for (auto& e : m_enemys)
						{
							e->Name == m_deadPlayers[i] ? e->Score += points : e->Score;
							highestScore = highestScore < e->Score ? e->Score : highestScore;
						}
					}
					net->Send(ss.str());
				}

				ss.str("");
				ss.clear();
				int points = ((m_enemys.size() + 1) * 2) - 1;

				ss << "PLAYER;" << m_winner << ";SCORE;" << points << ";";
				net->Send(ss.str());


				// Send winner points
				if (m_player->Name == m_winner)
				{
					m_player->Score += points;
					highestScore = highestScore < m_player->Score ? m_player->Score : highestScore;
				}
				else
				{
					for (auto& e : m_enemys)
					{
						if (m_winner == e->Name)
						{
							e->Score += points;
							highestScore = highestScore < e->Score ? e->Score : highestScore;
							break;
						}
					}
				}				

				// check if no new round is required
				if (highestScore >= Settings::getInstance()->WinningScore)
				{
					// Save data to csv!
					ofstream myfile;
					time_t now = time(0);

					ostringstream ss;
					ss << "data-" << now << ".csv";
					myfile.open(ss.str());
					myfile << "PackageSend,PackageReceived,ByteSend,ByteReceived,roundTime\n";

					for (int i = 0; i < data.size(); i += 4)
					{
						myfile << data[i] << "," << data[i + 1] << "," << data[i + 2] << "," << data[i + 3] << "\n";
					}

					// Return to lobby
					net->Send("GAME;SCENE;ROOM;");
					SceneManager::GetInstance()->SwitchTo("ROOM");
				}

				ResetRound();
			}
		} // End Authoritive host
	} // End IsStarted
	else if (m_isHost)
	{
		if (m_pingmsg.size() <= 0 && !IsStarted)
		{
			ostringstream ss;
			ss << "GAME;STARTED;" << currentTime << ";";
			net->Send(ss.str());
			net->Send(m_player->Serialize());
			IsStarted = true;
			m_counter->Start();
		}
	}
}

GameScene::GameScene() : Scene("GAME")
{
	m_counter = new Countdown(3.0f);
	currentTime = 0.0f;
	net = Net::GetInstance();

	m_player = new Player();
	m_counter->SetPrecision(0);

	ui = new GameUI();
	settings = Settings::getInstance();
}

void GameScene::Update(float deltaTime)
{
	currentTime += deltaTime;
	roundTime += deltaTime;
	ui->Counter = m_counter->CurrentTime();

	HandleMessages();
	HostOperations(deltaTime);
	m_counter->Update(deltaTime);
	ui->Update(deltaTime);
}

void GameScene::Render(RenderWindow & r)
{
	for (auto& obj : m_gameObjects)
	{
		obj->Render(r);
	}

	ui->Render(r);
}

void GameScene::Destroy()
{
	// Takes care of destroying all the m_gameObjects
	Scene::Destroy();
}

void GameScene::Enter()
{
	m_isHost = APIHandler::GetInstance()->IsHost();

	m_deadPlayers.clear();
	m_deadPlayers.shrink_to_fit();
	m_enemys.clear();
	m_enemys.shrink_to_fit();
	m_gameObjects.clear();
	m_gameObjects.shrink_to_fit();

	data.clear();
	data.shrink_to_fit();
	roundTime = 0;

	m_gameObjects.push_back(m_player);
	m_player->Score = 0;
	m_player->ResetPlayer();
	m_player->Name = APIHandler::GetInstance()->GetName();
	vector<NetPlayer> enemys = APIHandler::GetInstance()->getRoomOtherPlayers();
	net->SetRemotePlayers(enemys);

	for (auto & enemy : enemys)
	{
		Enemy * m_enemy = new Enemy();
		m_enemy->Name = enemy.name;
		m_enemy->GameTime = currentTime;
		m_gameObjects.push_back(m_enemy);
		m_enemys.push_back(m_enemy);

		m_pingmsg[enemy.name] = map<int, float>();
	}

	ui->SetEnemies(m_enemys);
	ui->SetPlayer(m_player);

	if (m_isHost)
	{
		net->Send("GAME;STARTED;");
		cout << "Im the host" << endl;
	} 
	else
	{
		ostringstream ss;
		ss << "GAME;TIME;" << m_player->Name << ";";
		net->Send(ss.str());
	}

}

vector<string> GameScene::DeserializeMessage(string message)
{
	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;

	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	return token;
}
