#pragma once
#include "GameObject.h"
#include "Line.h"

using namespace sf;
using namespace std;

class Enemy : public GameObject 
{
	private:
		CircleShape m_shape;
		vector<Vector2f> m_tail;
		vector<vector<Line>> m_lines;

		bool m_isAlive;

		bool stopDrawing = false;
		int currentTick = 0;
	public:
		string Name;

		Enemy();
		~Enemy();

		void Render(RenderWindow & r) override;
		void Update(float deltaTime) override;
		void SetPosition(Vector2f pos) override;
		void Deserialize(vector<string> token);
		bool CollidedWith(Vector2f pos);
		void ResetEnemy();
		bool IsAlive() { return m_isAlive; }
		void IsAlive(bool val) { m_isAlive = val; }
};