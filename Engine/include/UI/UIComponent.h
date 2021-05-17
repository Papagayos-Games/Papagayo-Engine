#pragma once

#ifndef _UI_COMPONENT_H
#define _UI_COMPONENT_H

#include "Component.h"

class Transform;

namespace CEGUI {
	class Window;
	class SubscriberSlot;
	class String;
}

class UIComponent : public Component
{
protected:
	std::pair<float, float> position;
	std::pair<float, float> size;
	std::string name;
	Transform* canvasTR;
	CEGUI::Window* uiWindow;
	//CEGUI::SubscriberSlot* subscriberEvent; //no va a hacer falta ya que los eventos se pueden suscribir como uiWindow->subscribeEvent(...)
												// de todos modos lo dejo comentado porque hay que hablarlo
	CEGUI::String* event_;

	UIComponent(std::pair<float, float> position_, std::pair<float, float> size_, std::string name_, int id);
	UIComponent(int id);
	virtual ~UIComponent();
public:

	virtual void setUp();
	virtual void init() = 0;
	virtual void update() {};

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params) = 0;
};

#endif
