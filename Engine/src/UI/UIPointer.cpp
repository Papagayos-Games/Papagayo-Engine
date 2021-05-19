#include "UIPointer.h"
#include "UIManager.h"
#include <glm/glm.hpp>

UIPointer::UIPointer() : Component(UIManager::getInstance(), (int)UIManager::UICmpId::Pointer)
{

}

UIPointer::~UIPointer()
{
}

void UIPointer::init()
{
	pointer = "TaharezLook/GreenArrow";
	visible = true;

	UIManager::getInstance()->setMouseImage(pointer);
	UIManager::getInstance()->setMouseVisibility(visible);
}

void UIPointer::load(const nlohmann::json& params)
{
	auto it = params.find("pointerImage");
	if (it != params.end()) {
		std::string i = it->get<std::string>();
		pointer = i;
	}

	it = params.find("visible");
	if (it != params.end()) {
		bool v = it->get<bool>();
		visible = v;
	}

	UIManager::getInstance()->setMouseImage(pointer);
	UIManager::getInstance()->setMouseVisibility(visible);
}
