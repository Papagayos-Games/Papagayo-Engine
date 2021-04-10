#include "Manager.h"
#include "Component.h"
#include "Entity.h"

Manager::Manager() {

}

Manager::~Manager() {

}

std::list<Component*> Manager::getComponents() {
	return compsList;
}

void Manager::destroyAllComponents() {
	for (auto it = compsList.begin(); it != compsList.end(); )
	{
		compsList.erase(it);
		delete* it;
	}
}

bool Manager::destroyComponent(Entity* ent, int compId) {
	//auto it = compsList.find(compId);
	auto it = compsList.begin();
	for (; it != compsList.end(); it++) {
		if ((*it)->getEntity() == ent) {
			delete *it;
			compsList.erase(it);
			return true;
		}
	}
	return false;
}