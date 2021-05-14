#include "..\..\include\Graphics\OgreContext.h"
#include "OgreContext.h"
#include <checkML.h>
#include "RTShaderTecnhiqueResolveListener.h"
#include "WindowGenerator.h"
//#include "OgrePlane.h"
#include <checkML.h>
#include "OgreRenderTarget.h"

#include <Ogre.h>
#include <OgreFileSystemLayer.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <OgreSTBICodec.h>
#include <OgreLight.h>		//TOERASE

#include "SDL.h"
#include <iostream>

OgreContext* OgreContext::instance_ = nullptr;

OgreContext::OgreContext(const std::string& appName) {
	appName_ = appName;
	init();
 }

OgreContext* OgreContext::getInstance()
{
	if (instance_ == nullptr)
		if (!setupInstance("PAPAGAYO ENGINE"))
			throw "ERROR: OgreContext couldn't be created\n";
	return instance_;
}

bool OgreContext::setupInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		instance_ = new OgreContext(appName);
		return true;
	}

	return false;
}

void OgreContext::createRoot()
{
#ifdef _DEBUG
	ogreRoot_ = new Ogre::Root("OgreD/plugins.cfg", "OgreD/ogre.cfg");
#else
	ogreRoot_ = new Ogre::Root("Ogre/plugins.cfg", "Ogre/ogre.cfg");
#endif

	if (ogreRoot_ == nullptr) {
		throw std::exception("No se ha podido crear el mRoot");
	}

	Ogre::STBIImageCodec::startup();

	ogreRoot_->restoreConfig();
	ogreRoot_->initialise(false);
}

void OgreContext::createSceneManager()
{
	ogreSceneManager_ = ogreRoot_->createSceneManager();
	ogreSceneManager_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreContext::setupRTShaderGenerator()
{
	try {
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			//Cogemos la instancia
			mShaderGenerator_ = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
			mShaderGenerator_->addSceneManager(ogreSceneManager_);

			//Resolutor de mallas 
			mMaterialListener_ = new RTShaderTecnhiqueResolveListener(mShaderGenerator_);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialListener_);

			// Add the shader libs resource location.
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				"media", "FileSystem");
		}
		else
			throw std::runtime_error("RTShader has not been initialized\n");
	}
	catch (const std::exception & e)
	{
		throw std::runtime_error("Fallo al inicializar el RTShader\n" + (std::string)e.what() + "\n");
	}
}

void OgreContext::clean()
{
	delete instance_;
}

void OgreContext::setSkyPlane(const std::string& materialName, const Ogre::Plane& plane, int width, int height, float bow)
{
		ogreSceneManager_->setSkyPlane(true,plane, materialName, 1, 1, true, bow, width, height);	
}

void OgreContext::init()
{
	createRoot();

	SDL_Init(SDL_INIT_EVERYTHING);

	try { WindowGenerator::setupInstance(getOgreRoot(), appName_); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("WindowGenerator init fail \n" + (std::string)e.what() + "\n");
	}

	createSceneManager();
	loadFromResourceFile();
	setupRTShaderGenerator();
}

void OgreContext::loadFromResourceFile()
{
	// create a Ogre::ConfigFile object and use it to parse our cfg file

	Ogre::ConfigFile cf;
#ifdef _DEBUG
	std::string mResourcesCfg_ = "OgreD/resources.cfg";
#else
	std::string mResourcesCfg_ = "Ogre/resources.cfg";
#endif
	cf.load(mResourcesCfg_);

	// Filesystem, Zip, etc.)

	// allow us to iterate through all of the sections discovered by the parser
	Ogre::ConfigFile::SettingsBySection_ secIt = cf.getSettingsBySection();

	// Ogre::MaterialManager::getSingleton().initialise();
	// Ogre::ParticleSystemManager::getSingleton()._createRenderer(
	// mRoot->getRenderSystem()->getName());

	// iterate through all of the results.
	for (auto it : secIt) {
		Ogre::String secName = it.first;
		// ask for another iterator that will let us iterate through the items
		// in each section
		Ogre::ConfigFile::SettingsMultiMap* settings = &it.second;
		Ogre::ConfigFile::SettingsMultiMap::iterator it2;

		// scan through each item with this iterator
		for (it2 = settings->begin(); it2 != settings->end(); ++it2) {
			// unpack each pair
			Ogre::String locType = it2->first; // location type of this resource
			Ogre::String name = it2->second;   // the path

			// add this location to our ResourceGroupManager
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				name, locType, secName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

OgreContext::~OgreContext()
{
	mShaderGenerator_->removeSceneManager(ogreSceneManager_);

	// destroy RTShader system.
	if (mShaderGenerator_ != nullptr) {
		Ogre::RTShader::ShaderGenerator::getSingleton().destroy();
		mShaderGenerator_ = nullptr;
	}

	//Destruir ventana
	WindowGenerator::getInstance()->clean();

	//Destruir FileSystemLayer
	delete mFSLayer_;	

	//Destruir SceneManager
	if (ogreRoot_ != nullptr)ogreRoot_->destroySceneManager(ogreSceneManager_);

	//Destruir root
	if (ogreRoot_ != nullptr)delete ogreRoot_;
	ogreRoot_ = nullptr;

	//Destruir RTShaderSystem;
	delete  mMaterialListener_;
}

Ogre::Root* OgreContext::getOgreRoot()
{
	return ogreRoot_;
}

Ogre::Root* OgreContext::getOgreRoot() const
{
	return ogreRoot_;
}

Ogre::SceneManager* OgreContext::getSceneManager()
{
	return ogreSceneManager_;
}

Ogre::SceneManager* OgreContext::getSceneManager() const
{
	return ogreSceneManager_;
}

Ogre::RenderTarget* OgreContext::getRenderTarget() const {
	return ogreRoot_->getRenderTarget(WindowGenerator::getInstance()->getRenderWindow()->getName());
}

Ogre::RenderWindow* OgreContext::getRenderWindow() const
{
	return WindowGenerator::getInstance()->getRenderWindow();
}
