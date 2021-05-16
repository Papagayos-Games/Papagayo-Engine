#pragma once

#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H


#include "UIComponent.h"

class UIButton:public UIComponent
{
private:
	std::string text;
public:
	UIButton();
	virtual ~UIButton();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);
};

#endif

