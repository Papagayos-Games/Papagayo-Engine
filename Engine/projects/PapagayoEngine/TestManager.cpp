#include "TestManager.h"

TestManager* TestManager::_instance = nullptr;

TestManager* TestManager::getInstance() {
	if (!_instance)
		_instance = new TestManager();
	return _instance;
}

void TestManager::start() {
	_instance->getComponents();
}

void TestManager::update() {

}

void TestManager::addComponent(Entity* ent, int id) {

}