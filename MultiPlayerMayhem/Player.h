#pragma once
#include "GameObject.h"
#include "Line.h"
#include "Settings.h"
#include "Snapshot.h"

using namespace sf;
using namespace std;

class Player : public GameObject
{
private:
	Settings * settings;

	Vector2f m_velocity;
	Vector2f m_angle;
	CircleShape m_shape;
	vector<Vector2f> m_tail;
	vector<vector<Line>> m_lines;

	// Ghostobject values
	Vector2f m_ghostPosition;
	Vector2f m_ghostVelocity;
	bool m_ghostDrawing = false;

	bool m_isAlive;
	
	float MAX_VELOCITY = 40;
	float TURN_RATE = 2;
	
	int currentTime = 0; // in millisecs
	float lastTimeSend = -500;
	int stopDrawingAfter = 500;
	int nextStopDrawing;
	bool stopDrawing = false;
	int currentTick = 0;

	Vector2f normalize(const Vector2f& source);
	float CalculateDistance(const Vector2f p1, const Vector2f p2);
	void setNewStopDrawingValues();
public:
	Player();
	~Player();

	void ResetPlayer();

	string Name;
	int Score;

	void Render(RenderWindow & r) override;
	void Update(float deltaTime) override;

	string Serialize(bool force = false);
	void Deserialize(vector<string> token);
	bool CollidedWith(Vector2f pos);
	bool CollidedWithItself();
	bool IsAlive() { return m_isAlive; }
	void IsAlive(bool val) { m_isAlive = val; }
	sf::Color GetColor() { return m_shape.getFillColor(); }
};