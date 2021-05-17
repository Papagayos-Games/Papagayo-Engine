#pragma once

#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H


#include "UIComponent.h"

class UIButton:public UIComponent
{
private:
	std::string text;
	std::string scene;
public:
	UIButton();
	virtual ~UIButton();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);

	/// <summary>
	/// Metodo encargado de hacer lo que corresponda cuando el boton ha sido clickado.
	/// ¿Debera hacer la llamada correspondiente con lua segun el evento?
	/// </summary>
	void onClick();

	/// <summary>
	/// Metodo encargado de hacer el cambio de escena cuando el boton es clickado
	/// </summary>
	void changeScene();
};

#endif

