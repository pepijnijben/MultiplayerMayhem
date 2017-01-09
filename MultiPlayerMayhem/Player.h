#pragma once
#include "GameObject.h"
#include "Line.h"

using namespace sf;
using namespace std;

class Player : public GameObject
{
private:
	Vector2f m_velocity;
	Vector2f m_angle;
	CircleShape m_shape;
	vector<Vector2f> m_tail;
	vector<vector<Line>> m_lines;

	bool m_isAlive;
	
	float MAX_VELOCITY = 40;
	float TURN_RATE = 2;
	
	int currentTime = 0; // in millisecs
	int stopDrawingAfter = 500;
	int nextStopDrawing;
	bool stopDrawing = false;
	int currentTick = 0;

	Vector2f normalize(const Vector2f& source);
	void setNewStopDrawingValues();
public:
	Player();
	~Player();

	void ResetPlayer();

	string Name;

	void Render(RenderWindow & r) override;
	void Update(float deltaTime) override;

	string Serialize();
	void Deserialize(vector<string> token);
	bool CollidedWith(Vector2f pos);
	bool IsAlive() { return m_isAlive; }
	void IsAlive(bool val) { m_isAlive = val; }
};