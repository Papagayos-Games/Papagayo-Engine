#include "UISlider.h"
#include "UIManager.h"

#include "CEGUI/Window.h"
#include "CEGUI/CEGUI.h"

#include <glm/glm.hpp>

UISlider::UISlider() : UIComponent((int)UIManager::UICmpId::Slider)
{
}

UISlider::~UISlider()
{
}

void UISlider::init()
{
	pos.first = 10;
	pos.second = 10;

	size.first = 100;
	size.second = 100;

	name = "SliderDefault";
	type = "Slider";
	uiWindow = UIManager::getInstance()->createSlider(pos, size, name, type);
}

void UISlider::load(const nlohmann::json& params)
{
	//--------------ASIGNACIONES_UI_COMPONENT--------------//
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

	it = params.find("type");
	if (it != params.end()) {
		std::string t = it->get<std::string>();
		type = t;
	}

	//Reposicionamiento para que parezca que el pivote esta
	//en el centro del boton (esto se puede meter en el resto de Widgets)
	//vector2 sizeN = normalizeVector2(size);
	//
	//position.first -= sizeN.first / 2;
	//position.second -= sizeN.second/ 2;

	uiWindow = UIManager::getInstance()->createSlider(pos, size, name, type);

	//------------ASIGNACIONES_UI_IMAGE--------------//

	//Propiedades de la Imagen
	it = params.find("property");
	if (it != params.end()) {
		std::vector<std::vector<std::string>> prop =
			it->get<std::vector<std::vector<std::string>>>();
		for (int i = 0; i < prop.size(); i++) {
			setProperty(prop.at(i).at(0), prop.at(i).at(1));
		}
	}

	it = params.find("active");
	if (it != params.end()) {
		bool ac = it->get<bool>();
		setActive(ac);
	}
}
