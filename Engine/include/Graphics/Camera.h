#pragma once

#ifndef _GRAPHICS_CAMERA_H
#define _GRAPHICS_CAMERA_H

#include "Component.h"
#include <string>

class Vector3;
class Transform;

namespace Ogre {
	class Camera;
	class SceneNode;
	class Viewport;
}

class Camera : public Component
{
protected:
	//Nodo que contiene a esta camara
	Ogre::SceneNode* camNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;
	Ogre::Viewport* vp_ = nullptr;
	std::string name_ = "";
	Transform* tr_ = nullptr;

public:

	Camera();
	virtual ~Camera();

	virtual void update(float deltaTime)override;
	virtual void setUp()override;
	virtual void load(const nlohmann::json& params) override;
	virtual void init()override;

	//Cambiar posicion del nodo asociado a la camara
	void setCameraPosition(const Vector3& newPos);
	//Cambiar la posicion global hacia la que apunta la camara
	void setCameraDir(Vector3& newDir);
	//Cambiar el color del viewport asociado a esta camara
	void setBackgroundColor(const Vector3& newColor ,float alpha);
	//Cambiar distancia de la camara al plano cercano
	void setNearClipDistance(int distance);
	//Cambiar distancia de la camara al plano lejano
	void setFarClipDistance(int distance);

	//Metodo para convertir una posición en coordenadas relativas a la ventana de la camapa
	Vector3 getScreenCoordinates(const Vector3& iPoint);
	//Getter posicion de la camara
	const Vector3& getCameraPosition() const;
	//Obtener camara
	inline Ogre::Camera* getCamera() const;
};

#endif