#include "Entity.h"
#include "Component.h"
#include "Manager.h"

Entity::Entity() {

}

Entity::~Entity() {
	for (auto it = componentMap.begin(); it != componentMap.end(); )
	{
		if (!it->second->getManager()->destroyComponent(this, it->first))
			throw "ERROR: Tried to destroy a non existant component while destroying the entity\n";
	}
}

void Entity::addComponent(Component* comp)
{
	ecs::CmpId id = comp->getId();
	componentMap[id] = comp;
}

Component* Entity::getComponent(ecs::CmpId id)
{
	return componentMap[id];
}

bool Entity::hasComponent(ecs::CmpId id)
{
	return componentMap.count(id);
}

bool Entity::removeComponent(ecs::CmpId id) {
	auto it = componentMap.find(id);
	if (it != componentMap.end()) {
		componentMap.erase(it);
		return true;
	}
	return false;
}