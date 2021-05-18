#include "UIImage.h"
#include "UIManager.h"

#include "CEGUI/Window.h"
#include "CEGUI/CEGUI.h"

#include <glm/glm.hpp>

UIImage::UIImage() : UIComponent((int)UIManager::UICmpId::Image)
{
}

UIImage::~UIImage()
{
}

void UIImage::init()
{
	pos.first = 35;
	pos.second = 35;

	size.first = 50;
	size.second = 50;

	image = "peblo.png";

	name = "ImageDefault";

	uiWindow = UIManager::getInstance()->createImage(image, pos, size, name);
}

void UIImage::load(const nlohmann::json& params)
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

	it = params.find("image");
	if (it != params.end()) {
		std::string i = it->get<std::string>();
		image = i;
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

	uiWindow = UIManager::getInstance()->createImage(image, pos, size, name);

	if (!_active) {
		uiWindow->hide();
	}
}
