#include "Entity.h"

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
