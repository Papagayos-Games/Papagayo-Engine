#include "UILabel.h"
#include "UIManager.h"

#include "CEGUI/Window.h"
#include "CEGUI/CEGUI.h"

#include <glm/glm.hpp>

UILabel::UILabel() : UIComponent((int)UIManager::UICmpId::Label)
{
}

UILabel::~UILabel()
{
}

void UILabel::init()
{
	pos.first = 15;
	pos.second = 15;

	size.first = 50;
	size.second = 50;

	text = "Label Default";

	name = "LabelDefault";

	uiWindow = UIManager::getInstance()->createLabel(text, pos, size, name);
}

void UILabel::load(const nlohmann::json& params)
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
	//
	//position.first -= sizeN.first / 2;
	//position.second -= sizeN.second/ 2;

	uiWindow = UIManager::getInstance()->createLabel(text, pos, size, name);

	if (!_active) {
		uiWindow->hide();
	}
}
