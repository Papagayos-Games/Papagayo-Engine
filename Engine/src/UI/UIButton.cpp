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
	position.first = 0;
	position.second = 0;

	size.first = 100;
	size.second = 50;

	text = "Boton Default";

	name = "ButtonDefault";

	uiWindow = UIManager::getInstance()->createButton(text, position, size, name);
	
}

void UIButton::load(const nlohmann::json& params)
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

	it = params.find("text");
	if (it != params.end()) {
		std::string t = it->get<std::string>();
		text = t;
	}

	

	//TODO: a la constructora de subscriberSlot habria que pasarle el metodo de lua que queramos que haga, ¿como? no se sabeh

	//it = params.find("clickEvent");
	//if (it != params.end()) {
	//	auto _event = it->find("event");
	//	if (_event != it->end()) {
	//		std::string e = _event->get<std::string>();
	//		event_ = new CEGUI::String(e);
	//
	//		if (event_ == &(CEGUI::String)"changeScene") {
	//
	//			auto scene_ = it->find("scene");
	//			if (scene_ != it->end()) {
	//				scene = scene_->get<std::string>();
	//			}
	//
	//			uiWindow->subscribeEvent(
	//				CEGUI::PushButton::EventClicked,
	//				CEGUI::Event::Subscriber(&UIButton::changeScene, this));
	//		}
	//		
	//	}
	//
	////	auto _subs = it->find("subscriber");
	////	if (_subs != it->end()) {
	////		std::string sub = _subs->get<std::string>();
	////		
	////		//subscriberEvent = new CEGUI::SubscriberSlot();
	//
	////	}
	//
	//uiWindow->subscribeEvent(*event_, *subscriberEvent);
	//}

	//Reposicionamiento para que parezca que el pivote esta
	//en el centro del boton (esto se puede meter en el resto de Widgets)
	//position.first -= size.first / 2;
	//position.second -= size.second/ 2;
	uiWindow = UIManager::getInstance()->createButton(text, position, size, name);
}

void UIButton::onClick()
{
	////provisional hasta hablarlo
	//if (event_ == &(CEGUI::String)"hola") {
	//	//metodo a hacer
	//}
	///*else if{
	//
	//}*/
	////...
	////...
	////...
}

void UIButton::changeScene()
{
	//aqui deberia cambiar a la escena 
}
