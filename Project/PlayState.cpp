#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameClearState.h"
#include "AnimatedGraphic.h"
#include "BulletManager.h"
#include "BossMonster.h"
#include "CollisionManager.h"
#include "WallManager.h"
const std::string PlayState::s_playID = "PLAY";
PlayState * PlayState::s_pInstance = 0;

void PlayState::update()
{
	CollisionManager::getInstance()->update();
	BulletManager::getInstance()->update();
	WallManager::getInstance()->update();
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	//{
	//	TheGame::Instance()->getStateMachine()->pushState(
	//		PauseState::Instance());
	//}
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	for (int x = 3; x <= 9; x++) {
		if (checkCollision(
			dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[x])))
		{
			TheGame::Instance()->getStateMachine()->pushState(
				new GameOverState());
		}
	}
		if (CollisionManager::getInstance()->Check == true) {
			TheGame::Instance()->getStateMachine()->changeState(
				new GameClearState());
			CollisionManager::getInstance()->Check = false;
		}
}

void PlayState::render()
{
	;	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	BulletManager::getInstance()->draw();
	WallManager::getInstance()->draw();
	TheTextureManager::Instance()->drawTTF("Timer", 300, 0, 50, 50, TheGame::Instance()->getRenderer());
}
bool PlayState::onEnter()
{
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
	if (!TheTextureManager::Instance()->load("assets/Player.png",
		"Player", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Enemy.png",
		"Enemy", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/BossMonster.png",
		"BossMonster", TheGame::Instance()->getRenderer())) {
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
	if (!TheTextureManager::Instance()->load("assets/hitPoint.png",
		"hitPoint", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/beam.png",
		"bullet", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (TTF_Init() != 0) {
		std::cout, "TTF_Init";
	}
	GameObject* GameBG = new AnimatedGraphic(
		new LoaderParams(0, 0, 640,520 , "GameBG"),2);
	GameObject* hitPoint = new Player(
		new LoaderParams(320, 450, 10, 10, "hitPoint"));
	GameObject* player = new Player(
		new LoaderParams(320, 450, 25, 35, "Player"));
	GameObject* enemy = new Enemy(
		new LoaderParams(120, 150, 19,19, "Enemy"));
	GameObject* enemy1 = new  Enemy(
		new LoaderParams(170, 150, 19, 19, "Enemy"));
	GameObject* enemy2 = new  Enemy(
		new LoaderParams(220, 150, 19, 19, "Enemy"));
	GameObject* enemy3 = new  Enemy(
		new LoaderParams(270, 150, 19, 19, "Enemy"));
	GameObject* enemy4 = new Enemy(
		new LoaderParams(320, 150, 19, 19, "Enemy"));
	GameObject* enemy5 = new  Enemy(
		new LoaderParams(370, 150, 19, 19, "Enemy"));
	GameObject* enemy6 = new  Enemy(
		new LoaderParams(420, 150, 19, 19, "Enemy"));
	GameObject* enemy7 = new  Enemy(
		new LoaderParams(470, 150, 19, 19, "Enemy"));
	GameObject* UI = new AnimatedGraphic(
		new LoaderParams(0, 0, 640, 40, "UI"),2);
	m_gameObjects.push_back(GameBG);
	m_gameObjects.push_back(hitPoint);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy1);
	m_gameObjects.push_back(enemy2);
	m_gameObjects.push_back(enemy3);
	m_gameObjects.push_back(enemy4);
	m_gameObjects.push_back(enemy5);
	m_gameObjects.push_back(enemy6);
	m_gameObjects.push_back(enemy7);
	m_gameObjects.push_back(UI);
	WallManager::getInstance()->PushBackWall(new BossMonster(new LoaderParams(200, 40, 120, 120, "BossMonster")));
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
	TheTextureManager::Instance()->clearFromTextureMap("BossMonster");
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
