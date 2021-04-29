#include "Manager.h"
#include "Component.h"
#include "Entity.h"

Manager::Manager(ManID id) : _manId(id) {

}

Manager::~Manager() {
	destroyAllComponents();
}

std::list<Component*> Manager::getComponents() {
	return _compsList;
}

void Manager::destroyAllComponents() {
	for (auto it = _compsList.begin(); it != _compsList.end(); it = _compsList.begin())
	{
		delete* it;
		_compsList.erase(it);
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

void Manager::registerComponent(std::string name, std::function<Component * ()> compConst)
{
	compsRegistry_[name] = compConst;
}

Component* Manager::create(std::string name, Entity* ent)
{
	Component* comp = nullptr;
	auto it = compsRegistry_.find(name);
	if (it != compsRegistry_.end())
		comp = it->second();
	if (comp != nullptr) {
		_compsList.push_back(comp);
		comp->setEntity(ent);
		return comp;
	}
	return nullptr;
}