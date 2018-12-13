#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include <iostream>
#include <map>
class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
};