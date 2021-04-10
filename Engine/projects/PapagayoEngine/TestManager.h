#pragma once
#include "Manager.h"

class TestManager: public Manager {
private:

	enum TestEnumCmpId : size_t {
		test0 = 0,
		test1 = 1
	};

	static TestManager* _instance;

	TestManager* getInstance();

public:
	void addComponent(Entity* ent, int id);
	// TestManager::getInstance()->addComponent(...);
	void start();
	void update();
};

