#pragma once
#include "OgreFrameListener.h"

class OgreRenderWindow;
class OgreRoot;
class OgreRenderSystem;

using namespace Ogre;

class WindowGenerator : public FrameListener
{
private:
	//Singleton
	static WindowGenerator* instance_;
	WindowGenerator();


	RenderWindow* renderWindow_;
	Root* mRoot_;
	RenderSystem* renderSystem_;

	void initWindow();
	void createRoot();

public:
	//Singleton, init y get separados
	static WindowGenerator* getInstance();
	static WindowGenerator* initInstance();

	virtual ~WindowGenerator();

	//Getters
	inline Root* getOgreRoot()const;
	inline RenderWindow* getRenderWindow()const;
	inline RenderSystem* getRenderSystem()const;
};

