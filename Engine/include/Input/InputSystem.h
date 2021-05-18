#pragma once

#ifndef _INPUTSYSTEM_H
#define _INPUTSYSTEM_H

#include "SDL_keycode.h"

union SDL_Event;

struct Vector2
{
	int x, y;
};

class InputSystem
{
public:
	/*enum MouseButton : Uint8 {
		Left = 0,
		Right = 1,
		Middle = 2
	};*/

	static InputSystem* getInstance();
	static bool setUpInstance();
	static void clean();
	static void destroy();

	bool handleInput(const SDL_Event& e);
	bool isKeyDown(SDL_Keycode key) const;
	bool isKeyDownTest(int key)const;
	bool isKeyUp(SDL_Keycode key) const;

	int clickEvent()const;
	int getMouseX()const { return mousePos.x; };
	int getMouseY()const { return mousePos.y; };

	SDL_Scancode lastKey()
	{
		return lstKey;
	}
	
private:
	InputSystem();
	virtual ~InputSystem();
	static InputSystem* instance_;

	void onMouseMotion(SDL_Event& e) const;
	
	// if in this frame there has been an event
	int clickEvent_ = 0; // 1 Left, 2 Right
	bool keyboardEvent_ = false; // press
	bool read = false;
	SDL_Scancode lstKey;
	Vector2 mousePos;
};

#endif // !_INPUTSYSTEM_H