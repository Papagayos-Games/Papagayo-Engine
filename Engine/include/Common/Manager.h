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
	UI,

	LastManId
};

class Manager {
protected:
	std::map <std::string, int> enum_map_;
	std::map <int, std::function<Component* ()>> compsRegistry_;
	std::list<Component*> _compsList;
	ManID _manId;
public:
	Manager(ManID id);
	virtual ~Manager();
	int getCompID(const std::string& s);
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
	virtual void update(float deltaTime) = 0;

	const std::list<Component*>& getComponents();
	const std::list<Component*>& getComponents() const;

	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);

	//-- Factory --//
	void registerComponent(const std::string& name, int id, std::function<Component * ()>compConst);
	Component* create(const std::string& name, Entity* ent);	//esto puede ser un puntero inteligente
	//-------------//

	int getId();
	int getId() const;
};

#endif