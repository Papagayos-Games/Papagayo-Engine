#pragma once

#include "json.hpp"

using json = nlohmann::json;

class ResourceManager {
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	static bool setupInstance(const std::string& path);
	static void clean();

	void init();

	json getSceneFile(const std::string& sceneName);
	json getPrefabs();

private:
	ResourceManager(const std::string& path);
	void loadPrefabs(const std::string& prefabName);

	std::string path_;
	json prefabs_;

	static ResourceManager* instance_;
};