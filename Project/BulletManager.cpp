#include "BulletManager.h"



BulletManager * BulletManager::_instance = nullptr;



BulletManager * BulletManager::getInstance()
{
	if (!_instance)
		_instance = new BulletManager;
	return _instance;
}

void BulletManager::draw()
{
	for (Bullet * iter : _bullets) {
		iter->draw();
	}
}


void BulletManager::update()
{
	for (Bullet * iter : _bullets)
		iter->update();
}



void BulletManager::clean()
{
	for (Bullet * iter : _bullets)
		iter->clean();
}

void BulletManager::PushBackBullet(Bullet * bullet)
{
	_bullets.push_back(bullet);
}



void BulletManager::DeleteBullet(Bullet * bullet)
{

	for (std::vector<Bullet*>::iterator iter = _bullets.begin();
		iter != _bullets.end(); iter++)
	{
		if ((*iter) == bullet)
		{
			_bullets.erase(iter);
			return;
		}
	}
}

std::vector<Bullet*> BulletManager::getBullets() const
{
	return _bullets;
}