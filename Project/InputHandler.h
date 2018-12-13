#pragma once
#include "SDL.h"

class Vector2D;
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};
class InputHandler
{
public:
	const Uint8* m_keystates;
	static InputHandler* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	bool isKeyDown(SDL_Scancode key);
	void update();
	void clean();  // 디바이스 관련 초기화된 부분을 clear 
	Vector2D* m_mousePosition;
	bool getMouseButtonState(int buttonNumber);
	Vector2D*  getMousePosition();
	void reset();
private:					
	InputHandler();
	~InputHandler() {}
	static InputHandler* s_pInstance;
};


typedef InputHandler TheInputHandler;
