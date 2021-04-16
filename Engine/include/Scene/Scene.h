#pragma once

#include <string>
#include <map>
#include <json.hpp>

using json = nlohmann::json;

using namespace std;

class Entity;

class Component;

class Scene
{
public:
	Scene();
	~Scene();

	bool load(json& j);

	void addEntity(Entity* ent);
	string getName() const;
	Entity* getEntity(const string& name);

private:
	map<int, Component*> components_;
	map<string, Entity*> entities_;
	list<Entity*> entityList_;
	string name;
};

