#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include <SDL_timer.h>
#include "OgreRoot.h"
#include "Vector3.h"

//-------MANAGER/SYSTEM---------//
#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "Graphics/OgreContext.h"
#include "Input/InputSystem.h"
#include "CommonManager.h"
#include "Graphics/RenderManager.h"
#include "Physics/PhysicsManager.h"
#include "UIManager.h"
#include "LUA/LUAManager.h"
#include "LoaderSystem.h"
#include "AudioSystem.h"

//-----------COMPONENT----------//
#include "OgrePlane.h"

PapagayoEngine* PapagayoEngine::instance_ = nullptr;

PapagayoEngine::PapagayoEngine(const std::string& appName) : appName_(appName) {
	
	// OGRE CONTEXT
	if (!OgreContext::setUpInstance(appName_)) {
		throw std::exception("ERROR: Couldn't load OgreContext\n");
	}
	ogre = OgreContext::getInstance();

	// INPUT SYSTEM
	if (!InputSystem::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load InputSystem\n");
	}
	input = InputSystem::getInstance();

	// UI MANAGER
	if (!UIManager::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load UIManager\n");
	}
	gui = UIManager::getInstance();

	// PHYSICS
	if (!PhysicsManager::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load PhysicsManager\n");
	}
	phys = PhysicsManager::getInstance();

	// RENDER
	if (!RenderManager::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load RenderManager\n");
	}
	render = RenderManager::getInstance();

	// SCENE MANAGER
	if (!SceneManager::setupInstance()) {
		throw std::exception("ERROR: Couldn't load SceneManager\n");
	}
	mSM = SceneManager::getInstance();

	// COMMON MANAGER
	if (!CommonManager::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load CommonManager\n");
	}
	common = CommonManager::getInstance();

	// LUA MANAGER
	if (!LUAManager::setUpInstance()) {
		throw std::exception("ERROR: Couldn't load LuaManager\n");
	}
	lua = LUAManager::getInstance();

	// AUDIO
	if (!AudioSystem::setupInstance()) {
		throw std::exception("ERROR: Couldn't load AudioSystem\n");
	}
	audio = AudioSystem::getInstance();
}

PapagayoEngine::~PapagayoEngine()
{
}

PapagayoEngine* PapagayoEngine::getInstance()
{
	return instance_;
}

bool PapagayoEngine::setupInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		try {
			instance_ = new PapagayoEngine(appName);
		}
		catch (...) {
			return false;
		}
	}

	return true;
}

void PapagayoEngine::destroy()
{
	// se borran todos los managers del motor
	// sistemas
	input->destroy();
	audio->destroy();

	// render
	render->destroy();
	gui->destroy();
	ogre->destroy();
	
	// fisicas
	phys->destroy();

	// common
	common->destroy();
	
	// logica
	lua->destroy();

	// escena
	mSM->destroy();
	
	delete instance_;
}

void PapagayoEngine::clean()
{
	input->clean();
	audio->clean();

	// render
	render->clean();
	gui->clean();
	ogre->clean();

	// fisicas
	phys->clean();

	// common
	common->clean();

	// logica
	lua->clean();

	// escena
	mSM->clean();
}

void PapagayoEngine::init()
{
	try { ogre->setUpInstance("PAPAGAYO ENGINE"); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("OgreContext init fail \n" + (std::string)e.what() + "\n");
	}
	
	try { mSM->setupInstance();}
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");
	}

	manRegistry_["Physics"] = phys;
	manRegistry_["Common"] = common;
	manRegistry_["Render"] = render;
	manRegistry_["LUA"] = LUAManager::getInstance();
	manRegistry_["UI"] = gui;
	//Estas 3 lineas de ui deber�an cargarse en funci�n de 
	//unos string que se reciban como parametro, de manera
	//que sea el usuario el que decida que configuracion
	//desea usuar.
	gui->loadScheme("TaharezLook", "TaharezLook.scheme");

	mSM->createStartScene();


#pragma region TOERASE
	//gui->createButton("Probando_boton", glm::vec2(0, 0), glm::vec2(200, 200), "Prueba");
	//ui->createLabel("Probando_boton", glm::vec2(100, 100), glm::vec2(10, 10), "Prueba");

	ogre->setSkyPlane("SkyPlaneMat", Ogre::Plane(Ogre::Vector3::UNIT_Z, -70), 10, 10, 4.0);

	//Audio de bad bunny metido 
	audio->playSound("Assets/badbunny.mp3", {0,0,0});

#pragma endregion

	start();
}

void PapagayoEngine::start()
{
	render->start();
	phys->start();
	lua->start();
}

void PapagayoEngine::update(float delta)
{
	try {
		SDL_Event event;
		bool run = true;
		while (SDL_PollEvent(&event) && run) {
			run = input->handleInput(event);
			gui->captureInput(event);
		}

		//Basicamente no va a actualizar nada mas
		//y se cerraria el programa
		if (!run) {
			running_ = run;
		}
		else {
			render->update(delta);
			phys->update(delta);

			lua->update(delta);
			
			++timer_;
			if (timer_ == 1000) {
				SceneManager::getCurrentScene()->killEntityByName("penguin");
				std::cout << "Cambio de escena\n";
				mSM->changeScene("test3");
			}

			mSM->update();
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo en el update:\n" + (std::string)e.what() + "\n");
	}
	catch (...) {
		throw "Excepcion no controlada\n";
	}

}

void PapagayoEngine::fixedUpdate(float delta) {
	try {
		lua->fixedUpdate(delta);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo en el fixedUpdate:\n" + (std::string)e.what() + "\n");
	}
	catch (...) {
		throw "Excepcion no controlada en fixedUpdate\n";
	}
}

void PapagayoEngine::run() {
	//running_ = false;
	// ciclo principal de juego
	startTime = SDL_GetTicks();
	float deltaSum = 0;
	float deltaTime = 0;
	while (running_) {

		//RETARDO DE FPS
		//auto current = SDL_GetTicks();
		//auto elapsed = current - startTime;
		//startTime = current;
		//lag += elapsed;

		//while (lag >= frame_rate) {
		//	lag -= frame_rate;
		//}

		deltaSum += deltaTime;

		update(deltaTime);

		if (deltaSum > sToCallFixedUpdate) {
			fixedUpdate(deltaTime);
			deltaSum = 0;
		}

		deltaTime = SDL_GetTicks() - startTime;
		deltaTime /= 1000;
		startTime = SDL_GetTicks();
	}
}

void PapagayoEngine::closeApp()
{
	running_ = false;
}

const std::map<std::string, Manager*>& PapagayoEngine::getManagers()
{
	return manRegistry_;
}

const std::map<std::string, Manager*>& PapagayoEngine::getManagers() const
{
	return manRegistry_;
}