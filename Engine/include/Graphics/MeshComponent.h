#pragma once

#ifndef _GRAPHICS_MESHCOMP_H
#define _GRAPHICS_MESHCOMP_H

#include "Component.h"
#include <string>

class SceneManager;
class Transform;

namespace Ogre {
	class SceneNode;
	class Entity;
}

class MeshComponent: public Component
{
private:

	Ogre::SceneNode* mNode_ = nullptr;		
	Ogre::Entity* ogreEnt_ = nullptr;
	Transform* tr_ = nullptr;
public:
	//constructora por defecto
	MeshComponent();
	virtual ~MeshComponent();

	//metodo para desactivar el componente y su nodo
	virtual void setActive( bool act) override;
	virtual void update(float deltaTime) override;
	virtual void setUp() override;
	virtual void load(const nlohmann::json& params) override;
	virtual void init()override;

	//Obtener la entidad de ogre asociada a este mesh
	Ogre::Entity* getOgreEntity();
	//metodo para asignar un material nuevo a la entidad
	void setMaterial(const std::string& matName);
};

#endif