#include "Manager.h"
#include "Component.h"
#include "Entity.h"

Manager::Manager(ManID id) : _manId(id) {

}

Manager::~Manager() {
	destroyAllComponents();
}

int Manager::getCompID(const std::string& s)
{
	auto e = enum_map_.find(s);
	if (e != enum_map_.end())
		return e->second;
	return -1;
}

const std::list<Component*>& Manager::getComponents() {
	return _compsList;
}

const std::list<Component*>& Manager::getComponents() const {
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

int Manager::getId() const {
	return (int)_manId;
}

void Manager::registerComponent(const std::string& name, int id, std::function<Component * ()> compConst)
{
	enum_map_[name] = id;
	compsRegistry_[id] = compConst;
}

Component* Manager::create(const std::string& name, Entity* ent)
{
	Component* comp = nullptr;
	auto it = compsRegistry_.find(enum_map_[name]);
	if (it != compsRegistry_.end())
		comp = it->second();
	if (comp != nullptr) {
		_compsList.push_back(comp);
		comp->setEntity(ent);
		return comp;
	}
	return nullptr;
}