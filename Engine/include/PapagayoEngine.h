#pragma once

#include <string>

// resto de includes graphics, physics, etc.

class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();

	void init();
	void initTestScene();
	void update();
private:
	PapagayoEngine(const std::string& appName);

	std::string appName_;

	static PapagayoEngine* instance_;
};