#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";


void GameOverState::s_gameOverToMain()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	TheGame::Instance()->getStateMachine()->changeState(
		new MenuState());
}
void GameOverState::s_restartPlay()
{
	Mix_Chunk * ButtonS = Mix_LoadWAV("assets/selection.wav");
	Mix_PlayChannel(-1, ButtonS, 0);
	TheGame::Instance()->getStateMachine()->changeState(
		new PlayState());
}

bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/Menu.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Retry.png",
		"restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/OverBG.png",
		"OverBG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* gameOver = new AnimatedGraphic(
		new  LoaderParams(0, 0,640, 520, "OverBG"), 2);

	GameObject* button1 = new MenuButton(
		new LoaderParams(240, 380, 145,50, "mainbutton"),
		s_gameOverToMain);
	GameObject* button2 = new MenuButton(
		new LoaderParams(240, 300, 145, 50, "restartbutton"),
		s_restartPlay);
	m_gameObjects.push_back(gameOver);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}

void GameOverState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void GameOverState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
bool GameOverState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("OverBG");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("restartbutton");
	std::cout << "exiting GameOverState\n";
	return true;
}