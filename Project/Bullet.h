#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include <iostream>
#include <vector>
class Bullet : public SDLGameObject
{
public:
	virtual void draw();
	virtual void update();
	virtual void clean();
	Bullet(const LoaderParams* pParams);
	std::vector<Bullet*> getBullets() const;
private:
	void handleInput();
	std::vector<Bullet*> _bullets;
};