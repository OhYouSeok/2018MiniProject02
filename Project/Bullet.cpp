#include "Bullet.h"
#include "BulletManager.h"


Bullet::Bullet(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setY(-15);
}
void Bullet::draw()
{
	SDLGameObject::draw(); 
}
void Bullet::update()
{
	for(Bullet * bullet : BulletManager::getInstance()->getBullets()){
	if (m_position.getY() <= 50) {
		BulletManager::getInstance()->DeleteBullet(bullet);
	}
	}
	SDLGameObject::update();
}

void Bullet::clean()
{
}

void Bullet::handleInput() {
}

std::vector<Bullet*> Bullet::getBullets() const
{
	return _bullets;
}


