#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "Graphics/WindowGenerator.h"
#include "Graphics/OgreContext.h"
#include "LoaderSystem.h"

#include "PapagayoEngine.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"



SceneManager* SceneManager::instance_= nullptr;
Scene* SceneManager::currentScene_ = nullptr;

SceneManager::~SceneManager()
{
	clean();
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
	cleanupScene();
	delete instance_->loader_;
	delete instance_;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	//crea escena vacia
	currentScene_ = new Scene();
	currentScene_.
	//la llena de objetos
	loader_->loadEntities(sceneName, currentScene_);

	//json j = ResourceManager::getInstance()->getSceneFile(sceneName);
	//currentScene_->load(j);
}

void SceneManager::cleanupScene()
{
	//decir a ogre que limpie la escena
	
	if(currentScene_){
		delete currentScene_; 
		currentScene_ = nullptr;
	}
}

SceneManager::SceneManager() {
	loader_ = new LoaderSystem();
	createStartScene();
}


void SceneManager::createStartScene() {
	
	sceneFiles_ = loader_->loadScenes("Scenes/scenes.json");
	loadScene(sceneFiles_[0]);
}
