#include "UIComponent.h"
#include <glm/glm.hpp>
#include "UIManager.h"
#include "CommonManager.h"
#include "Transform.h"
#include "Entity.h"
#include "CEGUI/Window.h"
#include <math.h>

inline glm::vec2 cvt(const vector2& V) {
	return glm::vec2(V.first, V.second);
}

inline vector2  cvt(const glm::vec2& V) {
	return std::pair<float, float>(V.x, V.y);
}

vector2 UIComponent::normalizeVector2(const vector2& v)
{
	float x = std::pow(v.first, 2);
	float y = std::pow(v.second, 2);;
	float sqr = std::sqrt(x + y);
	vector2 vec;
	vec.first = v.first / sqr;
	vec.second = v.second / sqr;
	
	return vec;
}

UIComponent::UIComponent(vector2  position_, vector2 size_, std::string name_, int id) : Component(UIManager::getInstance(), id),
	pos(position_), size(size_), name(name_)
{
}

UIComponent::UIComponent(int id) : Component(UIManager::getInstance(), id)
{

}

UIComponent::~UIComponent()
{
}

void UIComponent::setActive(bool act)
{
	_active = act;
	if (_active && !uiWindow->isVisible()) {
		uiWindow->activate();
	}
	else if(!_active && uiWindow->isVisible()){
		uiWindow->hide();
	}
}

void UIComponent::setPosition(const vector2& p)
{
	pos = p;
	CEGUI::UDim x(pos.first, 0);
	CEGUI::UDim y(pos.second, 0);
	CEGUI::UVector2 pU(x, y);

	uiWindow->setPosition(pU);
}

void UIComponent::setSize(const vector2& s)
{
	size = s;
	CEGUI::UDim x(size.first, 0);
	CEGUI::UDim y(size.second, 0);
	CEGUI::UVector2 sU(x, y);

	uiWindow->setPosition(sU);
}

void UIComponent::setName(const std::string& n)
{
	name = n;
	uiWindow->setName(name);
}

void UIComponent::setProperty(const std::string nameProp, const std::string value)
{
	try
	{
		uiWindow->setProperty(nameProp, value);
	}
	catch (const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
}
