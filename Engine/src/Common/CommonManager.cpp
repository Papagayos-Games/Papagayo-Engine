#include "CommonManager.h"

CommonManager* CommonManager::_instance = nullptr;

CommonManager::CommonManager() : Manager(ManID::Common) {

}

CommonManager::~CommonManager() {

}

CommonManager* CommonManager::getInstance() {
	if (!_instance)
		_instance = new CommonManager();
	return _instance;
}

void CommonManager::start() {

}

void CommonManager::update() {

}

void CommonManager::addComponent(Entity* ent, int compId) {

}