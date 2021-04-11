#include "Entity.h"
#include "Component.h"
#include "Manager.h"

Entity::Entity() {

}

Entity::~Entity() {
	for (auto it = _componentMap.begin(); it != _componentMap.end(); it++)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end();) {
			if (!it2->second->getManager()->destroyComponent(this, it->first))
				throw "ERROR: Tried to destroy a non existant component while destroying the entity\n";
		}
	}
}

void Entity::addComponent(Component* comp)
{
	_componentMap[comp->getManager()->getId()][comp->getId()] = comp;
}

Component* Entity::getComponent(int managerId, int compId)
{
	return _componentMap[managerId][compId];
}

bool Entity::hasComponent(int managerId, int compId)
{
	return _componentMap[managerId].count(compId);
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