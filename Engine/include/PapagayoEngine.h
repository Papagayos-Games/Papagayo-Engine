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
	void init();
	void destroy();
	void clean();
	void start();
	void run();
	void closeApp();
	const std::map<std::string, Manager*>& getManagers();
	const std::map<std::string, Manager*>& getManagers() const;
	
private:
	uint32_t startTime = 0;
	uint32_t lag = 0;
	uint32_t frame_rate = 1000 / 60;
	
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
	int timer_ = 0;
	PapagayoEngine(const std::string& appName);
	virtual ~PapagayoEngine();
	void update();
};

#endif