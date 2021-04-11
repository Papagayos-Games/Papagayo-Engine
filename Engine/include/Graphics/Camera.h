#pragma once
#include "Component.h"

class Vector3;

namespace Ogre {
	class Camera;
	class SceneNode;
	class TransformSpace;
}

class Camera : public Component
{
protected:
	//Nodo que contiene a esta camara
	Ogre::SceneNode* camNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;

	virtual void init()override;
public:
	Camera();
	virtual ~Camera();

	virtual void update()override;

	void setCameraPosition(Vector3 newPos);
	//void setCameraDir(Vector3 newDir, Ogre::Node::TransformSpace  transformSpace = Ogre::Node::TS_WORLD);

	Vector3 getCameraPosition();
	inline Ogre::Camera* getCamera();

};

