#pragma once
#include "ecs.h"
#include <string>

class Entity;
class Manager;

class Component {
protected:
	ecs::CmpId _id;   // identificador del tipo de componente
	std::string _name;
	bool _active;

	Entity* _entity;
	Manager* _manager;

	virtual void init() = 0;
public:
	//constructor
	Component(ecs::CmpId id, Manager* man);
	virtual ~Component();

	virtual void update() = 0;

	bool isActive();
	void setActive(bool act);

	void setId(ecs::CmpId id);
	ecs::CmpId getId() const;

	Entity* getEntity();
	void setEntity(Entity* e);
	
	Manager* getManager();
};