#pragma once

#ifndef _UI_LABEL_H
#define _UI_LABEL_H

#include "UIComponent.h"

class UILabel : public UIComponent
{
private:
	std::string text;
public:
	UILabel();
	virtual ~UILabel();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);

	//Aplica un nuevo texto al label
	void setText(std::string t);
};

#endif

