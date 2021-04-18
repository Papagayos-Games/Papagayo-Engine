

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
//#include "Scene.h"

// nlohmann::json;

void LoaderSystem::loadScenes(std::string fileName)
{
}


void LoaderSystem::loadEntities(std::string fileName/*, Scene* scene*/)
{
	//-- se puede cargar el json previamente y pasarle sus valores cen estos metodos --//
	std::fstream i(fileName);
	if (!i.is_open()) {
		throw "ERROR: Loading scene " + fileName + " failed, file missing\n";
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
		loadComponents(entities[i]["Components"], ent);		
	}
	
}

void LoaderSystem::loadComponents(nlohmann::json comps, Entity* entity)
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
		if(type.is_null() || !type.is_string())
			throw std::exception("ERROR: Component type not found\n");

		component = comps[i]["Component"];
		if (component.is_null() || !component.is_string())
			throw std::exception("ERROR: Component name not found\n");

		Component* c = mans[type]->create(component, entity);
		if (c == nullptr)
			throw std::exception("ERROR: Component couldn't be created, it is not registered\n");

		// Si hay parametros, se cargan; si no, se crea el componente por defecto
		
		params = comps[i]["Parameters"];
		if (!params.is_null() && params.is_object()) {
			
			try { c->load(params); }
			catch(std::exception e){
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
void LoaderSystem::readParameters(std::string dump, std::map<std::string, std::string>& params)
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
