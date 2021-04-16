#include "Managers/RenderManager.h"
#include "Graphics/OgreContext.h"
#include "OgreRoot.h"

#include "Entity.h"
#include "Graphics/MeshComponent.h"

RenderManager* RenderManager::instance_ = nullptr;

RenderManager::RenderManager() : Manager(ManID::Render)
{
	ogreRoot_ = OgreContext::getInstance()->getOgreRoot();
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
		cmp->setEntity(ent);
		break;
	case RenderCmpId::Camera:
		break;
	case RenderCmpId::LastRenderCmpId:
		break;
	default:
		throw "ERROR: Tried to add a non existant Common Component\n";
	}
	if (!cmp)
		throw ("ERROR: Common Manager couldn't create a component with an Id: ", compId, "\n");
	_compsList.push_back(cmp);
	ent->addComponent(cmp);
}

void RenderManager::start()
{
}

void RenderManager::update()
{
	ogreRoot_->renderOneFrame();	//TODO: esto no lo esta lanzando el RenderManager
}
