#pragma once
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"

Game * Game::s_pInstance = 0;
Game::Game() {};
bool Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, fullscreen);
		renderer = SDL_CreateRenderer(window, -1, 0);
		m_bRunning = true;
		SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
		m_pGameStateMachine = new GameStateMachine();
		m_pGameStateMachine->changeState(MenuState::Instance());
		return true;
	}
	else {
		return false;
	}


}
void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(PlayState::Instance());
	}
}

void Game::update() {
	m_pGameStateMachine->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TheInputHandler::Instance()->clean();
	Mix_CloseAudio();
	TTF_Quit();
}

void Game::Quit() {
	m_bRunning = false;
	TTF_Quit();
	Mix_CloseAudio();
}

