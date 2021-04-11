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
	TestManager();
	~TestManager();
public:
	void addComponent(Entity* ent, int compId);
	// TestManager::getInstance()->addComponent(...);
	void start();
	void update();
};

