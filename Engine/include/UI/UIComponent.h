#pragma once

#ifndef _UI_COMPONENT_H
#define _UI_COMPONENT_H

#include "Component.h"
#include <iostream>
class Transform;

namespace CEGUI {
	class Window;
	class SubscriberSlot;
	class String;
}

using vector2 = std::pair<float, float>;
class UIComponent : public Component
{
protected:
	vector2 position;
	vector2 size;
	std::string name;
	Transform* canvasTR;
	CEGUI::Window* uiWindow;

	CEGUI::String* event_;

	UIComponent(vector2 position_, vector2 size_, std::string name_, int id);
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
