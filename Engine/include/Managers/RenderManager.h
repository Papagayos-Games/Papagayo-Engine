#pragma once

namespace Ogre {
	class Root;
	class Camera;
}

class RenderManager
{
public:
	~RenderManager();
	static RenderManager* getInstance();
	static bool setupInstance();
	static void clean();

	void update();

private:
	RenderManager();
	static RenderManager* instance_;
	Ogre::Root* ogreRoot_;
	Ogre::Camera* camera_;

};

