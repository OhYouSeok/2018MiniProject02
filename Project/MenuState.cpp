#include "MenuState.h"
#include "Player.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"


const std::string MenuState::s_menuID = "MENU";
MenuState * MenuState::s_pInstance = 0;

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
void MenuState::s_menuToPlay()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(
		new PlayState());

}

void MenuState::s_exitFromMenu()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->Quit();
}
bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/Start.png",
		"playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Quit.png",
		"exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/MainBG.png",
		"MainBG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* MainBG = new AnimatedGraphic(new LoaderParams(0, 0, 640, 520,"MainBG"), 2);
	GameObject* button1 = new MenuButton(
		new LoaderParams(240, 270,145 , 50, "playbutton"),
		s_menuToPlay);

	GameObject* button2 = new MenuButton(
		new LoaderParams(240, 350, 145, 50, "exitbutton"),
		s_exitFromMenu);
	m_gameObjects.push_back(MainBG);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("exitbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("MainBG");
	std::cout << "exiting MenuState\n";
	return true;
}