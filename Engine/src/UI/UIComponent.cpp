#include "UIComponent.h"
#include <glm/glm.hpp>
#include "UIManager.h"
#include "CommonManager.h"
#include "Transform.h"
#include "Entity.h"
#include "CEGUI/Window.h"


inline glm::vec2 cvt(const vector2& V) {
	return glm::vec2(V.first, V.second);
}

inline vector2  cvt(const glm::vec2& V) {
	return std::pair<float, float>(V.x, V.y);
}

UIComponent::UIComponent(vector2  position_, vector2 size_, std::string name_, int id) : Component(UIManager::getInstance(), id),
	position(position_), size(size_), name(name_)
{
}

UIComponent::UIComponent(int id) : Component(UIManager::getInstance(), id)
{

}

UIComponent::~UIComponent()
{
}

void UIComponent::setUp()
{
	canvasTR = static_cast<Transform*>(_entity->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));

	position.first += canvasTR->getPos().x;
	position.second += canvasTR->getPos().y;

	glm::vec2 aux = cvt(position);

	CEGUI::UDim x(aux.x, 0);
	CEGUI::UDim y(aux.y, 0);

	uiWindow->setPosition(CEGUI::UVector2(x, y));
}
