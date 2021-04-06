#include "MeshComponent.h"
#include "Managers/SceneManager.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>


void MeshComponent::init()
{
	sceneInstance_ = SceneManager::getInstance();
}

MeshComponent::MeshComponent():Component(ecs::Mesh)
{
	init();
	mNode_ = sceneInstance_->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode(); //TO DO: NOMBRES A LOS NODOS
	ent_ = sceneInstance_->getOgreSceneManager()->createEntity("cube.mesh"); //TO DO: NO HACERLO A PELO XDDD
	auto aux = ent_->getMesh();
	auto aux2 = ent_->getName();
	mNode_->attachObject(ent_);
}

MeshComponent::MeshComponent(Ogre::SceneNode* parentNode): Component(ecs::Mesh)
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::update()
{
}
