#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"

#include "Graphics/OgreContext.h"

//pruebas
#include "Graphics/Camera.h"
#include "Graphics/MeshComponent.h"
#include "OgreRoot.h"
#include "Entity.h"
#include "Transform.h"
#include "CommonManager.h"
#include "Managers/RenderManager.h"
#include "Vector3.h"


PapagayoEngine* PapagayoEngine::instance_ = nullptr;

PapagayoEngine::PapagayoEngine(const std::string& appName) : appName_(appName) {
}

PapagayoEngine::~PapagayoEngine()
{
}

PapagayoEngine* PapagayoEngine::getInstance()
{
	if (instance_ == nullptr)
		if (!setupInstance("PAPAGAYO ENGINE"))
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
	OgreContext::getInstance()->clean();

	delete instance_;
}

void PapagayoEngine::init()
{
	try { OgreContext::setupInstance("PAPAGAYO ENGINE"); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("OgreContext init fail \n" + (std::string)e.what() + "\n");
	}

	// iniciar resto de singletons/managers

	try { ResourceManager::setupInstance("assets/"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceManager init fail \n" + (std::string)e.what() + "\n");
	}
	
	try { SceneManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");
	}

	Entity* ent = new Entity();


	//Camara
	Camera* camara = new Camera();
	//Prueba de pintado XD
	//MeshComponent* funcaPlz = new MeshComponent();
	CommonManager::getInstance()->addComponent(ent,(int)CommonManager::CommonCmpId::TransId);
	RenderManager::getInstance()->addComponent(ent, (int)RenderManager::RenderCmpId::Mesh);
	Transform* transform_ = static_cast<Transform*>(ent->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	MeshComponent* funcaPlz = static_cast<MeshComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh));
	transform_->setPosX(100);
	transform_->setDimensions(Vector3(1, 1, 1));
	funcaPlz->update();
}




void PapagayoEngine::update()
{
	try {
		//std::cout << "Updating\n";
		OgreContext::getInstance()->getOgreRoot()->renderOneFrame();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo de renderizado \n" + (std::string)e.what() + "\n");
	}

}



void PapagayoEngine::run() {
	init();
	// ciclo principal de juego
	while (running_) {
		update();
	}
}