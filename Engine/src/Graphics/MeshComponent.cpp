#include "Graphics/MeshComponent.h"
#include "Managers/SceneManager.h"
#include "Managers/RenderManager.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Transform.h"
#include "Graphics/OgreContext.h"





MeshComponent::MeshComponent():Component(nullptr, (int)RenderManager::RenderCmpId::Mesh)
{
	
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(); //TO DO: NOMBRES A LOS NODOS
	ogreEnt_ = OgreContext::getInstance()->getSceneManager()->createEntity("cube.mesh"); //TO DO: NO HACERLO A PELO XDDD
	mNode_->attachObject(ogreEnt_);
}

MeshComponent::MeshComponent(std::string meshName):Component(nullptr, (int)RenderManager::RenderCmpId::Mesh)
{
	
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(); //TO DO: NOMBRES A LOS NODOS
	ogreEnt_ = OgreContext::getInstance()->getSceneManager()->createEntity(meshName + ".mesh");
	mNode_->attachObject(ogreEnt_);
}

//void MeshComponent::setActive(const bool act)
//{
//	active = act;
//	mNode_->setVisible(active);
//}

MeshComponent::MeshComponent(Ogre::SceneNode* parentNode, std::string meshName): Component(nullptr, (int)RenderManager::RenderCmpId::Mesh)
{
	
	mNode_ = parentNode->createChildSceneNode(); //TO DO: NOMBRES A LOS NODOS
	ogreEnt_ = OgreContext::getInstance()->getSceneManager()->createEntity(meshName + ".mesh");
	mNode_->attachObject(ogreEnt_);
}

MeshComponent::~MeshComponent()
{
	if (ogreEnt_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroyEntity(ogreEnt_);
	if (mNode_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroySceneNode(mNode_);
}

void MeshComponent::update()
{
	
}
