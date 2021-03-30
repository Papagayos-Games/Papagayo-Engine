#pragma once
#include <string>

class Scene;

class SceneManager {
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	void loadScene(const std::string& sceneName);
	void cleanupScene();

	void start();
	void update();

private:
	SceneManager();
	static SceneManager* instance_;

	Scene* currentScene_ = nullptr;
};