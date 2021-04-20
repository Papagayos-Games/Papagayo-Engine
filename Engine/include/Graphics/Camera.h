#pragma once
#include "Component.h"
#include <string>

class Vector3;
class Transform;

namespace Ogre {
	class Camera;
	class SceneNode;
	class Viewport;
}

enum class CameraType : int {
	STATIC = 0,
	DYNAMIC
};

class Camera : public Component
{
protected:
	//Nodo que contiene a esta camara
	Ogre::SceneNode* camNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;
	Ogre::Viewport* vp_ = nullptr;
	std::string name_ = "";
	Transform* tr_ = nullptr;
	CameraType type_ = CameraType::STATIC;

public:

	Camera();
	//	Constructora de la cámara con un nodo padre
	//Camera(Ogre::SceneNode* parentNode,std::string name);
	
	virtual ~Camera();

	virtual void update()override;
	virtual void setUp()override;
	virtual void load(nlohmann::json params)override;
	virtual void init()override;

	void setCameraPosition(Vector3 newPos);
	void setCameraDir(Vector3 newDir);
	void setBackgroundColor(Vector3 newColor ,float alpha);
	void setNearClipDistance(int distance);
	void setFarClipDistance(int distance);


	Vector3 getCameraPosition();
	inline Ogre::Camera* getCamera();

};

