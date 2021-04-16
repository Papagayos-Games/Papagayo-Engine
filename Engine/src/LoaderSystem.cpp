#include "LoaderSystem.h"

#include "Scene/Scene.h"
#include "Entity.h"
#include "PapagayoEngine.h"
#include "Manager.h"

#include <fstream>
#include <string>
#include <exception>
//#include "Scene.h"
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
	json j;
	i >> j;
	// -- -- //
	json entities = j["Entities"];
	if (entities.is_null() || !entities.is_array())
		throw std::exception("ERROR: Entities not found\n");

	size_t entSize = entities.size();
	
	for (int i = 0; i < entSize; i++) {
		Entity* ent = new Entity();
		loadComponents(entities[i]["Components"], ent);		
	}
	
}

void LoaderSystem::loadComponents(json comps, Entity* entity)
{
	if (comps.is_null() || !comps.is_array())
		throw std::exception("ERROR: Components not found\n");
	int compSize = comps.size();
	
	auto mans = PapagayoEngine::getInstance()->getManagers();
	json params;
	for (int i = 0; i < compSize; i++) {
		params = comps[i]["Parameters"];
		if (params.is_null() || !params.is_object())
			throw std::exception("ERROR: Component parameters not found\n");

		std::map<std::string, std::string> p;
		readParameters(comps[i]["Parameters"].dump(), p);

		Component* c = mans[comps[i]["Type"]]->create(comps[i]["Component"], p, entity);
		if (c == nullptr)
			throw std::exception("ERROR: Component couldn't be created, it is not registered\n");
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
