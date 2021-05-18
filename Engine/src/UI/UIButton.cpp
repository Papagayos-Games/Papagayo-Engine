#include "UIButton.h"
#include "UIManager.h"
#include "CEGUI/String.h"
#include "CEGUI/SubscriberSlot.h"
#include "CEGUI/Window.h"
#include "CEGUI/CEGUI.h"

#include <iostream>
#include <glm/glm.hpp>

UIButton::UIButton() : UIComponent((int)UIManager::UICmpId::Button)
{
}

UIButton::~UIButton()
{
}

void UIButton::init()
{
	pos.first = 0;
	pos.second = 0;

	size.first = 100;
	size.second = 50;

	text = "Boton Default";

	name = "ButtonDefault";

	uiWindow = UIManager::getInstance()->createButton(text, pos, size, name);
	
}

void UIButton::load(const nlohmann::json& params)
{
	auto it = params.find("position");
	if (it != params.end()) {
		std::vector<float> p = it->get<std::vector<float>>();
		pos.first = p[0];
		pos.second = p[1];
	}

	it = params.find("size");
	if (it != params.end()) {
		std::vector<float> s = it->get<std::vector<float>>();
		size.first = s[0];
		size.second = s[1];
	}

	it = params.find("name");
	if (it != params.end()) {
		std::string n = it->get<std::string>();
		name = n;
	}

	it = params.find("text");
	if (it != params.end()) {
		std::string t = it->get<std::string>();
		text = t;
	}

	it = params.find("active");
	if (it != params.end()) {
		bool ac = it->get<bool>();
		_active = ac;
	}

	//Reposicionamiento para que parezca que el pivote esta
	//en el centro del boton (esto se puede meter en el resto de Widgets)
	//vector2 sizeN = normalizeVector2(size);
	
	//position.first -= sizeN.first / 2;
	//position.second -= sizeN.second/ 2;

	uiWindow = UIManager::getInstance()->createButton(text, pos, size, name);
	uiWindow->subscribeEvent(
		CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&UIButton::buttonWasPressed, this));

	if (!_active) {
		uiWindow->hide();
	}
}

void UIButton::buttonWasPressed()
{
	buttonPressed = true;
}

void UIButton::buttonNotPressed()
{
	buttonPressed = false;
}

bool UIButton::getButtonPressed()
{
	return buttonPressed;
}

void UIButton::setText(std::string t)
{
	text = t;
	uiWindow->setText(text);
}
