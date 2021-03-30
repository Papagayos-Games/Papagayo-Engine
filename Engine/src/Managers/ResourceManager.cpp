#include "Managers\ResourceManager.h"

#include <iostream>
#include <fstream>

ResourceManager* ResourceManager::instance_ = nullptr;

ResourceManager::ResourceManager(const std::string& path) :path_(path)
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;

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

json ResourceManager::getPrefabs()
{
	return prefabs_;
}
