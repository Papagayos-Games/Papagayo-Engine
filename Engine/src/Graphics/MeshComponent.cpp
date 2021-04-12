#include "Graphics/MeshComponent.h"
#include "Managers/SceneManager.h"
#include "Managers/RenderManager.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Transform.h"
#include "Graphics/OgreContext.h"
#include "Entity.h"
#include "CommonManager.h"
#include "Transform.h"





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

void MeshComponent::setActive(bool act)
{
	_active = act;
	mNode_->setVisible(_active);
}

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
	//posicion
	Transform* transform_=static_cast<Transform*>(_entity->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	Vector3 pos = transform_->getPos();
	mNode_->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	Vector3 rot = transform_->getRot();
	//rotaciones //TO DO: revisar
	mNode_->resetOrientation();
	mNode_->yaw(Ogre::Degree(rot.y),Ogre::Node::TS_WORLD);//ejeY
	mNode_->pitch(Ogre::Degree(rot.x),Ogre::Node::TS_WORLD);//ejex
	mNode_->roll(Ogre::Degree(rot.z),Ogre::Node::TS_WORLD);//ejez
	//escala
	Vector3 scale = transform_->getDimensieons();
	mNode_->scale(Ogre::Vector3(scale.x, scale.y, scale.z));
	
}

void MeshComponent::setMaterial(std::string matName)
{
	ogreEnt_->setMaterialName(matName);
}
