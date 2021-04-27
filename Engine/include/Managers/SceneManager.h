#pragma once
#include <string>
#include <vector>

class LoaderSystem;
class Entity;
class Scene;

class SceneManager {
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();
	
	void update();
	void changeScene(const std::string& sceneName);
	void createStartScene();
private:
	SceneManager();	
	
	void loadScene(const std::string& sceneName);
	void cleanupScene();

	static SceneManager* instance_;
	static Scene* currentScene_;
	std::vector<std::string> sceneFiles_;
	LoaderSystem* loader_;
	bool change_;
	std::string nextScene_;
};