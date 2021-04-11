#pragma once
#include <string>

namespace Ogre {
	class Root;
	class SceneManager;
	class Camera;
	class SceneNode;
	class OverlaySystem;
	/*namespace RTShader {
		class ShaderGenerator;
	}*/
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


private:
	SceneManager();
	static SceneManager* instance_;
	static Scene* currentScene_;

	
	void addCamera();

	// Crea la escena por defecto
	void createStartScene();
};