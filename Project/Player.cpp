#include "Player.h"
#include "Game.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}
void Player::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}
void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput(); // add our function
	SDLGameObject::update();
}
void Player::clean()
{
}
void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 30;
	if (m_position.getY() <= 40) {
		m_velocity.setY(1);
	}
	else if (m_position.getY() >= 480) {
		m_velocity.setY(-1);
	}
	if (m_position.getX() <= 0) {
		m_velocity.setX(1);
	}
	else if (m_position.getX() >= 600) {
		m_velocity.setX(-1);
	}
}