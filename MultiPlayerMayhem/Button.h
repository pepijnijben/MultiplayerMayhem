#pragma once
#include "GameObject.h"
#include <functional>

using namespace sf;
using namespace std;

class Button : public GameObject
{
private:
	bool m_isActive, m_isPressed, m_isVisible;
	Vector2f m_size;
	Text m_title;
	Font m_font;
	RectangleShape m_background;
	Vector2i m_mousePosition;

	// Callbacks
	vector<function<void(Button*)>> m_onMouseDown;
	vector<void*> m_onMouseUp;
	vector<function<void*(bool)>> m_onHover;
public:
	Button(Vector2f pos, string title);
	~Button() {};

	void Render(sf::RenderWindow & r) override;
	void Update(float deltaTime) override;

	bool IsActive() { return m_isActive; }
	bool IsPressed() { return m_isPressed; }
	bool IsVisible() { return m_isVisible; }

	void SetActive(bool active) 
	{ 
		Color c	= m_background.getFillColor();
		c.a = active ? 255 : 128;
		m_background.setFillColor(c);

		m_isActive = active; 
	}
	void SetVisible(bool visible) { m_isVisible = visible; }
	string GetTitle() { return m_title.getString(); }
	
	// Add callbacks
	template<typename Function>
	void AddOnMouseDown(Function && cb) { m_onMouseDown.push_back(forward<Function>(cb)); };
	void AddOnMouseUp(void *cb()) { m_onMouseUp.push_back(cb); };
	//void AddOnHover(function<void*(bool)> cb) { m_onHover.push_back(cb); };

	// Remove callbacks
	/*bool RemoveOnMouseDown(void* cb)
	{
		for (vector<void*>::iterator i = m_onMouseDown.begin(); i != m_onMouseDown.end(); i++) {
			if (cb == *i)
			{
				m_onMouseDown.erase(i);
				return true;
			}
		}

		return false;
	};*/

	bool RemoveOnMouseUp(void* cb)
	{
		for (vector<void*>::iterator i = m_onMouseUp.begin(); i != m_onMouseUp.end(); i++) {
			if (cb == *i)
			{
				m_onMouseUp.erase(i);
				return true;
			}
		}

		return false;
	}
};