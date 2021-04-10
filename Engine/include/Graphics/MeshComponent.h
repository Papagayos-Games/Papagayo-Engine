#pragma once
#include "Component.h"
#include <string>
#include <list>

class SceneManager;



namespace Ogre {
	class SceneNode;
	class Entity;
	
}

class MeshComponent: public Component
{
private:

	Ogre::SceneNode* mNode_ = nullptr;
	Ogre::SceneNode* parentNode_ = nullptr;
	Ogre::Entity* ogreEnt_ = nullptr;
	
protected:
	virtual void init()override {}

public:
	MeshComponent();
	MeshComponent(Ogre::SceneNode* parentNode,const std::string meshName);
	MeshComponent(const std::string meshName);

	//virtual void setActive( const bool act) override;
	
	virtual ~MeshComponent();
	virtual void update() override;
};

