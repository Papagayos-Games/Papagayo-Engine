#pragma once
#include "Component.h"
#include <memory>
#include <functional>
#include <string>
#include <map>

/*class ComponentFactory
{
private:
	static ComponentFactory* instance_;

	std::map<std::string, std::function<Component*()>> compsRegistry_;
public:
	static ComponentFactory* getInstance();
	void registerComponent(std::string name, std::function<Component* ()>compConst);
	std::shared_ptr<Component> create(std::string name);
};*/

