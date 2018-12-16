#include "WallManager.h"
#include "BossMonster.h"

WallManager * WallManager::_instance = nullptr;

WallManager * WallManager::getInstance()

{

	if (!_instance)

		_instance = new WallManager;



	return _instance;

}

void WallManager::PushBackWall(BossMonster * BossMonster)

{
	_Boss.push_back(BossMonster);

}



void WallManager::DeleteWall(BossMonster * a)
{

	for (std::vector<BossMonster*>::iterator iter = _Boss.begin();
		iter != _Boss.end(); iter++)
	{
		if ((*iter) == a)
		{
			_Boss.erase(iter);
			return;
		}
	}
}

void WallManager::draw()

{

	for (BossMonster * iter : _Boss)

		iter->draw();

}



void WallManager::update()

{

	for (BossMonster * iter : _Boss)

		iter->update();

}



void WallManager::clean()

{

	for (BossMonster * iter : _Boss)

		iter->clean();

}

std::vector<BossMonster*> WallManager::getWalls() const

{

	return _Boss;

}