#include "Managers\ResourceManager.h"

#include <iostream>
#include <fstream>

#include "PapagayoEngine.h"
#include <Ogre.h>
#include <OgreFileSystemLayer.h>
#include <OgreEntity.h>

ResourceManager* ResourceManager::instance_ = nullptr;
std::string ResourceManager::PATH_ = "assets/";

ResourceManager::ResourceManager(const std::string& path) :path_(path)
{
	ogreRoot_ = PapagayoEngine::getInstance()->getOgreRoot();
	mFSLayer = new Ogre::FileSystemLayer("PapagayoEngine");
	loadFromResourceFile();
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if (instance_ == nullptr)
		if (!setupInstance(ResourceManager::PATH_))
			throw "ERROR: ResourceManager couldn't be created\n";

	return instance_;
}

bool ResourceManager::setupInstance(const std::string& path)
{
	if (instance_ == nullptr) {
		instance_ = new ResourceManager(path);
		return true;
	}

	return false;
}

void ResourceManager::clean()
{
	delete instance_;
}

void ResourceManager::init()
{
	loadPrefabs("prefabs");
}

json ResourceManager::getSceneFile(const std::string& sceneName)
{
	json j;

	std::fstream i(path_ + sceneName + ".json");

	if (i.is_open())
	{
		i >> j;
		i.close();
	}
	else
	{
		std::cout << "File not found: " << path_ << sceneName << ".json" << "\n";
	}

	return j;
}

void ResourceManager::loadPrefabs(const std::string& prefabName)
{
	std::fstream i(path_ + prefabName + ".json");

	if (i.is_open())
	{
		i >> prefabs_;
		i.close();
	}
	else
	{
		std::cout << "File not found: " << path_ << prefabName << ".json" << "\n";
	}
}

void ResourceManager::loadFromResourceFile()
{
	Ogre::ConfigFile configFile;
	std::string configurationPath;

#ifdef _DEBUG
	configurationPath = "OgreD/resources.cfg";
#else
	configurationPath = "Ogre/resources.cfg"
#endif
	mFSLayer->setHomePath("./bin"/*+ configurationPath*/);
	Ogre::String resourcesPath = mFSLayer->getConfigFilePath(configurationPath);

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

json ResourceManager::getPrefabs()
{
	return prefabs_;
}
