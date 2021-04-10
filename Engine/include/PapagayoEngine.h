#pragma once

#include <string>

// resto de includes graphics, physics, etc.
namespace Ogre {
	class Root;
	class SceneManager;
	class Camera;
	class SceneNode;
	namespace RTShader {
		class ShaderGenerator;
	}
	//class RenderWindow;
}

class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();

	void run();

	
private:
	static PapagayoEngine* instance_;
	std::string appName_;
	
	bool running_ = true;

	// nos guardamos el root para poder crear las escenas a partir de ogre
	


	PapagayoEngine(const std::string& appName);
	void init();

	void update();
	


};