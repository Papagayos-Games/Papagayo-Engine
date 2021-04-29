#pragma once

#ifndef _PAPAENG_PAPAENG_H
#define _PAPAENG_PAPAENG_H

#include <map>
#include <vector>
#include <string>
#ifdef _DEBUG
#include "checkML.h"
#endif
class Manager;

class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();
	void start();
	void run();
	const std::map<std::string, Manager*>& getManagers();
	const std::map<std::string, Manager*>& getManagers() const;
	
private:
	static PapagayoEngine* instance_;
	std::string appName_;
	std::map<std::string, Manager*> manRegistry_;
	bool running_ = true;
	int timer_ = 0;
	PapagayoEngine(const std::string& appName);
	void init();
	void update();
};

#endif