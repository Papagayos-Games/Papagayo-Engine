#pragma once

#ifndef _UI_POINTER_H
#define _UI_POINTER_H

#include "Component.h"

class UIPointer : public Component
{
private:
	std::string pointer;
	bool visible;
public:
	UIPointer();
	virtual ~UIPointer();

	virtual void init();
	virtual void update(float deltaTime) {};

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);
};

#endif

