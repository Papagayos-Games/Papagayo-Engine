#include "ComponentFactory.h"



/*ComponentFactory* ComponentFactory::getInstance()
{
	if (!instance_)
		instance_ = new ComponentFactory();
	return instance_;
}

void ComponentFactory::registerComponent(std::string name, std::function<Component *()> compConst)
{
	compsRegistry_.at(name) = compConst;
}

std::shared_ptr<Component> ComponentFactory::create(std::string name)
{
	Component *comp = nullptr;
	auto it = compsRegistry_.find(name);
	if (it != compsRegistry_.end())
		comp = it->second();
	if (comp != nullptr)
		return std::shared_ptr<Component>(comp);
	return nullptr;
}
*/