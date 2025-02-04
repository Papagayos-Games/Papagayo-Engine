#include "Component.h"
#include "Entity.h"
#include "Manager.h"

Component::Component(Manager* man, int id) : _manager(man), _id(id) {

}

Component::~Component() {
	if (_entity)
		_entity->removeComponent(_manager->getId(), _id);
}

void Component::setId(int id) {
	_id = id;
}

int Component::getId() const {
	return _id;
}

bool Component::isActive() const {
	return _active;
}

void Component::setActive(bool act) {
	_active = act;
}

Entity* Component::getEntity() const {
	return _entity;
}

void Component::setEntity(Entity* e) {
	_entity = e;
}

Manager* Component::getManager() const {
	return _manager;
}

void Component::setUp() {

}