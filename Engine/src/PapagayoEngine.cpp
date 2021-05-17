#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include <SDL_timer.h>
#include "OgreRoot.h"
#include "Vector3.h"

//-------MANAGER/SYSTEM---------//
#include "Managers/SceneManager.h"
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
	ogre = OgreContext::getInstance();
	input = InputSystem::getInstance();
	gui = UIManager::getInstance();
	phys = PhysicsManager::getInstance();
	render = RenderManager::getInstance();
	mSM = SceneManager::getInstance();
	common = CommonManager::getInstance();
	lua = LUAManager::getInstance();
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
	phys->clean();
	mSM->clean();
	ogre->clean();
	//RenderManager::getInstance()->clean();
	input->clean();
	
	delete instance_;
}

void PapagayoEngine::init()
{
	try { ogre->setupInstance("PAPAGAYO ENGINE"); }
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
	gui->setMouseImage("TaharezLook/MouseArrow");
	gui->loadFont("DejaVuSans-12.font"); 
	
	mSM->createStartScene();

#pragma region TOERASE
	//gui->createButton("Probando_boton", glm::vec2(0, 0), glm::vec2(200, 200), "Prueba");
	//ui->createLabel("Probando_boton", glm::vec2(100, 100), glm::vec2(10, 10), "Prueba");

	ogre->setSkyPlane("SkyPlaneMat", Ogre::Plane(Ogre::Vector3::UNIT_Z, -70), 10, 10, 4.0);
	//Audio de bad bunny metido 
	AudioEngine* au = new AudioEngine();
	au->Init();
	au->PlaySound("Assets/badbunny.mp3", {0,0,0});

#pragma endregion

	start();
}

void PapagayoEngine::start()
{
	render->start();
	phys->start();
	LUAManager::getInstance()->start();
}

void PapagayoEngine::update()
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
			phys->update();
			render->update();

			if (timer_ == 1000) {
				std::cout << "Cambio de escena\n";
				mSM->changeScene("test2");
			}

			mSM->update();
			++timer_;
			lua->update();
		}
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
	startTime = SDL_GetTicks();
	while (running_) {

		//RETARDO DE FPS
		auto current = SDL_GetTicks();
		auto elapsed = current - startTime;
		startTime = current;
		lag += elapsed;

		while (lag >= frame_rate) {
			lag -= frame_rate;
		}

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