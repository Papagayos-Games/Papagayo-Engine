#include "..\..\include\Graphics\LightComponent.h"
#include "..\..\include\Graphics\LightComponent.h"
#include "LightComponent.h"
#include "OgreContext.h"
#include <checkML.h>
#include "OgreLight.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "RenderManager.h"
#include "Vector3.h"
#include <stdexcept>

LightComponent::LightComponent(): Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Light)
{
	init();
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

void LightComponent::init()
{
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}

void LightComponent::update()
{
}

void LightComponent::setActive(bool status)
{
	status ? turnOn() : turnOff();
	Component::setActive(status);
}

void LightComponent::load(const nlohmann::json& params)
{
	auto it = params.find("lightName");
	if (it != params.end()) {
		std::string name = it->get<std::string>();
		ogreLight_ = OgreContext::getInstance()->getSceneManager()->createLight(name);
		mNode_->attachObject(ogreLight_);
	}
	else {
		throw std::runtime_error("Cannot create light without name\n");
	}

	it = params.find("lightType");
	if (it != params.end()) {
		int type = it->get<int>();
		lightType_ = (LIGHT_TYPE)type;

		switch (lightType_)
		{
		case LIGHT_TYPE::DIRECTIONAL:
			ogreLight_->setType(Ogre::Light::LT_DIRECTIONAL);
			break;
		case LIGHT_TYPE::POINT:
			ogreLight_->setType(Ogre::Light::LT_POINT);
			break;
		case LIGHT_TYPE::SPOTLIGHT:
			ogreLight_->setType(Ogre::Light::LT_SPOTLIGHT);
			break;
		default:
			ogreLight_->setType(Ogre::Light::LT_POINT);
			break;
		}
	}

	it = params.find("diffuseColour");
	if (it != params.end()) {
		std::vector<float> diff = it->get<std::vector<float>>();
		ogreLight_->setDiffuseColour(diff[0], diff[1], diff[2]);
	}
	else ogreLight_->setDiffuseColour(1.0, 1.0, 1.0);

	it = params.find("lightPower");
	if (it != params.end()) {
		int pow = it->get<int>();
			ogreLight_->setPowerScale(pow);
	}
	else ogreLight_->setPowerScale(1);

	it = params.find("visible");
	if (it != params.end()) {
		bool vis = it->get<bool>();
			ogreLight_->setVisible(vis);
	}
	else ogreLight_->setVisible(false);


	it = params.find("castShadow");
	if (it != params.end()) {
		bool cast = it->get<bool>();
			ogreLight_->setCastShadows(cast);
	}
	else ogreLight_->setCastShadows(true);

	it = params.find("lightDirection");
	if (it != params.end()) {
		std::vector<float> diff = it->get<std::vector<float>>();
		ogreLight_->setDirection(diff[0], diff[1], diff[2]);
	}
	else ogreLight_->setDirection(0, 0, 1.0);
	

}
