#pragma once
#include "GameObject.h"
#include <iomanip>
#include <sstream>

class Countdown : public GameObject
{
private:
	bool m_isDone;
	float m_currentTime;
	float m_startTime;
	int m_precision;
public:
	Countdown() : m_isDone(true), m_currentTime(0.0f), m_startTime(9999.0f), m_precision(2) {};
	Countdown(float startTime) : m_isDone(true), m_currentTime(0.0f), m_startTime(startTime) {};
	~Countdown() {};
	// Resets and starts the countdown
	void Start() { m_currentTime = m_startTime; m_isDone = false; };
	void Stop() { m_isDone = true; };

	void Render(sf::RenderWindow & r) override {};
	void Update(float deltaTime) override 
	{ 
		m_currentTime = !m_isDone ? m_currentTime - deltaTime : m_currentTime;
		m_isDone = m_currentTime <= 0.0f ? true : false;
	};

	std::string CurrentTime() const
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(m_precision) << m_currentTime;
		return m_isDone ? "" : stream.str();
	}

	bool IsFinnished() const { return m_isDone; }
	void SetStartTime(float time) { m_startTime = time; }
	void SetPrecision(int p) { m_precision = p; }
};
