#pragma once
#include "GameState.h"
#include "SDLGameObject.h"

class PlayState : public GameState
{
public:
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }
	static PlayState * Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}
	int start;
private:
	int b;
	int a = 60;
	static const std::string s_playID;
	static PlayState* s_pInstance;
	std::vector<GameObject*> m_gameObjects;
};
typedef PlayState PlayState;