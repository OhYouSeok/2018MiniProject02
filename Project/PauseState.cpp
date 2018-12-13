#include "PauseState.h"
#include "GameObject.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

const std::string PauseState::s_pauseID = "PAUSE";
PauseState * PauseState::s_pInstance = 0;

void PauseState::s_pauseToMain()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	TheGame::Instance()->getStateMachine()->changeState(
		new MenuState());
}

void PauseState::s_resumePlay()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	Mix_ResumeMusic();
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/RESUME.png",
		"resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/MENU.png",
		"mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/PauseBG.png",
		"PauseBG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* gamePause = new AnimatedGraphic(
		new  LoaderParams(0, 0, 640, 520, "PauseBG"), 2);
	GameObject* button1 = new MenuButton(new
		LoaderParams(240, 380, 145, 50, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new
		LoaderParams(240, 300, 145, 50, "resumebutton"), s_resumePlay);
	m_gameObjects.push_back(gamePause);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("PauseBG");
	TheInputHandler::Instance()->reset();
	std::cout << "exiting PauseState\n";
	return true;
}
