#pragma once
#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams),m_position(pParams->getX(),pParams->getY()),m_velocity(0.0f,0.0f),m_acceleration(0.0f,0.0f)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 0;
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else {
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}

SDL_Rect SDLGameObject::getRect() 
{
	SDL_Rect rect;
	rect.x = (int)m_position.getX();
	rect.y = (int)m_position.getY();
	rect.w = rect.x + m_width;
	rect.h = rect.y + m_height;
    return rect;

}
void SDLGameObject::update() {
	m_velocity += m_acceleration;
	m_position += m_velocity;
}
std::string SDLGameObject::getTextureID() const

{
	return m_textureID;
}

void SDLGameObject::clean() {

}

Vector2D SDLGameObject::getPosition() {
	return m_position;
}

int SDLGameObject::getHeight() {
	return m_height;
}

int SDLGameObject::getWidth() {
	return m_width;
}