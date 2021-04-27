#include "Scene/Scene.h"
#include "Common/Entity.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}


void Scene::addEntity(Entity* ent)
{
	entities_.push_back(ent);
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
	/*map<string, Entity*>::iterator entity = entities_.find(name);
	if (entity == entities_.end())
		return nullptr;
	else
		return entity->second;*/
}