#pragma once

#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H


#include "UIComponent.h"


class UIButton:public UIComponent
{
private:
	std::string text;
	std::string scene;

	bool buttonPressed = false;

public:
	UIButton();
	virtual ~UIButton();

	virtual void init();

	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);

	//Evento que se suscribe al pulsar el boton, el cual activa
	//el booleano que usara lua para su logica
	void buttonWasPressed();

	//Cuando en lua se aplique la logica correspondiente al pulsar el 
	//boton se desasctivara el booleano para que pueda ser pulsado de nuevo
	void buttonNotPressed();

	//Devuelve el estado del boton (pulsado o no pulsado)
	bool getButtonPressed();

	//Aplica un nuevo texto al boton
	void setText(std::string t);
};

#endif

