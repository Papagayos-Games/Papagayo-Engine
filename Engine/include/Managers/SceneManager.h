#pragma once

#ifndef _PAPAENG_SCENEMAN_H
#define _PAPAENG_SCENEMAN_H

#include <string>
#include <vector>

class LoaderSystem;
class Entity;
class Scene;

class SceneManager {
public:
	static SceneManager* getInstance();
	static Scene* getCurrentScene();
	static bool setupInstance();
	static void clean();
	static void destroy();
	
	void update();
	void changeScene(const std::string& sceneName);
	void createStartScene(const std::string& startScene);
private:
	SceneManager();	
	~SceneManager();

	void loadScene(const std::string& sceneName);
	void cleanupScene();

	static SceneManager* instance_;
	static Scene* currentScene_;
	std::vector<std::string> sceneFiles_;
	LoaderSystem* loader_;
	bool change_;
	std::string nextScene_;
};

#endif // !_PAPAENG_SCENEMAN_H