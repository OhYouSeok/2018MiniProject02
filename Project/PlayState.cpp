#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameClearState.h"
#include "AnimatedGraphic.h"

const std::string PlayState::s_playID = "PLAY";
PlayState * PlayState::s_pInstance = 0;

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(
			PauseState::Instance());
	}
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	for (int x = 2; x <= 11; x++) {
		if (checkCollision(
			dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[x])))
		{
			TheGame::Instance()->getStateMachine()->pushState(
				new GameOverState());
		}
	}
	b = a - ((SDL_GetTicks() - start) / 1000);
	if (b <= 0) {
		TheGame::Instance()->getStateMachine()->pushState(new GameClearState());
	}
}

void PlayState::render()
{
	std::string leftTime = std::to_string(b);
	if (!TheTextureManager::Instance()->loadTTF("assets/a.ttf", "Timer", leftTime, TheGame::Instance()->getRenderer(),255,122,165))
	{
	}
	;	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	TheTextureManager::Instance()->drawTTF("Timer", 300, 0, 50, 50, TheGame::Instance()->getRenderer());
}
bool PlayState::onEnter()
{
	start = SDL_GetTicks();
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
	if (!TheTextureManager::Instance()->load("assets/Player.png",
		"Player", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Enemy.png",
		"Enemy", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/UI.png",
		"UI", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/GameBG.png",
		"GameBG", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (TTF_Init() != 0) {
		std::cout, "TTF_Init";
	}
	GameObject* GameBG = new AnimatedGraphic(
		new LoaderParams(0, 0, 640,520 , "GameBG"),2);
	GameObject* player = new Player(
		new LoaderParams(320, 240, 28, 26, "Player"));
	GameObject* enemy = new Enemy(
		new LoaderParams(50, 50, 19,19, "Enemy"));
	GameObject* enemy2 = new Enemy(
		new LoaderParams(250, 50, 19, 19, "Enemy"));
	GameObject* enemy3 = new Enemy(
		new LoaderParams(450, 50, 19, 19, "Enemy"));
	GameObject* enemy4 = new Enemy(
		new LoaderParams(50, 50, 19, 19, "Enemy"));
	GameObject* enemy5 = new Enemy(
		new LoaderParams(50, 250, 19, 19, "Enemy"));
	GameObject* enemy6 = new Enemy(
		new LoaderParams(50, 450, 19, 19, "Enemy"));
	GameObject* enemy7 = new Enemy(
		new LoaderParams(450, 50, 19, 19, "Enemy"));
	GameObject* enemy8 = new Enemy(
		new LoaderParams(450, 250, 19, 19, "Enemy"));
	GameObject* enemy9 = new Enemy(
		new LoaderParams(450, 450, 19, 19, "Enemy"));
	GameObject* enemy10 = new Enemy(
		new LoaderParams(150, 450, 19, 19, "Enemy"));
	GameObject* enemy11 = new Enemy(
		new LoaderParams(350, 450, 19, 19, "Enemy"));
	GameObject* UI = new AnimatedGraphic(
		new LoaderParams(0, 0, 640, 40, "UI"),2);
	m_gameObjects.push_back(GameBG);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);
	m_gameObjects.push_back(enemy2);
	m_gameObjects.push_back(enemy3);
	m_gameObjects.push_back(enemy4);
	m_gameObjects.push_back(enemy5);
	m_gameObjects.push_back(enemy6);
	m_gameObjects.push_back(enemy8);
	m_gameObjects.push_back(enemy9);
	m_gameObjects.push_back(enemy10);
	m_gameObjects.push_back(enemy11);
	m_gameObjects.push_back(UI);
	std::cout << "entering PlayState\n";
	return true;
}
bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("Player");
	TheTextureManager::Instance()->clearFromTextureMap("Enemy");
	TheTextureManager::Instance()->clearFromTextureMap("Timer");
	TheTextureManager::Instance()->clearFromTextureMap("UI");
	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	p1->getRect();
	p2->getRect();
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}
