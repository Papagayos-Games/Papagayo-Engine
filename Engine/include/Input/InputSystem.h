#pragma once

#ifndef _INPUTSYSTEM_H
#define _INPUTSYSTEM_H

#include "SDL_keycode.h"

union SDL_Event;

class InputSystem
{
public:
	/*enum MouseButton : Uint8 {
		Left = 0,
		Right = 1,
		Middle = 2
	};*/

	virtual ~InputSystem();
	static InputSystem* getInstance();
	static void clean();

	void handleInput();
	bool isKeyDown(SDL_Keycode key);
	bool isKeyUp(SDL_Keycode key);
	
private:
	InputSystem();
	static InputSystem* instance_;

	void onMouseMotion(SDL_Event& e);
	
	// if in this frame there has been an event
	bool mouseEvent_ = false; // click
	bool keyboardEvent_ = false; // press
	bool read = false;
};

#endif // !_INPUTSYSTEM_H