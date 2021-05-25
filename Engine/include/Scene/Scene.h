#pragma once

#ifndef _PAPAENG_SCENE_H
#define _PAPAENG_SCENEH

#include <string>
#include <list>
#include <map>
#include <vector>
#include <iterator>

class Entity;
class Component;

class Scene
{
public:
    const char SPECIAL_CHAR = '_';

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
    std::list<Entity*>& getAllEntitiesWith(const std::string& name);

private:

    // para identificar con un nombre especifico
    std::map<std::string, Entity*> entities;

    // para borrar fuera del bucle principal
    std::list<std::map<std::string, Entity*>::iterator> entities_to_erase;

    // para obtener todas las entidades con el mismo nombre general, no especifico
    std::map<std::string, std::list<Entity*>> pool_name;
    
    // para saber cuantas veces se ha instanciado una entidad con el mismo nombre
    std::map<std::string, int> usedNames;

    // nombre de la escena
    std::string name;

    static std::list<Entity*> nullList;
};

#endif