#pragma once

#ifndef _UI_SLIDER_H
#define _UI_SLIDER_H

#include "UIComponent.h"

class UISlider:public UIComponent
{
public:
	UISlider();
	virtual ~UISlider();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);
};

#endif

