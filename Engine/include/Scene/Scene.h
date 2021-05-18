#pragma once

#ifndef _PAPAENG_SCENE_H
#define _PAPAENG_SCENEH

#include <string>
#include <list>
#include <map>
#include <iterator>

//#include "json.hpp"

//namespace nlohmann {
//    class json;
//}

class Entity;
class Component;

class Scene
{
public:
    Scene();
    ~Scene();

    void clean();
    void eraseEntities();
    void killEntityByName(const std::string& s);
    void killEntity(Entity* e);
    void addEntity(const std::string& name, Entity* ent);
    void setName(const std::string& s);
    const std::string& getName() const;
    Entity* getEntity(const std::string& name);

private:
    // la key seria el nombre del archivo
    // std::map<std::string, Entity*> prefabs;

    //std::list<Entity> entities_;
    std::map<std::string, Entity*> entities;
    std::list<std::map<std::string, Entity*>::iterator> entities_to_erase;
    std::map<std::string, int> usedNames;
    std::string name;
};

#endif