#pragma once
#include "Component.h"

class SceneManager;

namespace Ogre {
	class SceneNode;
	class Entity;
}

class MeshComponent: public Component
{
private:
	SceneManager* sceneInstance_;
	Ogre::SceneNode* mNode_ = nullptr;
	//Nodo padre del que parte mNode -> si es un solo MeshComponent del que no cuelga ninguna otra maya otro es Root
	//Si no, es el nodo que creó esa nueva maya
	Ogre::SceneNode* parentNode_ = nullptr;
	Ogre::Entity* ent_ = nullptr;

protected:
	virtual void init();

public:
	MeshComponent();
	MeshComponent(Ogre::SceneNode* parentNode);

	virtual ~MeshComponent();
	virtual void update();
};

