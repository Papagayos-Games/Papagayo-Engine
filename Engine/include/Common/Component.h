#pragma once

#ifndef _COMMON_COMPONENT_H
#define _COMMON_COMPONENT_H

#include <json.hpp>	//provisional en el .h
class Entity;
class Manager;

class Component {
protected:
	int _id;   // identificador del tipo de componente
	bool _active = true;

	Entity* _entity;
	Manager* _manager;

public:
	//constructor
	Component(Manager* man, int id);
	virtual ~Component();

	virtual void init() = 0;
	virtual void load(const nlohmann::json& params) = 0;
	virtual void update() = 0;
	virtual void setUp();

	bool isActive() const;
	virtual void setActive(bool act);

	void setId(int);
	int getId();
	int getId() const;

	void setEntity(Entity* e);
	Entity* getEntity();
	Entity* getEntity() const;
	
	Manager* getManager();
	Manager* getManager() const;
};

#endif