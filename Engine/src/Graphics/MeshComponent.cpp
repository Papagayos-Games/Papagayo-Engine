#include "MeshComponent.h"
#include "RenderManager.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Transform.h"
#include "OgreContext.h"
#include "Entity.h"
#include "CommonManager.h"
#include "Transform.h"


MeshComponent::MeshComponent():Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Mesh)
{
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}


void MeshComponent::setActive(bool act)
{
	_active = act;
	mNode_->setVisible(_active);
}

//MeshComponent::MeshComponent(Ogre::SceneNode* parentNode, std::string meshName): Component(nullptr, (int)RenderManager::RenderCmpId::Mesh)
//{
//	mNode_ = parentNode->createChildSceneNode(); //TO DO: NOMBRES A LOS NODOS
//	ogreEnt_ = OgreContext::getInstance()->getSceneManager()->createEntity(meshName + ".mesh");
//	mNode_->attachObject(ogreEnt_);
//}

MeshComponent::~MeshComponent()
{
	if (ogreEnt_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroyEntity(ogreEnt_);
	if (mNode_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroySceneNode(mNode_);
}

void MeshComponent::update()
{
	//posicion
	Vector3 pos = tr_->getPos();
	mNode_->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	Vector3 rot = tr_->getRot();
	//rotaciones //TO DO: revisar
	mNode_->resetOrientation();
	mNode_->yaw(Ogre::Degree(rot.y),Ogre::Node::TS_WORLD);//ejeY
	mNode_->pitch(Ogre::Degree(rot.x),Ogre::Node::TS_WORLD);//ejex
	mNode_->roll(Ogre::Degree(rot.z),Ogre::Node::TS_WORLD);//ejez
	//escala
	Vector3 scale = tr_->getDimensions();
	mNode_->setScale(Ogre::Vector3(scale.x, scale.y, scale.z));
	
}

void MeshComponent::setUp()
{
	tr_ = static_cast<Transform*>(_entity->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
}

void MeshComponent::load(nlohmann::json params)
{
	auto it = params.find("meshName");
	//OBLIGATORIO CAMPO MESHNAME
	if (it != params.end()) {
		std::string meshName = it->get<std::string>();
		ogreEnt_ = OgreContext::getInstance()->getSceneManager()->createEntity(meshName + ".mesh");
		mNode_->attachObject(ogreEnt_);
	}
	else {
		throw std::runtime_error("Invalid format: component mesh requires a meshName, did you forget to include it?\n");
	}

	it = params.find("meshMaterial");
	if (it != params.end()) {
		std::string meshMat = it->get<std::string>();
		setMaterial(meshMat);
	}

}

void MeshComponent::init()
{
}

void MeshComponent::setMaterial(std::string matName)
{
	ogreEnt_->setMaterialName(matName);
}
