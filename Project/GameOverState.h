#pragma once
#include"GameState.h"
class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }
	static GameOverState * Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}
private:
	static const std::string s_gameOverID;
	static GameOverState* s_pInstance;
	static void s_gameOverToMain();
	static void s_restartPlay();
	static void s_exitFromMenu();
};
typedef GameOverState GameOverState;