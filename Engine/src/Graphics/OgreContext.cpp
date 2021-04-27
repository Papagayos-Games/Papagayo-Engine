#include "..\..\include\Graphics\OgreContext.h"
#include "OgreContext.h"
#include <checkML.h>
#include "RTShaderTecnhiqueResolveListener.h"
#include "WindowGenerator.h"
#include "OgrePlane.h"
#include <checkML.h>

#include <Ogre.h>
#include <OgreFileSystemLayer.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <OgreLight.h>		//TOERASE

#include "SDL.h"


OgreContext* OgreContext::instance_ = nullptr;

OgreContext::OgreContext(std::string appName) {
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

bool OgreContext::setupInstance(std::string appName)
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

		}
		else throw std::runtime_error("RTShader has not been initialized\n");
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

void OgreContext::setSkyPlane(std::string materialName, Ogre::Plane plane, int width, int height, float bow)
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
	mFSLayer_ = new Ogre::FileSystemLayer("OgreContext");

	Ogre::ConfigFile configFile;
	std::string configurationPath;

#ifdef _DEBUG
	configurationPath = "OgreD/resources.cfg";
#else
	configurationPath = "Ogre/resources.cfg";
#endif
	mFSLayer_->setHomePath("./bin");
	Ogre::String resourcesPath = mFSLayer_->getConfigFilePath(configurationPath);

	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		configFile.load(resourcesPath);
	else
	{
		throw std::exception("No se ha encontrado el archivo de recursos de Ogre");
	}

	Ogre::String sec, type, arch;

	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = configFile.getSettingsBySection().begin(); seci != configFile.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

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

Ogre::Root* OgreContext::getOgreRoot() const
{
	return ogreRoot_;
}

 Ogre::SceneManager* OgreContext::getSceneManager() const
{
	return ogreSceneManager_;
}


