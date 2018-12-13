#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include <iostream>
#include <vector>
class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	void handleInput();
};
