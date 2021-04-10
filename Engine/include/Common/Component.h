#pragma once

#ifndef _COMMON_COMPONENT_H
#define _COMMON_COMPONENT_H

#include <string>

class Entity;
class Manager;

class Component {
protected:
	int _id;   // identificador del tipo de componente
	bool _active;

	Entity* _entity;
	Manager* _manager;

	virtual void init() = 0;
public:
	//constructor
	Component(int id, Manager* man);
	virtual ~Component();

	virtual void update() = 0;

	bool isActive();
	void setActive(bool act);

	void setId(int);
	int getId() const;

	Entity* getEntity();
	void setEntity(Entity* e);
	
	Manager* getManager();
};

#endif