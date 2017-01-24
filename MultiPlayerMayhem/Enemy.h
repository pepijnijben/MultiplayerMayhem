#pragma once
#include "GameObject.h"
#include "Line.h"
#include "Settings.h"
#include "Snapshot.h"

using namespace sf;
using namespace std;

class Enemy : public GameObject 
{
	private:
		Settings * settings;
		vector<Snapshot> m_snapshots;
		
		CircleShape m_shape;
		vector<Vector2f> m_tail;
		vector<vector<Line>> m_lines;

		bool m_isAlive;
		Vector2f m_velocity;

		Vector2f m_desPosition;
		float fraction = 1;

		bool stopDrawing = false;
		int currentTick = 0;
		void CheckVelocity();
	public:
		string Name;
		int Score;
		float GameTime;

		Enemy();
		~Enemy();

		void Render(RenderWindow & r) override;
		void Update(float deltaTime) override;
		void Deserialize(vector<string> token, bool reset);
		bool CollidedWith(Vector2f pos);
		bool CollidedWithItself();
		void ResetEnemy();
		bool IsAlive() { return m_isAlive; }
		void IsAlive(bool val) { m_isAlive = val; }
		sf::Color GetColor() { return m_shape.getFillColor(); }
};