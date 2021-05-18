#include "Entity.h"
#include "Component.h"
#include "Manager.h"

Entity::Entity() {

}

Entity::~Entity() {
	for (auto it = _componentMap.begin(); it != _componentMap.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2 = it->second.begin()) {
			int id = it2->second->getId();
			//removeComponent(it->first, id);
			if (!removeComponent(it2->second->getManager()->getId(), id))
				throw std::runtime_error("ERROR: Tried to destroy a non existant component while destroying the entity\n");
		}
	}
}

void Entity::start()
{
	for (auto it = _componentMap.begin(); it != _componentMap.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			it2->second->setUp();
		}
	}
}

void Entity::destroy()
{
	for (auto it = _componentMap.begin(); it != _componentMap.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2 = it->second.begin()) {	
			int id = it2->second->getId();
			it2->second->getManager()->destroyComponent(this, id);
		}
	}
}

void Entity::addComponent(Component* comp)
{
	_componentMap[comp->getManager()->getId()][comp->getId()] = comp;
}

const std::string& Entity::getName() const
{
	return name_;
}

void Entity::setName(const std::string& name)
{
	name_ = name;
}

Component* Entity::getComponent(int managerId, int compId)
{
	return _componentMap[managerId][compId];
}

bool Entity::hasComponent(int managerId, int compId) const
{
	auto man = _componentMap.find(managerId);
	if (man != _componentMap.end()) {
		return man->second.find(compId) != man->second.end();
	}
	return false;
}

bool Entity::removeComponent(int managerId, int compId) {
	auto itMaps = _componentMap.find(managerId);
	if (itMaps != _componentMap.end()) {
		auto it = itMaps->second.find(compId);
		if (it != itMaps->second.end()) {
			itMaps->second.erase(it);
			return true;
		}
	}
	return false;
}