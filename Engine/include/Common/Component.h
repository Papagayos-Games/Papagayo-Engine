#pragma once

#ifndef _COMMON_COMPONENT_H
#define _COMMON_COMPONENT_H

class Entity;
class Manager;

class Component {
protected:
	int _id;   // identificador del tipo de componente
	bool _active;

	Entity* _entity;
	Manager* _manager;

public:
	//constructor
	Component(Manager* man, int id);
	virtual ~Component();

	virtual void init() = 0;
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