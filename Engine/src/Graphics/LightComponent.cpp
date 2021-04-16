#include "..\..\include\Graphics\LightComponent.h"
#include "..\..\include\Graphics\LightComponent.h"
#include "LightComponent.h"
#include "OgreContext.h"
#include "OgreLight.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "RenderManager.h"
#include "Vector3.h"
#include <stdexcept>

LightComponent::LightComponent(Vector3 pos, std::string name, LIGHT_TYPE type): Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Light)
{
	if (type == LIGHT_TYPE::SPOTLIGHT) throw std::exception("tipo invalido de luz");
	initLight(name);
	lightType_ = type;
	switch (type)
	{
	case LIGHT_TYPE::DIRECTIONAL:
		ogreLight_->setType(Ogre::Light::LT_DIRECTIONAL);
		mNode_->setDirection(Ogre::Vector3(pos.x, pos.y, pos.z));
		break;
	case LIGHT_TYPE::POINT:
		ogreLight_->setType(Ogre::Light::LT_POINT);
		mNode_->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
		break;
	default:
		break;
	}
	ogreLight_->setDiffuseColour(1.0, 1.0, 1.0);
}

LightComponent::LightComponent(Vector3 pos, Vector3 dir, std::string name): Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Light)
{
	initLight(name);
	lightType_ = LIGHT_TYPE::SPOTLIGHT;
	ogreLight_->setType(Ogre::Light::LT_SPOTLIGHT);
	mNode_->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	mNode_->setDirection(Ogre::Vector3(dir.x, dir.y, dir.z));
	ogreLight_->setDiffuseColour(1.0, 1.0, 1.0);
}

void LightComponent::turnOn()
{
	ogreLight_->setVisible(true);
}

void LightComponent::turnOff()
{
	ogreLight_->setVisible(false);
}

void LightComponent::setColor(Vector3 newColor)
{
	ogreLight_->setDiffuseColour(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));

}

void LightComponent::setLightPower(float intensity)
{
	ogreLight_->setPowerScale(intensity);
}

void LightComponent::setCastShadow(bool status)
{
	ogreLight_->setCastShadows(status);
}

void LightComponent::initLight(std::string name)
{
	ogreLight_ = OgreContext::getInstance()->getSceneManager()->createLight(name);
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mNode_->attachObject(ogreLight_);
}

void LightComponent::init()
{
}

void LightComponent::update()
{
}

void LightComponent::setActive(bool status)
{
	status ? turnOn() : turnOff();
	Component::setActive(status);
}
