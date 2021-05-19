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
	vector2 pos;
	vector2 size;
	std::string name;
	std::string type;
	CEGUI::Window* uiWindow = nullptr;

	//Normaliza el vector size del objeto para poder 
	//usar en el posicionamiento
	vector2 normalizeVector2(const vector2& v);

	UIComponent(vector2 position_, vector2 size_, std::string name_, int id);
	UIComponent(int id);
	virtual ~UIComponent();
public:

	virtual void init() = 0;
	virtual void update() {};
	virtual void setActive(bool act);

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params) = 0;

	// Setters
	void setPosition(const vector2& p);
	void setSize(const vector2& s);
	void setName(const std::string& n);
	void setProperty(const std::string nameProp, const std::string value);
};

#endif
