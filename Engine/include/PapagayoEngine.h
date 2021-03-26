#pragma once

#include <string>

// resto de includes graphics, physics, etc.

class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	void init();
	bool setupInstance(const std::string& appName);
private:
	PapagayoEngine(const std::string& appName);




	static PapagayoEngine* instance_;
	std::string appName_;
};