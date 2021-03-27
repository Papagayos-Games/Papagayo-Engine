#include "Scene/Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::load(json& j)
{
	string aux = j["name"];
	name = aux;

	if (!j["entities"].is_null() && j["entities"].is_array()) {
		// Si hay un array de entities dentro del json
		vector<json> ents = j["entities"];

		for (json e : ents) {
			// Se recorre el array de entities del json
			// Se crea la entidad correspondiente y se añade al mapa de entidades
			// entities[e["name"]]= cargar entidad
		}
	}

	return true;
}

void Scene::start()
{
	
}

void Scene::update()
{
	// recorrer lista de entidades/componentes
	/*for (pair<string, Entity*> e : entities) {
		// update de la entidad/componente
	}*/
}

string Scene::getName() const
{
	return name;
}

/*Entity* Scene::getEntity(const string& name) {
	map<string, Entity*>::iterator entity = entities.find(name);
	if (entity == entities.end())
		return nullptr;
	else
		return entity->second;
}*/