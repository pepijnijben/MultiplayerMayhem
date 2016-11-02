#pragma once
#include "GameObject.h"

using namespace sf;
using namespace std;

class Player : public GameObject
{
private:
	Vector2f m_velocity;
	Vector2f m_angle;
	CircleShape m_shape;
	vector<Vector2f> m_tail;
	vector<Vertex> m_tail2;
	
	float MAX_VELOCITY = 40;
	float TURN_RATE = 2;
	
	int currentTime = 0; // in millisecs
	int stopDrawingAfter = 500;
	int nextStopDrawing;

	Vector2f normalize(const Vector2f& source);
	void setNewStopDrawingValues();
public:
	Player();
	~Player();

	void Render(RenderWindow & r);
	void Update(float deltaTime);
};