#pragma once

#ifndef _PAPAENG_PAPAENG_H
#define _PAPAENG_PAPAENG_H

#include <map>
#include <vector>
#include <string>

#ifdef _DEBUG
#include "checkML.h"
#endif

class Manager;
class InputSystem;
class UIManager;
class PhysicsManager;
class RenderManager;
class SceneManager;
class CommonManager;
class LUAManager;
class OgreContext;
class AudioSystem;

class PapagayoEngine {
public:
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);

	/// <summary>
	/// Inicia el juego
	/// </summary>
	/// <param name="schemeName">
	/// Nombre del Scheme de configuracion que se usa para cargar CEGUI
	/// Ejemplo: TaharezLook
	/// </param>
	/// <param name="schemeFile">
	/// Archivo donde se guarda la configuracion Scheme para cargar CEGUI
	/// Ejemplo: TaharezLook.scheme
	/// </param>
	/// <param name="fontFile">
	/// Nombre del archivo de la fuente de texto que se usara con CEGUI
	/// Ejemplo: DejaVuSans-12.font
	/// </param>
	/// <param name="startScene">
	/// Nombre de la escena inicial del juego
	/// Ejemplo: mainMenu.json
	/// </param>
	/// <param name="music">
	/// Nombre del archivo de música inicial que se quiere poner
	/// </param>
	/// <param name="skyPlane">
	/// Nombre del fondo que se quiere usar al inicio. Debe ser
	/// un material crado mediante .material
	/// </param>
	void init(std::string schemeName, std::string schemeFile,
		std::string fontFile, std::string startScene, std::string music, std::string skyPlane);
	
	//Destruccion de todos los managers y sus respectivos componentes asociados
	void destroy();
	//Limpieza de sus  managers y sus respectivos componentes
	void clean();
	//Inicializar managers del motor
	void start();
	//Bucle principal del juego
	void run();
	//Cerrar aplicacion
	void closeApp();

	const std::map<std::string, Manager*>& getManagers();
	const std::map<std::string, Manager*>& getManagers() const;
	
private:
	uint32_t startTime = 0;
	uint32_t lag = 0;
	uint32_t frame_rate = 1000 / 60;
	float sToCallFixedUpdate = 0.15;
	
	InputSystem* input;
	UIManager* gui;
	PhysicsManager* phys;
	RenderManager* render;
	SceneManager* mSM;
	CommonManager* common;
	LUAManager* lua;
	OgreContext* ogre;
	AudioSystem* audio;

	static PapagayoEngine* instance_;
	std::string appName_;
	std::map<std::string, Manager*> manRegistry_;
	bool running_ = true;

	PapagayoEngine(const std::string& appName);
	virtual ~PapagayoEngine();
	void update(float delta);
	void fixedUpdate(float delta);
};

#endif