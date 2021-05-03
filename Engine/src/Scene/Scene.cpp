#include "Scene/Scene.h"
#include "Common/Entity.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::clean()
{
	for (auto it = entities_.begin(); it != entities_.end(); it++) {
		delete it->second;

		//entities_.pop_front();
	}
	entities_.clear();
	usedNames_.clear();
}


void Scene::addEntity(const std::string& name, Entity* ent)
{
	//entities_.push_back(name, ent);
	std::string n = name;
	if (entities_.find(name) != entities_.end())
		n += std::to_string(++usedNames_[name]);
	else usedNames_.insert(std::pair<std::string, int>(name, 0));
	entities_.insert(std::pair<std::string, Entity*>(n, ent));
	ent->setName(n);
}

void Scene::setName(const std::string& s)
{
	name = s;
}

const std::string& Scene::getName() const
{
	return name;
}

Entity* Scene::getEntity(const std::string& name) {
	std::map<std::string, Entity*>::iterator entity = entities_.find(name);
	if (entity == entities_.end())
		return nullptr;
	else
		return entity->second;
	//return nullptr;
}