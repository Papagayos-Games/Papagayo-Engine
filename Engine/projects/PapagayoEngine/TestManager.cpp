#include "TestManager.h"

TestManager* TestManager::_instance = nullptr;

TestManager::TestManager() : Manager(0) {

}

TestManager::~TestManager() {

}

TestManager* TestManager::getInstance() {
	if (!_instance)
		_instance = new TestManager();
	return _instance;
}

void TestManager::start() {

}

void TestManager::update() {

}

void TestManager::addComponent(Entity* ent, int compId) {

}