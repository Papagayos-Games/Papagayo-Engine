#include "Managers/RenderManager.h"
#include "PapagayoEngine.h"

#include "OgreRoot.h"

RenderManager* RenderManager::instance_ = nullptr;

RenderManager::RenderManager()
{
	ogreRoot_ = PapagayoEngine::getInstance()->getOgreRoot();
}

RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;

	return instance_;
}

bool RenderManager::setupInstance()
{
	if (instance_ == nullptr) {
		instance_ = new RenderManager();
		return true;
	}

	return false;
}

void RenderManager::clean()
{
	delete instance_;
}

void RenderManager::update()
{
	ogreRoot_->renderOneFrame();
}
