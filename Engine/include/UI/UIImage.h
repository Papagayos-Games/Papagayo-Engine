#pragma once

#ifndef _UI_IMAGE_H
#define _UI_IMAGE_H

#include "UIComponent.h"

class UIImage : public UIComponent
{
private:
	std::string image;
public:
	UIImage();
	virtual ~UIImage();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);
};

#endif

