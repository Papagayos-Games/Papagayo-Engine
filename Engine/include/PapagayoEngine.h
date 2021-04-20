#pragma once

#include <string>
#ifdef _DEBUG
#include "checkML.h"
#endif


class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();
	void run();
private:
	static PapagayoEngine* instance_;
	std::string appName_;
	bool running_ = true;

	PapagayoEngine(const std::string& appName);
	void init();
	void update();
	void pollEvents();


};