#pragma once

namespace Ogre {
	class Root;
	class Camera;
}

class RenderManager
{
public:
	enum class RenderCmpId : int {
		Mesh = 0,
		Camera,

		LastCommonCmpId
	};
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

