#include "Scene/Scene.h"
#include "Common/Entity.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::load(json& j)
{
	return true;
}

void Scene::addEntity(Entity* ent)
{
	entityList_.push_back(ent);
}

string Scene::getName() const
{
	return name;
}

Entity* Scene::getEntity(const string& name) {
	map<string, Entity*>::iterator entity = entities_.find(name);
	if (entity == entities_.end())
		return nullptr;
	else
		return entity->second;
}