#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "Managers/ResourceManager.h"

SceneManager* SceneManager::instance_ = nullptr;

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;
	
		return instance_;
}

bool SceneManager::setupInstance()
{
	if (instance_ == nullptr) {
		instance_ = new SceneManager();
		return true;
	}

	return false;
}

void SceneManager::clean()
{
	delete instance_;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	json j = ResourceManager::getInstance()->getSceneFile(sceneName);

	currentScene_ = new Scene();
	currentScene_->load(j);
}

void SceneManager::cleanupScene()
{
	delete currentScene_; currentScene_ = nullptr;

	//decir a ogre que limpie la escena
}

void SceneManager::start()
{
	currentScene_->start();
}

void SceneManager::update()
{
	currentScene_->update();
}

SceneManager::SceneManager() {

}
