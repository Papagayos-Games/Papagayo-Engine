#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "LoaderSystem.h"

#include "PapagayoEngine.h"
#include "OgreContext.h"
#include "OgreRenderWindow.h"

SceneManager* SceneManager::instance_= nullptr;
Scene* SceneManager::currentScene_ = nullptr;

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	return instance_;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene_;
}

bool SceneManager::setupInstance()
{
	if (instance_ == nullptr) {
		try {
			instance_ = new SceneManager();
		}
		catch (...) {
			return false;
		}
	}

	return true;
}

void SceneManager::clean()
{
	instance_->cleanupScene();
}

void SceneManager::destroy() {
	instance_->clean();
	delete instance_->loader_;
	delete instance_;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	//crea escena vacia
	currentScene_ = new Scene();
	currentScene_->setName(sceneName);
	//la llena de objetos
	loader_->loadEntities(sceneName, currentScene_);

	//json j = ResourceManager::getInstance()->getSceneFile(sceneName);
	//currentScene_->load(j);
}

void SceneManager::cleanupScene()
{
	currentScene_->clean();
	delete currentScene_; 
	currentScene_ = nullptr;
}

SceneManager::SceneManager() {
	loader_ = new LoaderSystem();
	change_ = false;
}


void SceneManager::update()
{
	currentScene_->eraseEntities();
	if (change_) {
		//cleanupScene();
		PapagayoEngine::getInstance()->clean();
		loadScene(nextScene_);
		
		change_ = false;
		nextScene_ = "";
		
		PapagayoEngine::getInstance()->start();
	}
}

void SceneManager::changeScene(const std::string& sceneName)
{
	bool exist = false;
	int i = 0;
	while (i < sceneFiles_.size() && !exist) {
		exist = sceneFiles_[i] == sceneName;
		i++;
	}
	if (exist) {
		nextScene_ = sceneName;
		change_ = true;
	}
	else {
		throw std::runtime_error("ERROR: Scene: " + sceneName + " doesn't exist\n");	
	}
}

void SceneManager::createStartScene(const std::string& startScene) {
	
	//sceneFiles_ = loader_->loadScenes("Scenes/scenes.json");
	sceneFiles_ = loader_->loadScenes(startScene);
	loadScene(sceneFiles_[0]);
}
