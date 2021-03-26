#pragma once
#include "OgreFrameListener.h"

//
class OgreRenderWindow;
class OgreRoot;
class OgreRenderSystem;


using namespace Ogre;

class WindowGenerator : public FrameListener
{
private:

	RenderWindow* renderWindow_;
	Root* mRoot_;
	RenderSystem* renderSystem_;

	void initWindow();
	void createRoot();

public:
	WindowGenerator();
	virtual ~WindowGenerator();
};

