#pragma once
#include "OgreFrameListener.h"

namespace Ogre {
	class OgreRenderWindow;
	class OgreRoot;
	class OgreRenderSystem;
	class Root;
}



class WindowGenerator : public Ogre::FrameListener
{
private:
	//Singleton
	static WindowGenerator* instance_;
	WindowGenerator(Ogre::Root* root);


	Ogre::RenderWindow* renderWindow_;
	Ogre::Root* mRoot_;
	Ogre::RenderSystem* renderSystem_;

	void initWindow();

public:
	//Singleton, init y get separados
	static WindowGenerator* getInstance();
	static bool setupInstance(Ogre::Root* root);

	virtual ~WindowGenerator();

	//Getters
	inline Ogre::RenderWindow* getRenderWindow()const;
	inline Ogre::RenderSystem* getRenderSystem()const;
};

