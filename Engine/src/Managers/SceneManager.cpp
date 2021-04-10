#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "Managers/ResourceManager.h"
#include "Graphics/WindowGenerator.h"


#include "PapagayoEngine.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"



SceneManager* SceneManager::instance_= nullptr;
Scene* SceneManager::currentScene_ = nullptr;

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
	cleanupScene();
	delete instance_;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	//crea escena vacia
	currentScene_ = new Scene();

	//la llena de objetos
	json j = ResourceManager::getInstance()->getSceneFile(sceneName);
	currentScene_->load(j);
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
	ogreRoot_ = PapagayoEngine::getInstance()->getOgreRoot();
	createStartScene();
}


void SceneManager::createStartScene() {
	mSM_ = ogreRoot_->createSceneManager();
	mSM_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	addCamera();
}

Ogre::Camera* SceneManager::getCamera(){
	return mCamera_;
}

Ogre::SceneManager* SceneManager::getOgreSceneManager()
{
	return mSM_;
}

void SceneManager::addCamera() {
	mCamera_ = mSM_->createCamera("MainCamera");
	mCamera_->setNearClipDistance(1);
	mCamera_->setFarClipDistance(10000);
	//mCamera_->lookAt(0, 0, -1);
	mCamera_->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mainCamNode_ = mSM_->getRootSceneNode()->createChildSceneNode("mCam");//->getRootSceneNode()->createChildSceneNode("nCam");
	mainCamNode_->attachObject(mCamera_);

	mainCamNode_->setPosition(0, 0, 1000);
	mainCamNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = WindowGenerator::getInstance()->getRenderWindow()->addViewport(mCamera_);
	vp->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0, 1.0));//cambia el color del fondo
}