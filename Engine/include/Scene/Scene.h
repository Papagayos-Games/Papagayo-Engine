#pragma once

#include <string>
#include <map>
#include <json.hpp>

using json = nlohmann::json;

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	bool load(json& j);
	void start();
	void update();

	string getName() const;
	//Entity* getEntity(const string& name);

private:
	//map<string, Entity*> entities;
	string name;
};

