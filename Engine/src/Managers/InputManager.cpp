	#include "InputManager.h"
   //#include "App.h"
   #include "Vector3.h"
InputManager::InputManager(App* app) : app_(app)
{
	for (int i = 0; i < mouseState_.size(); ++i) {
		mouseState_[i] = false;
	}
	clearState();
	keyboardState_ = SDL_GetKeyboardState(&numKeys_);
	lastKeyboardState_ = new Uint8[numKeys_];	///

}

void InputManager::update()
{
	clearState();
	// For later knowing if the mouse moved
	Vector2D tempMousePos = mousePos_;

	SDL_Event e;
	
	///
	for (int i = 0; i < numKeys_; ++i) {
		lastKeyboardState_[i] = keyboardState_[i];
	}

	while (SDL_PollEvent(&e)) 
	{
		switch (e.type) {
		case SDL_QUIT:
			app_->Exit();
			break;
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
}



InputManager::~InputManager()
{
	delete[] lastKeyboardState_;
}

void InputManager::clearState()
{
	mouseEvent_ = false;
	keyboardEvent_ = false;
	
}
