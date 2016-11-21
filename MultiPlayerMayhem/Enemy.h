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

		bool stopDrawing = false;
		int currentTick = 0;

	public:
		Enemy();
		~Enemy();

		void Render(RenderWindow & r) override;
		void Update(float deltaTime) override;
		void SetPosition(Vector2f pos) override;
		void Deserialize(vector<string> token);
};