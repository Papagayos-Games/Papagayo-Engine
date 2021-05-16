#include "InputSystem.h"

#include <iostream>

#include "SDL.h"
#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include <SDL_gamecontroller.h>
#include <SDL_events.h>

InputSystem* InputSystem::instance_ = nullptr;

InputSystem::InputSystem()
{
}

/*void InputSystem::update()
{
	clearState();
	// For later knowing if the mouse moved
	SDL_Event e;

	///
	for (int i = 0; i < numKeys_; ++i) {
		lastKeyboardState_[i] = keyboardState_[i];
	}

	while (SDL_PollEvent(&e))
	{
		switch (e.type) {
		case SDL_KEYDOWN:
			keyboardEvent_ = true;
			if (read)
			{
				lstKey = e.key.keysym.scancode;

			}
			break;
		case SDL_KEYUP:

			keyboardEvent_ = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseEvent_ = true;
			onMouseChange(e, true);
			break;
		case SDL_MOUSEBUTTONUP:
			mouseEvent_ = true;
			onMouseChange(e, false);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(e);
			break;
		}
	}

	// After mouse has updated its position, update the mouse movement
	mouseMovementInFrame_ = mousePos_ - tempMousePos;
}*/



InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::getInstance()
{
	return instance_;
}

bool InputSystem::setUpInstance() {
	if (instance_ == nullptr)
		instance_ = new InputSystem();
	return true;
}

void InputSystem::clean()
{
}

void InputSystem::destroy()
{
	instance_->clean();
	delete instance_;
}

bool InputSystem::handleInput(const SDL_Event& e)
{
    switch(e.type){
		case SDL_KEYDOWN:
			lstKey = e.key.keysym.scancode;
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				clickEvent_ = 1;
			}
			if (e.button.button == SDL_BUTTON_RIGHT) {
				clickEvent_ = 2;
			}
			break;
		case SDL_MOUSEBUTTONUP:
				clickEvent_ = 0;
			break;
		case SDL_QUIT:
			return false;
			break;
		default:
                break;
		
	}

	return true;
}

bool InputSystem::isKeyDownTest(int key)const {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	int pressed = 0;
	return keystate[SDL_Scancode(key)] == true;
}

bool InputSystem::isKeyDown(SDL_Keycode key) const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	return state[SDL_Scancode(key)] == true;
}

bool InputSystem::isKeyUp(SDL_Keycode key) const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	return state[SDL_Scancode(key)] == false;
}

int InputSystem::clickEvent() const
{
	return clickEvent_;
}

void InputSystem::onMouseMotion(SDL_Event& e) const
{
}
