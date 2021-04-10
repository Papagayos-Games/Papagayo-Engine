#pragma once
#include "Component.h"

class btCollisionShape;
class Collider : public Component
{
private:
	btCollisionShape* shapeColl = nullptr;
	
public:
	Collider(ecs::CmpId id);
	btCollisionShape* getShape() { return shapeColl; };

	virtual void init() {};
	virtual void update() {};
};

