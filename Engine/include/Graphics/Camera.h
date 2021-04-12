#pragma once
#include "Component.h"
#include <string>

class Vector3;

namespace Ogre {
	class Camera;
	class SceneNode;
	
}

class Camera : public Component
{
protected:
	//Nodo que contiene a esta camara
	Ogre::SceneNode* camNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;
	Ogre::Viewport* vp_ = nullptr;
	std::string name = "MainCamera";
	virtual void init()override;
public:
	Camera();
	Camera(std::string cameraName);
	//camara unica de la escena
	
	virtual ~Camera();

	virtual void update()override;
	

	void setCameraPosition(Vector3 newPos);
	void setCameraDir(Vector3 newDir);
	void setBackgroundColor(Vector3 newColor ,float alpha);
	void setNearClipDistance(int distance);
	void setFarClipDistance(int distance);


	Vector3 getCameraPosition();
	inline Ogre::Camera* getCamera();

};

