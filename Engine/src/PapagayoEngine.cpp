#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"

#include "Managers/InputSystem.h"
#include "Graphics/OgreContext.h"

//pruebas
#include "Graphics/Camera.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/LightComponent.h"
#include "OgreRoot.h"
#include "Entity.h"
#include "Transform.h"
#include "CommonManager.h"
#include "Graphics/RenderManager.h"
#include "Vector3.h"
#include "LoaderSystem.h"

#include "OgrePlane.h"
#include "Graphics/PlaneComponent.h"
#include "Physics/PhysicsManager.h"
#include "SDL.h"

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
	InputSystem::getInstance()->clean();

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

#pragma region TESTEO


	Entity* ent = new Entity();
	

	manRegistry_["Common"] = CommonManager::getInstance();
	manRegistry_["Render"] = RenderManager::getInstance();

	LoaderSystem loader;
	loader.loadEntities("Scenes/testScene.json");

	//manRegistry_.insert("Common", CommonManager::getInstance());


	
	//Component* comp = manRegistry_["Common"]->create("Transform");
	//ent->addComponent(comp);
	//Camara
	Camera* camara = new Camera();
	camara->setCameraPosition(Vector3(500,0,0));
	camara->setCameraDir(Vector3(-1, 0, 0));
	//Prueba de pintado XD
	//MeshComponent* funcaPlz = new MeshComponent();
	CommonManager::getInstance()->addComponent(ent,(int)CommonManager::CommonCmpId::TransId);
	RenderManager::getInstance()->addComponent(ent, (int)RenderManager::RenderCmpId::Mesh);
	Transform* transform_ = static_cast<Transform*>(ent->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	MeshComponent* funcaPlz = static_cast<MeshComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh));
	funcaPlz->setMaterial("Practica1_Azulejo");
	//transform_->setPosX(100);
	transform_->setDimensions(Vector3(10, 10, 10));

	PlaneComponent* plane = new PlaneComponent("PLN", "Practica1_Azulejo", 100, 50, PLANE_DIR::PLANE_X);
	
	//Pruebas de luz
	//Entity* luz = new Entity();
	//CommonManager::getInstance()->addComponent(luz, (int)CommonManager::CommonCmpId::TransId);
	LightComponent* l = new LightComponent(Vector3(0, 0, 500), Vector3(0, 0, -1), "LI");
	l->setLightPower(0.1);
	//LightComponent* l = new LightComponent(Vector3(0, 0, 500), "LI", LIGHT_TYPE::POINT);
#pragma endregion

	OgreContext::getInstance()->setSkyPlane("SkyPlaneMat", Ogre::Plane(Ogre::Vector3::UNIT_Z, -70), 10, 10, 4.0);
	// dejar al final
	RenderManager::getInstance()->start();
	//Test
	//funcaPlz->update();
	//camara->update();
}

void PapagayoEngine::update()
{
	try {
		//std::cout << "Updating\n";
		OgreContext::getInstance()->getOgreRoot()->renderOneFrame();
		pollEvents();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo de renderizado \n" + (std::string)e.what() + "\n");
	}

}

void PapagayoEngine::pollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		InputSystem::getInstance()->handleInput(e);
	}
}



void PapagayoEngine::run() {
	init();
	// ciclo principal de juego
	while (running_) {
		update();
	}
}

std::map<std::string, Manager*> PapagayoEngine::getManagers()
{
	return manRegistry_;
}
