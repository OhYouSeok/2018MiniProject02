#pragma once
#include"GameState.h"
class Prologue : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_prologueID; }
	static  Prologue * Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new  Prologue();
		}
		return s_pInstance;
	}
private:
	static const std::string s_prologueID;
	static  Prologue* s_pInstance;
	static void s_menuToPlay();
};
typedef  Prologue  Prologue;