#include "PlaneComponent.h"
#include "RenderManager.h"
#include "OgreMeshManager.h"
#include "Vector3.h"
#include "OgreSceneNode.h"
#include "OgreContext.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"

PlaneComponent::PlaneComponent(std::string name, std::string materialName, int width, int height, PLANE_DIR type):
	Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Plane)

{
	switch (type)
	{
		case PLANE_DIR::PLANE_X:
			Ogre::MeshManager::getSingleton().createPlane(name,
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				Ogre::Plane(Ogre::Vector3::UNIT_X, 0), width, height,
				1, 1, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
			break;
		case PLANE_DIR::PLANE_Y:
			Ogre::MeshManager::getSingleton().createPlane(name,
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), width, height,
				1, 1, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
			break;
		case PLANE_DIR::PLANE_Z:
			Ogre::MeshManager::getSingleton().createPlane(name,
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), Ogre::Real(width), Ogre::Real(height),
				1, 1, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
			break;
		default:
			break;
	}
	ent_ = OgreContext::getInstance()->getSceneManager()->createEntity(name);
	ent_->setMaterialName(materialName);
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode_->attachObject(ent_);
}

void PlaneComponent::setTexture(std::string textName)
{
	try {
		ent_->setMaterialName(textName);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("The texture " + textName + " no exist. " + e.what());
	}
}
