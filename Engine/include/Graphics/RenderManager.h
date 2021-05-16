#pragma once

#ifndef _GRAPHICS_RENDMAN_H
#define _GRAPHICS_RENDMAN_H

#include "Manager.h"

namespace Ogre {
	class Root;
	class Camera;
}

class RenderManager : public Manager
{
private:
	static RenderManager* instance_;

	Ogre::Root* ogreRoot_;
	RenderManager();
	virtual ~RenderManager();
public:
	enum class RenderCmpId : int {
		Mesh = 0,
		Camera,
		Light,
		Plane,

		LastRenderCmpId
	};

	static RenderManager* getInstance();
	static bool setUpInstance();
	static void clean();
	static void destroy();
	virtual void start();
	virtual void update();
};

#endif