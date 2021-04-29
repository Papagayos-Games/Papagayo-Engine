#pragma once
#include <json.hpp>
class Scene;
class Entity;

class LoaderSystem
{
private:
	void loadComponents(nlohmann::json comps, Entity* entity);
	void loadPrefabs(nlohmann::json pref, Entity* ent);
public:
	std::vector<std::string> loadScenes(std::string fileName);
	void readParameters(std::string dump, std::map<std::string, std::string>& params);
	void loadEntities(std::string fileName, Scene* scene);
};

