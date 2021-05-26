#pragma once

#ifndef _COMMON_COMPONENT_H
#define _COMMON_COMPONENT_H

#include <json.hpp>

class Entity;
class Manager;

class Component {
protected:
	int _id;   // identificador del tipo de componente
	bool _active = true;

	Entity* _entity;
	Manager* _manager;

public: 
	//Constructora
	Component(Manager* man, int id);
	//Destructora
	virtual ~Component();


	//Método a redefinir, sirve para inicializar cada uno de los componentes
	virtual void init() = 0;
	//Carga del componente mediante datos
	virtual void load(const nlohmann::json& params) = 0;
	//Actualizar el estado del componente en cada iteracion
	virtual void update(float deltaTime) = 0;
	//Metodo para coger referencias a otros componentes tras la inicialización de todos
	virtual void setUp();
	
    //Comprueba si el componente esta activo
	bool isActive() const;
	//Guardar identificador de componente
	void setId(int id);
	//Settear la entidad asociada a este componente
	void setEntity(Entity* e);
	
	//Metodo para activar y desactivar el componente
	virtual void setActive(bool act);
	//Devuelve la entidad asociada a este componente
	Entity* getEntity() const;
	//Devuleve el manager al que esta asociado este componente
	Manager* getManager() const;
	//Obtener identificador del componente
	int getId() const;
};

#endif