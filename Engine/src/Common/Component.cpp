#include "Component.h"

Component::Component(ecs::CmpId id) : id(id) {}

Component::~Component() {}

bool Component::isActive() {
	return active;
}

void Component::setActive(bool act) {
	active = act;
}