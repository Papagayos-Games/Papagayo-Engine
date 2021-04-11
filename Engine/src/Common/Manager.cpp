#include "Manager.h"
#include "Component.h"
#include "Entity.h"

Manager::Manager(ManID id) : _manId(id) {

}

Manager::~Manager() {

}

std::list<Component*> Manager::getComponents() {
	return _compsList;
}

void Manager::destroyAllComponents() {
	for (auto it = _compsList.begin(); it != _compsList.end(); )
	{
		_compsList.erase(it);
		delete* it;
	}
}

bool Manager::destroyComponent(Entity* ent, int compId) {
	auto it = _compsList.begin();
	for (; it != _compsList.end(); it++) {
		if ((*it)->getEntity() == ent) {
			delete *it;
			_compsList.erase(it);
			return true;
		}
	}
	return false;
}

int Manager::getId() {
	return (int)_manId;
}