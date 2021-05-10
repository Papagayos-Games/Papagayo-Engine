#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include "Managers/SceneManager.h"

#include "Graphics/OgreContext.h"

#include "Input/InputSystem.h"

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
#include "AudioSystem.h"
#include "UIManager.h"

#include "LUA/LUAManager.h"

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
	PhysicsManager::getInstance()->clean();
	SceneManager::getInstance()->clean();
	OgreContext::getInstance()->clean();
	//RenderManager::getInstance()->clean();
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
	
	try { SceneManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");
	}

	manRegistry_["Physics"] = PhysicsManager::getInstance();
	manRegistry_["Common"] = CommonManager::getInstance();
	manRegistry_["Render"] = RenderManager::getInstance();
	UIManager* ui = UIManager::getInstance();
	//ui->loadScheme("AlfiskoSkin", "./bin/cegui/AlfiskoSkin.scheme");

	SceneManager::getInstance()->createStartScene();

#pragma region TOERASE
	OgreContext::getInstance()->setSkyPlane("SkyPlaneMat", Ogre::Plane(Ogre::Vector3::UNIT_Z, -70), 10, 10, 4.0);
	//Audio de bad bunny metido 
	AudioEngine* au = new AudioEngine();
	au->Init();
	au->PlaySound("Assets/badbunny.mp3", {0,0,0});

	ui->createButton("Probando boton", glm::vec2(100, 100), glm::vec2(10, 10), "Prueba");
#pragma endregion

	start();
}

void PapagayoEngine::start()
{
	RenderManager::getInstance()->start();
	PhysicsManager::getInstance()->start();
}

void PapagayoEngine::update()
{
	
	try {
		InputSystem::getInstance()->handleInput();
		PhysicsManager::getInstance()->update();
		RenderManager::getInstance()->update();
		
		if (timer_ == 1000) {
			std::cout << "Cambio de escena\n";
			SceneManager::getInstance()->changeScene("test2");
		}
		SceneManager::getInstance()->update();
		++timer_;
		LUAManager::getInstance()->update();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo de renderizado \n" + (std::string)e.what() + "\n");
	}

}

void PapagayoEngine::run() {
	init();
	//running_ = false;
	// ciclo principal de juego
	while (running_) {
		update();
	}
}

const std::map<std::string, Manager*>& PapagayoEngine::getManagers()
{
	return manRegistry_;
}

const std::map<std::string, Manager*>& PapagayoEngine::getManagers() const
{
	return manRegistry_;
}