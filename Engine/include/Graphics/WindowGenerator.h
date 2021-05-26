#pragma once

#ifndef _GRAPHICS_WINDGENLIST_H
#define _GRAPHICS_WINDGENLIST_H

#include "OgreFrameListener.h"
#ifdef _DEBUG
//#include "checkML.h"
#endif

namespace Ogre {
	class OgreRenderWindow;
	class OgreRenderSystem;
	class Root;
}

class SDL_Window;

class WindowGenerator : public Ogre::FrameListener
{
private:
	//Singleton
	static WindowGenerator* instance_;
	WindowGenerator(Ogre::Root* root, const std::string& name);

	Ogre::RenderWindow* renderWindow_;
	Ogre::Root* mRoot_;
	//Ogre::RenderSystem* renderSystem_;

	SDL_Window* sdlWindow_;
	uint32_t winWidth_, winHeight_;

	void initWindow(std::string name);

public:
	//Singleton, init y get separados
	static WindowGenerator* getInstance();
	static bool setupInstance(Ogre::Root* root, const std::string& name);
	static void clean();

	virtual ~WindowGenerator();

	//Getters
	Ogre::RenderWindow* getRenderWindow();
	Ogre::RenderWindow* getRenderWindow() const;
	inline Ogre::RenderSystem* getRenderSystem();
	inline Ogre::RenderSystem* getRenderSystem() const;
	SDL_Window* getSDLWindow();
	SDL_Window* getSDLWindow() const;

	uint32_t getWindowWidth()const;
	uint32_t getWindowHeight()const;

};

#endif