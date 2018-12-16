#pragma once
#include <vector>
#include "BossMonster.h"

class WallManager
{
public:
	static WallManager * getInstance();
	std::vector<BossMonster*> getWalls() const;
	void PushBackWall(BossMonster * BossMonster);
	void DeleteWall(BossMonster * a);
	void draw();

	void update();

	void clean();
private:

	WallManager() {}

	static WallManager * _instance;

	std::vector<BossMonster*> _Boss;

};