#include "UISlider.h"
#include "UIManager.h"
#include <glm/glm.hpp>

UISlider::UISlider() : UIComponent((int)UIManager::UICmpId::Slider)
{
}

UISlider::~UISlider()
{
}

void UISlider::init()
{
	position.first = 10;
	position.second = 10;

	size.first = 100;
	size.second = 100;

	name = "SliderDefault";

	uiWindow = UIManager::getInstance()->createSlider(position, size, name);
}

void UISlider::load(const nlohmann::json& params)
{
	auto it = params.find("position");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		position.first = pos[0];
		position.second = pos[1];
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

	//	//TODO: a la constructora de subscriberSlot habria que pasarle el metodo de lua que queramos que haga, ¿como? no se sabeh

	//it = params.find("clickEvent");
	//if (it != params.end()) {
	//	auto _event = it->find("event");
	//	if (_event != it->end()) {
	//		std::string e = _event->get<std::string>();
	//		event_ = new CEGUI::String(e);
	//	}

	//	auto _subs = it->find("subscriber");
	//	if (_subs != it->end()) {
	//		std::string sub = _subs->get<std::string>();
	//		
	//		//subscriberEvent = new CEGUI::SubscriberSlot();
	//	}

	//	uiWindow->subscribeEvent(*event_, *subscriberEvent);
	//}

	uiWindow = UIManager::getInstance()->createSlider(position, size, name);
}
