#include "Prologue.h"
#include "Player.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"

const std::string Prologue::s_prologueID = "PROLOGUE";
Prologue * Prologue::s_pInstance = 0;

void Prologue::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void Prologue::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
void Prologue::s_menuToPlay()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(
		new PlayState());

}

bool Prologue::onEnter()
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
	if (!TheTextureManager::Instance()->load("assets/PrologueBG.png",
		"PrologueBG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* MainBG = new AnimatedGraphic(new LoaderParams(0, 0, 640, 520, "PrologueBG"), 2);
	GameObject* button1 = new MenuButton(
		new LoaderParams(260, 370, 145, 50, "playbutton"),
		s_menuToPlay);

	m_gameObjects.push_back(MainBG);
	m_gameObjects.push_back(button1);
	std::cout << "entering PrologueState\n";
	return true;
}

bool Prologue::onExit()
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