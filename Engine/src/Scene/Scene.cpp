#include "Scene/Scene.h"
#include "Common/Entity.h"
#include <PapagayoEngine.h>
#include <algorithm>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::clean()
{
    eraseEntities();
    for (auto it = entities.begin(); it != entities.end(); it++) {
        delete it->second;
    }
    entities.clear();
    usedNames.clear();
}

void Scene::eraseEntities()
{
    for (auto it = entities_to_erase.begin(); it != entities_to_erase.end(); ++it) {
        (*it)->second->destroy();
        delete (*it)->second;
        entities.erase(*it);
        //PapagayoEngine::getInstance()->closeApp();
    }
    entities_to_erase.clear();
}

void Scene::killEntityByName(const std::string& s)
{
    auto it = entities.find(s);
    if (it != entities.end()) {
        entities_to_erase.push_back(it);
    }
}

void Scene::killEntity(Entity* e)
{
    auto it = std::find_if(entities.begin(), entities.end(), [e](const auto& mo) {return mo.second == e; });
    if (it != entities.end()) {
        entities_to_erase.push_back(it);
    }

}


void Scene::addEntity(const std::string& name, Entity* ent)
{
    //entities.pushback(name, ent);
    std::string n = name;
    if (usedNames.find(name) != usedNames.end())
        n += std::to_string(++usedNames[name]);
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
