#pragma once

#ifndef _COMMON_ENTITY_H
#define _COMMON_ENTITY_H

#include <map>

class Component;

class Entity
{
private:
	std::map<int, std::map<int, Component*>> _componentMap;

public:
	//constructor
	Entity();
	//destructor
	~Entity();

	// añade un componente
	void addComponent(Component* comp);

	// devuelve el compenente asociado a esa id
	Component* getComponent(int managerId, int compI);
		
    // comprueba si la entidad tiene el componente id
	bool hasComponent(int managerId, int compId);

	// Este metodo solo elimina el componente de la lista de componentes de la entidad
	// Para destruirlo se debe llamar a Manager::destroyComponent(Entity* ent);
	bool removeComponent(int managerId, int compId);
};

#endif