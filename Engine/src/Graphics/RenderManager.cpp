#include "RenderManager.h"
#include "OgreContext.h"
#include <checkML.h>
#include "OgreRoot.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "LightComponent.h"
#include "PlaneComponent.h"

RenderManager* RenderManager::instance_ = nullptr;

RenderManager::RenderManager() : Manager(ManID::Render)
{
	ogreRoot_ = OgreContext::getInstance()->getOgreRoot();

	registerComponent("MeshComponent", (int)RenderCmpId::Mesh,[]() -> MeshComponent* { return new  MeshComponent(); });
	registerComponent("Camera", (int)RenderCmpId::Camera, []() -> Camera* { return new Camera(); });
	registerComponent("LightComponent", (int)RenderCmpId::Light, []() -> LightComponent* { return new LightComponent(); });
	registerComponent("PlaneComponent", (int)RenderCmpId::Plane, []() -> PlaneComponent* { return new PlaneComponent(); });
}

RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::getInstance()
{
	if (!instance_)
		instance_ = new RenderManager();
	return instance_;
}

void RenderManager::start()
{
	for (Component* cmp : _compsList)
	{
		cmp->setUp();
	}
}

void RenderManager::update()
{
	ogreRoot_->renderOneFrame();	//TODO: esto no lo esta lanzando el RenderManager
	for (Component* cmp : _compsList)
	{
		cmp->update();
	}
}
