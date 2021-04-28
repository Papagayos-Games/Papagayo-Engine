#pragma once

#ifndef _COMMON_MANAGER_H
#define _COMMON_MANAGER_H

#include <List>
#include <memory>
#include <functional>
#include <string>
#include <map>

class Entity;
class Component;


enum class ManID
{
	Common = 0,
	Physics,
	Render,
	LUA,

	LastManId
};

class Manager {
protected:
	std::map <std::string, std::function<Component* ()>> compsRegistry_;
	std::list<Component*> _compsList;
	ManID _manId;
public:
	Manager(ManID id);
	virtual ~Manager();

	/// <summary>
	/// Anyade un componente a la entidad
	/// </summary>
	/// <param name="compId">
	/// Para pasarle el id del componente hay que pasarle
	/// el id necesario desde su manager respectivo
	/// Ejemplo: desde PhysicsManager hay que pasarle lo siguiente
	///				PhysicsManager::PhysicsCmpId::Nombre
	/// </param>
	virtual void start() = 0;
	virtual void update() = 0;

	std::list<Component*> getComponents();
	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);


	//-- Factory --//
	void registerComponent(std::string name, std::function<Component * ()>compConst);
	Component* create(std::string name, Entity* ent);	//esto puede ser un puntero inteligente
	//-------------//
	int getId();
};

#endif