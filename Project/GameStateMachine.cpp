#include "GameStateMachine.h"
#include <SDL_mixer.h>

void GameStateMachine::pushState(GameState *pState)
{
	/*m_gameStates.push_back(pState);*/
	m_prevState = m_currentState;
	m_currentState = pState;
	musicChanger();
	m_currentState->onEnter();
}

void GameStateMachine::popState()
{
	m_currentState = m_prevState;
}

void GameStateMachine::changeState(GameState *pState)
{
	if (pState != NULL)
	{
		if (m_currentState != NULL) {
			m_prevState = m_currentState;
			m_currentState->onExit();
		}
		m_currentState = pState;
		musicChanger();
		m_currentState->onEnter();
	}
}

void GameStateMachine::update()
{
	if (m_currentState != NULL)
		m_currentState->update();
}

void GameStateMachine::render()
{
	if (m_currentState != NULL)
		m_currentState->render();
}

void GameStateMachine::musicChanger() {
	if (m_currentState->getStateID() == "PLAY") {
			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
			Mix_Music *music = Mix_LoadMUS("assets/GameBGM.mp3");
			Mix_PlayMusic(music, -1);
	}
	else if (m_currentState->getStateID() == "GAMECLEAR") {
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music *music = Mix_LoadMUS("assets/ClearBGM.mp3");
		Mix_PlayMusic(music, -1);
	}
	else if (m_currentState->getStateID() == "MENU") {
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music *music = Mix_LoadMUS("assets/MainBGM.mp3");
		Mix_PlayMusic(music, -1);
	}
	else if (m_currentState->getStateID() == "GAMEOVER") {
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music *music = Mix_LoadMUS("assets/GameoverBGM.mp3");
		Mix_PlayMusic(music, -1);
	}
	else if (m_currentState->getStateID() == "PAUSE") {
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_PauseMusic();
	}
}