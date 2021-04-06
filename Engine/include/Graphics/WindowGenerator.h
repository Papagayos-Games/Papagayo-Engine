#pragma once
#include "OgreFrameListener.h"

namespace Ogre {
	class OgreRenderWindow;
	class OgreRenderSystem;
	class Root;
}



class WindowGenerator : public Ogre::FrameListener
{
private:
	//Singleton
	static WindowGenerator* instance_;
	WindowGenerator(Ogre::Root* root, std::string name);


	Ogre::RenderWindow* renderWindow_;
	Ogre::Root* mRoot_;
	Ogre::RenderSystem* renderSystem_;

	void initWindow(std::string name);

public:
	//Singleton, init y get separados
	static WindowGenerator* getInstance();
	static bool setupInstance(Ogre::Root* root, std::string name);

	virtual ~WindowGenerator();

	//Getters
	Ogre::RenderWindow* getRenderWindow()const;
	inline Ogre::RenderSystem* getRenderSystem()const;
};

