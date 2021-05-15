

#include "LoaderSystem.h"

#include "Scene/Scene.h"
#include "Entity.h"
#include "Component.h"
#include "PapagayoEngine.h"
#include "Manager.h"

#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include <LUA/LUAManager.h>
//#include "Scene.h"

// nlohmann::json;

std::vector<std::string> LoaderSystem::loadScenes(const std::string& fileName)
{
	std::fstream i(fileName);
	if (!i.is_open()) {
		throw std::runtime_error("ERROR: Loading scene " + fileName + " failed, file missing\n");
	}
	nlohmann::json j;
	i >> j;
	nlohmann::json sceneFiles = j["SceneFiles"];
	if (sceneFiles.is_null() || !sceneFiles.is_array())
		throw std::exception("ERROR: Scene files not found\n");
	std::vector<std::string> scenes = sceneFiles.get<std::vector<std::string>>();
	i.close();
	return scenes;
}


void LoaderSystem::loadEntities(const std::string& fileName, Scene* scene)
{

	std::fstream i(SCENES_FILE_PATH + fileName + FILE_EXTENSION);	// TO DO: poner la ruta definitiva cuando este la carpeta final
	if (!i.is_open()) {
		throw std::runtime_error("ERROR: Loading scene " + fileName + " failed, file missing\n");
	}
	nlohmann::json j;
	i >> j;
	// -- -- //
	nlohmann::json entities = j["Entities"];
	if (entities.is_null() || !entities.is_array())
		throw std::exception("ERROR: Entities not found\n");

	size_t entSize = entities.size();

	for (int i = 0; i < entSize; i++) {
		Entity* ent = new Entity();
		nlohmann::json prefab = entities[i]["Prefab"];
		if (!prefab.is_null() && prefab.is_string())
			loadPrefabs(entities[i], ent);
		if(!entities[i]["Components"].is_null() && entities[i]["Components"].is_array())
			loadComponents(entities[i]["Components"], ent);
		scene->addEntity(fileName, ent);	// TO DO: procesar el nombre de las entidades desde json
	}

	i.close();
}

void LoaderSystem::loadComponents(const nlohmann::json& comps, Entity* entity)
{
	if (comps.is_null() || !comps.is_array())
		throw std::exception("ERROR: Components not found\n");
	int compSize = comps.size();

	auto mans = PapagayoEngine::getInstance()->getManagers();
	nlohmann::json type;
	nlohmann::json component;
	nlohmann::json params;
	for (int i = 0; i < compSize; i++) {
		//std::map<std::string, std::string> p;
		//readParameters(comps[i]["Parameters"].dump(), p);
		type = comps[i]["Type"];
		if (type.is_null() || !type.is_string())
			throw std::exception("ERROR: Component type not found\n");

		component = comps[i]["Component"];
		if (component.is_null() || !component.is_string())
			throw std::exception("ERROR: Component name not found\n");
		Component* c;
		if (!entity->hasComponent(mans[type]->getId(), mans[type]->getCompID(component))){
			c = mans[type]->create(component, entity);
				if (c == nullptr)
					throw std::exception("ERROR: Component couldn't be created, it is not registered\n");
		}
		// Si hay parametros, se cargan; si no, se crea el componente por defecto
		else {
			c = entity->getComponent(mans[type]->getId(), mans[type]->getCompID(component));
		}
		params = comps[i]["Parameters"];
		if (!params.is_null() && params.is_object()) {

			try { c->load(params); }
			catch (std::exception e) {
				//resetear los valores del componente si hay algun parametro con un formato erroneo
				std::cout << "WARNING: Component " + component.get<std::string>() + " parameters are wrong, reseting to default\n";
				c->init();
				//throw std::exception("WARNING: Component parametrs are wrong\n");
			}
		}

		entity->addComponent(c);
	}
}

// Deserialize parameters	
void LoaderSystem::readParameters(std::string& dump, std::map<std::string, std::string>& params)
{
	std::string delimiter = "\"";

	size_t pos = 1;
	std::string key;
	std::string value;
	dump.erase(0, pos + delimiter.length());
	while ((pos = dump.find(delimiter)) != std::string::npos) {
		key = dump.substr(0, pos);
		dump.erase(0, pos + delimiter.length() + 1);
		pos = dump.find(delimiter);
		value = dump.substr(0, pos - 1);
		dump.erase(0, pos + delimiter.length());
		params[key] = value;
	}
	if (params.size() > 0) {
		auto it = --params.end();
		it->second.pop_back();
	}
}

void LoaderSystem::loadPrefabs(nlohmann::json& pref, Entity* ent) {
	if (pref.is_null() || !pref.is_object())
		throw std::exception("ERROR: Prefab not found\n");

	if (pref["Prefab"].is_null() || !pref["Prefab"].is_string())
		throw std::exception("ERROR: Prefab files not found\n");

	std::string fileName = pref["Prefab"].get<std::string>();
	std::fstream i(PREFAB_FILE_PATH + fileName + FILE_EXTENSION);

	if (!i.is_open()) {
		throw std::runtime_error("ERROR: Loading scene " + fileName + " failed, file missing\n");
	}

	nlohmann::json prefJson;
	i >> prefJson;

	/*if (!pref["Arguments"].is_null() && pref["Arguments"].is_array()) {
		nlohmann::json args = pref["Arguments"];
		int argSize = args.size();

		for (int i = 0; i < argSize; i++) {
			nlohmann::json type = args[i]["Type"];
			if (type.is_null() || !type.is_string())
				throw std::exception("ERROR: Component type not found\n");

			nlohmann::json component = args[i]["Component"];
			if (component.is_null() || !component.is_string())
				throw std::exception("ERROR: Component name not found\n");

			for (nlohmann::json::iterator it = prefJson["Components"].begin(); it != prefJson["Components"].end(); ++it) {
				
				if (it.value()["Type"] == type && it.value()["Component"] == component) {

					for (auto p : args[i]["Parameters"].items())
					{
						it.value()["Parameters"][p.key()] = p.value();
					}
					break;
				}
				std::cout << *it << '\n';
			}
		}
	}*/
	if(!prefJson["Components"].is_null() && prefJson["Components"].is_array())
		loadComponents(prefJson["Components"], ent);
	// ya funciona sin parametros individuales

	i.close();
}

void LoaderSystem::loadPrefabByName(std::string fileName, Entity* ent)
{
	std::fstream i(PREFAB_FILE_PATH + fileName + FILE_EXTENSION);

	if (!i.is_open()) {
		throw std::runtime_error("ERROR: Loading scene " + fileName + " failed, file missing\n");
	}

	nlohmann::json prefJson;
	i >> prefJson;

	loadComponents(prefJson["Components"], ent);
	// ya funciona sin parametros individuales

	i.close();
}
