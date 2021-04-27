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

	registerComponent("MeshComponent", []() -> MeshComponent* { return new  MeshComponent(); });
	registerComponent("Camera", []() -> Camera* { return new Camera(); });
	registerComponent("LightComponent", []() -> LightComponent* { return new LightComponent(); });
	registerComponent("PlaneComponent", []() -> PlaneComponent* { return new PlaneComponent(); });
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

void RenderManager::addComponent(Entity* ent, int compId)
{
	
	RenderCmpId id = (RenderCmpId)compId;
	Component* cmp = nullptr;
	switch (id)
	{
	case RenderCmpId::Mesh:
		cmp = new MeshComponent();
		break;
	case RenderCmpId::Camera:
		cmp = new Camera();
		break;
	case RenderCmpId::LastRenderCmpId:
		break;
	default:
		throw "ERROR: Tried to add a non existant Common Component\n";
	}
	if (!cmp)
		throw ("ERROR: Common Manager couldn't create a component with an Id: ", compId, "\n");
	_compsList.push_back(cmp);
	cmp->setEntity(ent);
	ent->addComponent(cmp);
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
