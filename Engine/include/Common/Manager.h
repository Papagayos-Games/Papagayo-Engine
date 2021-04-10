#pragma once
#include <List>

class Entity;
class Component;

class Manager {
protected:
	std::list<Component*> compsList;
public:
	Manager();
	virtual ~Manager();

	virtual void addComponent(Entity* ent, int id) = 0;
	virtual void start() = 0;
	virtual void update() = 0;

	virtual std::list<Component*> getComponents();
	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);
};