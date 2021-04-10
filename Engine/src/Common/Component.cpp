#include "Component.h"
#include "Entity.h"
#include "Manager.h"

Component::Component(ecs::CmpId id, Manager* man) : _id(id), _manager(man) {

}

Component::~Component() {
	_entity->removeComponent(_id);
}

void Component::setId(ecs::CmpId id) {
	id = id;
}

ecs::CmpId Component::getId() const {
	return _id;
}

bool Component::isActive() {
	return _active;
}

void Component::setActive(bool act) {
	_active = act;
}

Entity* Component::getEntity() {
	return _entity;
}

void Component::setEntity(Entity* e) {
	_entity = e;
}

Manager* Component::getManager() {
	return _manager;
}