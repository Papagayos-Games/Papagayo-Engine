#pragma once

#ifndef _COMMON_MANAGER_H
#define _COMMON_MANAGER_H

#include <List>

class Entity;
class Component;

class Manager {
protected:
	std::list<Component*> _compsList;
	int _manId;
public:
	Manager(int id);
	virtual ~Manager();

	virtual void addComponent(Entity* ent, int compId) = 0;
	virtual void start() = 0;
	virtual void update() = 0;

	std::list<Component*> getComponents();
	void destroyAllComponents();
	bool destroyComponent(Entity* ent, int compId);

	int getId();
};

#endif