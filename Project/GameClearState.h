#pragma once
#include "GameState.h"

class GameObject;

class GameClearState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameClearID; }
private:
	static void s_gameClearToMain();
	static const std::string s_gameClearID;
	std::vector<GameObject*> m_gameObjects;
};