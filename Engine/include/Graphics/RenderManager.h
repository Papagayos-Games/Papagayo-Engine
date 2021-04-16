#pragma once
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
	~RenderManager();
public:
	enum class RenderCmpId : int {
		Mesh = 0,
		Camera,
		Light,

		LastRenderCmpId
	};

	static RenderManager* getInstance();

	virtual void addComponent(Entity* ent, int compId);
	virtual void start();
	virtual void update();
};

