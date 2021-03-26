#pragma once

#include <string>
#include <map>

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void start();
	void update();

	string getName() const;

private:
	//map<string, Entity*> entities;
	string name;
};

