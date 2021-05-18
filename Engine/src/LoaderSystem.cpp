

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
		std::string name = fileName;
		Entity* ent = new Entity();
		auto pref = entities[i].find("Prefab");
		if (pref != entities[i].end() && pref.value().is_string()) {
			loadPrefabs(entities[i], ent, name);
		}
		if(!entities[i]["Components"].is_null() && entities[i]["Components"].is_array())
			loadComponents(entities[i]["Components"], ent);

		auto it = entities[i].find("Name");
		if (it != entities[i].end() && it.value().is_string()) {
			name = it.value();
		}
		scene->addEntity(name, ent);
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
		// Comprueba el tipo de componente
		auto it = comps[i].find("Type");
		if (it == comps[i].end() || !it.value().is_string())
			throw std::exception("ERROR: Component type not found\n");
		type = it.value();

		// Comprueba el nombre del componente
		it = comps[i].find("Component");
		if (it == comps[i].end() || !it.value().is_string())
			throw std::exception("ERROR: Component name not found\n");
		component = it.value();
		Component* c;

		// si no se ha cargado este script de lua, añadelo como posible componente
		if (type == "LUA") {
			if (mans[type]->getCompID(component) == -1) {
				LUAManager::getInstance()->addRegistry(component);
			}
		}
		if (!entity->hasComponent(mans[type]->getId(), mans[type]->getCompID(component))){
			c = mans[type]->create(component, entity);
				if (c == nullptr)
					throw std::exception("ERROR: Component couldn't be created, it is not registered\n");
		}
		// Si hay parametros, se cargan; si no, se crea el componente por defecto
		else {
			c = entity->getComponent(mans[type]->getId(), mans[type]->getCompID(component));
		}
		// TO DO: Cargar LUA components si no tienen "Parameters" en el json
		it = comps[i].find("Parameters");
		if (it != comps[i].end() && it.value().is_object()) {

			try { c->load(it.value()); }
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

void LoaderSystem::loadPrefabs(nlohmann::json& pref, Entity* ent, std::string& entName) {
	if (pref.is_null() || !pref.is_object())
		throw std::exception("ERROR: Prefab not found\n");

	auto it = pref.find("Prefab");

	if (it == pref.end() || !it.value().is_string())
		throw std::exception("ERROR: Prefab files not found\n");

	std::string fileName = it.value().get<std::string>();
	std::fstream i(PREFAB_FILE_PATH + fileName + FILE_EXTENSION);

	if (!i.is_open()) {
		throw std::runtime_error("ERROR: Loading scene " + fileName + " failed, file missing\n");
	}

	nlohmann::json prefJson;
	i >> prefJson;

	it = prefJson.find("Components");

	if(it != prefJson.end() && it.value().is_array())
		loadComponents(it.value(), ent);

	it = prefJson.find("Name");
	if (it != prefJson.end() && it.value().is_string())
		entName = it.value();

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

	i.close();
}
