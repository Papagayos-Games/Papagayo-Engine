#include "WindowGenerator.h"

//Includes generales
#include <exception>

//Includes de Ogre
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreFileSystemLayer.h>

void WindowGenerator::initWindow()
{
	createRoot();

	//TEST: Configuracion inicial de la ventana 
	renderWindow_ = mRoot_->initialise(true, "Papagayos_Engine");
	renderWindow_->resize(800, 600);
	renderWindow_->windowMovedOrResized();

	mRoot_->addFrameListener(this);
}

void WindowGenerator::createRoot()
{

#ifdef _DEBUG
	mRoot_ = new Root("OgreD/plugins.cfg");
#else
	mRoot_ = new Root("Ogre/plugins.cfg");
#endif

	if (mRoot_ == nullptr) {
		throw std::exception("No se ha podido crear el mRoot");
	}
	else {
		const Ogre::RenderSystemList& lRenderSystemList = mRoot_->getAvailableRenderers();
		if (lRenderSystemList.size() == 0) {
			throw std::exception("No se encuentra sistema de render disponible");
		}
		else {
			renderSystem_ = lRenderSystemList[0];
			mRoot_->setRenderSystem(renderSystem_);
		}
	}
}

WindowGenerator::WindowGenerator()
{
	initWindow();
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

inline Root* WindowGenerator::getOgreRoot()const
{
	return mRoot_;
}

inline RenderWindow* WindowGenerator::getRenderWindow()const
{
	return renderWindow_;
}

inline RenderSystem* WindowGenerator::getRenderSystem()const
{
	return renderSystem_;
}
