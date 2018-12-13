#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setY(2);
	m_velocity.setX(2);
}
void Enemy::draw()
{
	SDLGameObject::draw();
}
void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 2));
	if (m_position.getY() < 50) {
		m_velocity.setY(rand()%5);
	}
	else if (m_position.getY() > 470) {
		m_velocity.setY(-(rand() % 5));
	}
	if (m_position.getX() < 0) {
		m_velocity.setX(rand() % 5);
	}
	else if (m_position.getX() > 590) {
		m_velocity.setX(-(rand() % 5));
	}
	SDLGameObject::update();
}

void Enemy::clean() {

}