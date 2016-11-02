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
	
	float MAX_VELOCITY = 50;
	float TURN_RATE = 2;

	Vector2f normalize(const Vector2f& source);
public:
	Player();
	~Player();

	void Render(RenderWindow & r);
	void Update(float deltaTime);
};