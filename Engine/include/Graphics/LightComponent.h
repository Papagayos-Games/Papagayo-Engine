#pragma once

#ifndef _GRAPHICS_LIGHTCOMP_H
#define _GRAPHICS_LIGHTCOMP_H

#include <Component.h>
#include <string>

class Vector3;

namespace Ogre {
	class SceneNode;
	class Light;
}

enum class LIGHT_TYPE
{
	SPOTLIGHT, POINT, DIRECTIONAL
};

class LightComponent :
    public Component
{
private:
	Ogre::SceneNode* mNode_ = nullptr;
	Ogre::SceneNode* parentNode_ = nullptr;
	Ogre::Light* ogreLight_ = nullptr;
	LIGHT_TYPE lightType_;

public:
	//Constructora
	LightComponent();
	virtual ~LightComponent();
	//	Enciende la luz
	inline void turnOn();
	//	Apaga la luz
	void turnOff();
	//	Cambia el color de una luz
	void setColor(const Vector3& newColor);
	//	Cambia la intensidad de una luz ( 0.0 -> 1.0)
	void setLightPower(float intensity);
	//	Activa las sombras
	void setCastShadow(bool status);

	virtual void init()override;
	virtual void update(float deltaTime) override;
	virtual void setActive(bool status)override;
	virtual void load(const nlohmann::json& params)override;
};

#endif