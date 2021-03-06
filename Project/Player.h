#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include <iostream>
#include <vector>
#include "Bullet.h"
class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	void handleInput();
	int speed = 3;
	int Tick = 1000;
	std::vector<Bullet*> m_Bullets;
};
