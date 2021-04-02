#include "Graphics/WindowGenerator.h"

//Includes generales
#include <exception>

//Includes de Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreFileSystemLayer.h>

WindowGenerator* WindowGenerator::instance_ = 0;

using namespace Ogre;

void WindowGenerator::initWindow(std::string name)
{
	const Ogre::RenderSystemList& lRenderSystemList = mRoot_->getAvailableRenderers();
	if (lRenderSystemList.size() == 0) {
		throw std::exception("No se encuentra sistema de render disponible");
	}
	else {
		renderSystem_ = lRenderSystemList[0];
		mRoot_->setRenderSystem(renderSystem_);
	}

	//TEST: Configuracion inicial de la ventana 
	renderWindow_ = mRoot_->initialise(true, name);
	renderWindow_->resize(800, 600);
	renderWindow_->windowMovedOrResized();

	mRoot_->addFrameListener(this);
}

WindowGenerator::WindowGenerator(Root* root, std::string name) : mRoot_(root)
{
	initWindow(name);
}

WindowGenerator* WindowGenerator::getInstance()
{
	if (instance_ == nullptr)
	{
		return nullptr;
	}

	return instance_;
}

bool WindowGenerator::setupInstance(Root* root, std::string name)
{
	if (instance_ == 0)
	{
		instance_ = new WindowGenerator(root, name);
		return true;
	}

	return false;
}

WindowGenerator::~WindowGenerator()
{
	if (renderWindow_ != nullptr) {
		mRoot_->destroyRenderTarget(renderWindow_);
		renderWindow_ = nullptr;
	}

	delete mRoot_;
	mRoot_ = nullptr;
}

inline RenderWindow* WindowGenerator::getRenderWindow()const
{
	return renderWindow_;
}

inline RenderSystem* WindowGenerator::getRenderSystem()const
{
	return renderSystem_;
}
