#include "BossMonster.h"
#include "Game.h"

const unsigned int _INTERVAL = 1000;
unsigned int last_time = 0;

BossMonster::BossMonster(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	HP = 51;
	//m_velocity.setY(2);
	m_velocity.setX(3);
}
void BossMonster::draw()
{
	SDLGameObject::draw();
}
void BossMonster::update()
{
	if (check == true) {
		if (!TheTextureManager::Instance()->load("assets/BossMonster_Damaged.png",
			"BossMonster", TheGame::Instance()->getRenderer())) {
		}
		if (last_time + _INTERVAL <= SDL_GetTicks())
		{
			last_time = SDL_GetTicks();
			check = false;
		}
	}
	else {
		if (!TheTextureManager::Instance()->load("assets/BossMonster.png",
			"BossMonster", TheGame::Instance()->getRenderer())) {
		}
	}
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	if (m_position.getX() < 10) {
		m_velocity.setX(rand() % 6);
	}
	else if (m_position.getX() > 530) {
		m_velocity.setX(-(rand() % 6));
	}
	SDLGameObject::update();
}

void BossMonster::clean() {

}

std::vector<BossMonster*> BossMonster::getWalls() const

{

	return _Boss;

}