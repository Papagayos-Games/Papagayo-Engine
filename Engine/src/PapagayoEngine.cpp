#include "PapagayoEngine.h"

#include <stdexcept>

#include <iostream>

#include "Ogre.h"
//#include <OgreWindowEventUtilities.h>
//#include <OgreRenderWindow.h>

//#include "OgreViewport.h"

#include "Graphics/WindowGenerator.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"




PapagayoEngine* PapagayoEngine::instance_ = nullptr;

PapagayoEngine::PapagayoEngine(const std::string& appName) : appName_(appName) {
}

PapagayoEngine::~PapagayoEngine()
{
}

PapagayoEngine* PapagayoEngine::getInstance()
{
	if (instance_ == nullptr)
		if(!setupInstance("PAPAGAYO ENGINE"))
			throw "ERROR: PapagayoEngine couldn't be created\n";
	return instance_;
}


bool PapagayoEngine::setupInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		instance_ = new PapagayoEngine(appName);
		return true;
	}

	return false;
}

void PapagayoEngine::clean()
{
	// se borrarian todos los managers del motor
	
	SceneManager::getInstance()->clean();
	ResourceManager::getInstance()->clean();
	//WindowGenerator::getInstance()->clean();

	delete instance_;
}

void PapagayoEngine::init()
{
	createRoot();

	// iniciar resto de singletons/managers
	try { ResourceManager::setupInstance("assets/"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceManager init fail \n" + (std::string)e.what() + "\n");
	}
	try { WindowGenerator::setupInstance(getOgreRoot(), appName_); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("WindowGenerator init fail \n" + (std::string)e.what() + "\n");
	}
	try { SceneManager::setupInstance(); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");
	}
}

void PapagayoEngine::createRoot()
{
#ifdef _DEBUG
	ogreRoot_ = new Ogre::Root("OgreD/plugins.cfg");
#else
	ogreRoot_ = new Ogre::Root("Ogre/plugins.cfg");
#endif

	if (ogreRoot_ == nullptr) {
		throw std::exception("No se ha podido crear el mRoot");
	}
}


void PapagayoEngine::update()
{
	//std::cout << "Updating\n";
	ogreRoot_->renderOneFrame();
	
}

inline Ogre::Root* PapagayoEngine::getOgreRoot() const
{
	return ogreRoot_;
}

void PapagayoEngine::run() {
	init();
	// ciclo principal de juego
	while(running_){
		update();	
	}
}