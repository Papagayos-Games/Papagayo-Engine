#pragma once
#include <json.hpp>
class Scene;
class Entity;

class LoaderSystem
{
public:
	std::vector<std::string> loadScenes(std::string fileName);
	void loadEntities(std::string fileName, Scene* scene);
	void loadComponents(nlohmann::json comps, Entity* entity);
	void readParameters(std::string dump, std::map<std::string, std::string>& params);
};

