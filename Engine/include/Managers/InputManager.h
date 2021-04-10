#pragma once
#include "SDL.h"
#include <array>
#include <memory>
#include <vector>
#include <SDL_gamecontroller.h>
#include <iostream>
//class App;
class Vector3;
class InputManager
{
public:
	enum MouseButton : Uint8 {
		Left = 0,
		Right = 1,
		Middle = 2
	};
	
	InputManager(App* app);
	InputManager(InputManager&) = delete;
	InputManager& operator= (InputManager&) = delete;

	void update();

	// Keyboard
	inline bool isKeyUp(SDL_Scancode code) {
		return keyboardState_[code] == 0;
	};
	inline bool isKeyUp(SDL_Keycode code) {
		return isKeyUp(SDL_GetScancodeFromKey(code));
	};
	inline bool isKeyDown(SDL_Scancode code) {
		return keyboardState_[code] == 1;
	};
	inline bool isKeyDown(SDL_Keycode code) {
		return isKeyDown(SDL_GetScancodeFromKey(code));
	};
	inline bool KeyPressed(SDL_Scancode code) {
		return lastKeyboardState_[code] == 0 && keyboardState_[code] == 1;
	};
	inline bool KeyPressed(SDL_Keycode code) {
		return KeyPressed(SDL_GetScancodeFromKey(code));
	}
	// if pressed or released a key this frame
	inline bool keyboardEvent() {
		return keyboardEvent_;
	}

	// Mouse
	inline bool isMouseButtonPressed(MouseButton button) {
		return mouseState_[button];
	};
	inline double getMousePosX() {
		return mousePos_.getX();
	};
	inline double getMousePosY() {
		return mousePos_.getY();
	};
	inline const Vector2D& getMousePos() {
		return mousePos_;
	};
	inline const Vector2D& getMouseMovement() {
		return mouseMovementInFrame_;
	}
	// if pressed or released a mouse button this frame
	inline bool mouseEvent() {
		return mouseEvent_;
	}

	

	void readKey() { read = true; }
	bool reading() { return read; }
	SDL_Scancode lastKey()
	{
		return lstKey;
	};

	virtual ~InputManager();
	
private:
	void clearState();

	inline void onMouseMotion(SDL_Event& e) {
		mousePos_.set(e.motion.x, e.motion.y);
	};


	void onMouseChange(SDL_Event& e, bool state) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			mouseState_[Left] = state;
		}
		else if (e.button.button == SDL_BUTTON_MIDDLE) {
			mouseState_[Middle] = state;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			mouseState_[Right] = state;
		}
	};

	App* app_;
	const Uint8* keyboardState_;
	Uint8* lastKeyboardState_;
	int numKeys_;
	Vector2D mousePos_;
	std::array<bool, 3> mouseState_; // true = pressed
	Vector2D mouseMovementInFrame_;
	
	// if in this frame there has been an event
	bool mouseEvent_ = false; // click
	bool keyboardEvent_ = false; // press
	bool read = false;
	SDL_Scancode lstKey;
};