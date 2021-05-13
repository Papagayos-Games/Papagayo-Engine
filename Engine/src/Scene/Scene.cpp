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
    for (auto it = entities.begin(); it != entities.end(); it++) {
        delete it->second;

        //entities_.popfront();
    }
    entities.clear();
    usedNames.clear();
}


void Scene::addEntity(const std::string& name, Entity* ent)
{
    //entities.pushback(name, ent);
    std::string n = name;
    if (entities.find(name) == entities.end())
        n += std::to_string(usedNames[name]++);
    else usedNames.insert(std::pair<std::string, int>(name, 0));
    entities.insert(std::pair<std::string, Entity*>(n, ent));
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
    std::map<std::string, Entity*>::iterator entity = entities.find(name);
    if (entity == entities.end())
        return nullptr;
    else
        return entity->second;
}
