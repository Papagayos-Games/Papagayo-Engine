#include "..\..\include\Common\CommonManager.h"
#include "..\..\include\Common\CommonManager.h"
#include "Entity.h"
#include "Transform.h"
#include "CommonManager.h"

CommonManager* CommonManager::_instance = nullptr;

CommonManager::CommonManager() : Manager(ManID::Common) {
	registerComponent("Transform", (int)CommonCmpId::TransId, []() -> Transform* { return new Transform(); });
}

CommonManager::~CommonManager() {

}

CommonManager* CommonManager::getInstance() {
	if (!_instance)
		_instance = new CommonManager();
	return _instance;
}

void CommonManager::clean()
{
	_instance->destroyAllComponents();
}

void CommonManager::destroy()
{
	_instance->clean();
	delete _instance;
}

void CommonManager::start() {

}

void CommonManager::update() {

}

void CommonManager::addComponent(Entity* ent, int compId) {
	Component* comp;
	CommonCmpId id = (CommonCmpId)compId;
	switch (id)
	{
	case CommonCmpId::TransId:
		comp = new Transform();
		break;
	default:
		throw "ERROR: Tried to add a non existant Common Component\n";
	}
	if (!comp)
		throw ("ERROR: Common Manager couldn't create a component with an Id: ", compId, "\n");
	_compsList.push_back(comp);
	comp->setEntity(ent);
	ent->addComponent(comp);
}