#pragma once

#include "json.hpp"

namespace Ogre {
	class Root;
	class FileSystemLayer;
}

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

	static std::string PATH_;
private:
	ResourceManager(const std::string& path);
	void loadPrefabs(const std::string& prefabName);
	void loadFromResourceFile();

	std::string path_;
	json prefabs_;

	static ResourceManager* instance_;
	Ogre::Root* ogreRoot_;
	Ogre::FileSystemLayer* mFSLayer;
};