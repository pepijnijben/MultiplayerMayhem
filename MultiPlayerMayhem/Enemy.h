#pragma once
#include "GameObject.h"

using namespace sf;
using namespace std;

class Enemy : public GameObject 
{
	private:
		CircleShape m_shape;
		vector<Vector2f> m_tail;

	public:
		Enemy();
		~Enemy();

		void Render(RenderWindow & r) override;
		void Update(float deltaTime) override;
		void SetPosition(Vector2f pos) override;
		void Deserialize(string message);
};