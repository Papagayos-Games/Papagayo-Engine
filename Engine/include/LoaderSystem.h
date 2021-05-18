#pragma once

#ifndef _PAPAENG_LOADERSYS_H
#define _PAPAENG_LOADERSYS_H

#include <json.hpp>
class Scene;
class Entity;

class LoaderSystem
{
private:
	const std::string PREFAB_FILE_PATH = "Prefabs/";
	const std::string SCENES_FILE_PATH = "Scenes/";
	const std::string FILE_EXTENSION = ".json";
	 
	void loadComponents(const nlohmann::json& comps, Entity* entity);
	void readParameters(std::string& dump, std::map<std::string, std::string>& params);
public:
	void loadPrefabs(nlohmann::json& pref, Entity* ent, std::string& entName);
	void loadPrefabByName(std::string fileName, Entity* ent);
	std::vector<std::string> loadScenes(const std::string& fileName);
	void loadEntities(const std::string& fileName, Scene* scene);
};

#endif