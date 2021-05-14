#pragma once

#ifndef _COMMON_ENTITY_H
#define _COMMON_ENTITY_H

#include <map>
#include <string>

class Component;

class Entity
{
private:
	std::map<int, std::map<int, Component*>> _componentMap;

	std::string name_;

public:
	//constructor
	Entity();
	//destructor
	~Entity();

	// inicializa las componentes
	void start();
	// añade un componente
	void addComponent(Component* comp);

	std::string& getName();
	const std::string& getName() const;

	void setName(const std::string& name);

	// devuelve el compenente asociado a esa id
	Component* getComponent(int managerId, int compI);
		
    // comprueba si la entidad tiene el componente id
	bool hasComponent(int managerId, int compId) const;

	// Este metodo solo elimina el componente de la lista de componentes de la entidad
	// Para destruirlo se debe llamar a Manager::destroyComponent(Entity* ent);
	bool removeComponent(int managerId, int compId);
};

#endif