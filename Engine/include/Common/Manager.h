#pragma once

#ifndef _COMMON_MANAGER_H
#define _COMMON_MANAGER_H

#include <List>
#include <memory>
#include <functional>
#include <string>
#include <map>

class Entity;
class Component;


enum class ManID
{
	Common = 0,
	Physics,
	Render,

	LastManId
};

class Manager {
protected:
	std::map <std::string, std::function<Component* ()>> compsRegistry_;
	std::list<Component*> _compsList;
	ManID _manId;
public:
	Manager(ManID id);
	virtual ~Manager();

	virtual void addComponent(Entity* ent, int compId) = 0;
	virtual void start() = 0;
	virtual void update() = 0;

	std::list<Component*> getComponents();
	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);


	//-- Factory --//
	void registerComponent(std::string name, std::function<Component * ()>compConst);
	Component* create(std::string name, Entity* ent);	//esto puede ser un puntero inteligente
	//-------------//
	int getId();
};

#endif