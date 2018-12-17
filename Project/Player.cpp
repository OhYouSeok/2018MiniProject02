#include "Player.h"
#include "Game.h"
#include "BulletManager.h"

const unsigned int BULLET_INTERVAL = 700;
unsigned int last_bullet_time = 0;

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
	if (m_position.getY() <= 170) {
		m_position.setY(171);
	}
	else if (m_position.getY() >= 480) {
		m_position.setY(479);
	}
	if (m_position.getX() <= 0) {
		m_position.setX(1);
	}
	else if (m_position.getX() >= 600) {
		m_position.setX(599);
	}
}
void Player::clean()
{
}
void Player::handleInput()
{
	//Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = *target - m_position;
	//m_velocity /= 30;
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		m_velocity.setX(-speed);
		m_velocity.setY(-speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		m_velocity.setX(-speed);
		m_velocity.setY(speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		m_velocity.setX(speed);
		m_velocity.setY(speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		m_velocity.setX(speed);
		m_velocity.setY(-speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-speed);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		m_velocity.setX(-speed);
		m_velocity.setY(-speed);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {

		if (last_bullet_time + BULLET_INTERVAL <= SDL_GetTicks())
		{
			last_bullet_time = SDL_GetTicks();
			BulletManager::getInstance()->PushBackBullet(new Bullet(new LoaderParams(m_position.getX()+5, m_position.getY()-15, 10, 30, "bullet")));
			Mix_Chunk * ButtonS = Mix_LoadWAV("assets/shoot.wav");
			Mix_PlayChannel(-1, ButtonS, 0);
		}
	}
}