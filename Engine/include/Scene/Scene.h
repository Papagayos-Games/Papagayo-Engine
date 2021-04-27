#pragma once

#include <string>
#include <list>

class Entity;
class Component;

class Scene
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* ent);
	void setName(const std::string& s);
	const std::string& getName() const;
	// TO DO: buscar a la entidad por tag
	Entity* getEntity(const std::string& name);

private:
	std::list<Entity*> entities_;
	std::string name;
};

