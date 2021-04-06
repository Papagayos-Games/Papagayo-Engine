#pragma once
#include <string>

namespace Ogre {
	class Root;
	class SceneManager;
	class Camera;
	class SceneNode;
}


class Entity;
class Scene;

class SceneManager {
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	void loadScene(const std::string& sceneName);
	static void cleanupScene();

	// Añade entidades y componentes a esas entidades al iniciar la escena y al instanciar gameObjects durante ejecuccion
	void addEntity() {};
	void addComponentTo(const std::string& entName) {};
	void addComponentTo(const Entity *ent){};
	// Devuelve la main cámara
	inline Ogre::Camera* getCamera();

private:
	SceneManager();
	static SceneManager* instance_;
	static Scene* currentScene_;
	// Root de ogre
	Ogre::Root* ogreRoot_;
	//	Puntero al manager
	Ogre::SceneManager* mSM_ = nullptr;
	Ogre::SceneNode* mainCamNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;
	//	Agrega una cámara a la escena
	void addCamera();

	// Crea la escena por defecto
	void createStartScene();
};