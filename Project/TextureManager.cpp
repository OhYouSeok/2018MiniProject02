#include "TextureManager.h"

TextureManager* TextureManager::pInstance = 0;

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer*pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer*pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_TextureMap.erase(id);
}

bool TextureManager::load(std::string fileName, std::string ID, SDL_Renderer * renderer) {
	SDL_Surface * pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		return false;
	}

	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_TextureMap[ID] = pTexture;
		return true;
	}
	else {
		return false;
	}
}
bool TextureManager::loadTTF(std::string fileName, std::string ID, std::string talk, SDL_Renderer * renderer,int R,int G,int B) {
	TTF_Font * font = TTF_OpenFont(fileName.c_str(), 25);
	SDL_Color color = { R, G, B };
	SDL_Surface * surface = TTF_RenderText_Solid(font, talk.c_str(), color);
	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_TextureMap[ID] = pTexture;
	return true;
}
void TextureManager::drawTTF(std::string ID, int x, int y, int width, int height, SDL_Renderer * renderer) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(renderer, m_TextureMap[ID], &srcRect, &destRect);
	SDL_RenderPresent(renderer);
}

