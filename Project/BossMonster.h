#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include <iostream>
#include <Vector>
class BossMonster : public SDLGameObject
{
public:
	BossMonster(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	bool check=false;
	int HP;
	std::vector<BossMonster*> getWalls() const;
private:
	std::vector<BossMonster*> _Boss;
};