#include "CollisionManager.h"
#include "Bullet.h"
#include "BossMonster.h"
#include "WallManager.h"
#include "BulletManager.h"
#include "Game.h"
#include "GameClearState.h"
#include <vector>

CollisionManager * CollisionManager::_instance = nullptr;

CollisionManager * CollisionManager::getInstance()
{
	if (!_instance)
		_instance = new CollisionManager;
	return _instance;
}

void CollisionManager::update()
{
	SDL_Point bulletPoint;
	for (BossMonster * BossMonster : WallManager::getInstance()->getWalls())
	{
		for (Bullet * bullet : BulletManager::getInstance()->getBullets())
		{
			bulletPoint.x = bullet->getRect().x;
			bulletPoint.y = bullet->getRect().y;
			if (SDL_PointInRect(&bulletPoint, &BossMonster->getRect()))
			{
				BulletManager::getInstance()->DeleteBullet(bullet);
				BossMonster->check = true;
				BossMonster->HP--;
				std::string leftHP = std::to_string(BossMonster->HP);
				if (!TheTextureManager::Instance()->loadTTF("assets/a.ttf", "Timer", leftHP, TheGame::Instance()->getRenderer(), 255, 122, 165))
				{
				}
				if (BossMonster->HP <= 1) {
					WallManager::getInstance()->DeleteWall(BossMonster);
					Check = true;
				}
			}
		}
	}
}