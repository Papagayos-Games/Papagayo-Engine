#pragma once
#include <string>
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



class OgreContext
{
private:
	static OgreContext* instance_;
	Ogre::Root* ogreRoot_ = nullptr;
	Ogre::SceneManager* ogreSceneManager_ = nullptr;
	Ogre::RTShader::ShaderGenerator* mShaderGenerator;
	std::string appName_;


	void createRoot();
	void createSceneManager();
	OgreContext(std::string appName);
	void init();
public:
	 Ogre::Root* getOgreRoot() const;
	 Ogre::SceneManager* getSceneManager() const;
	static OgreContext* getInstance();
	static bool setupInstance(std::string appName);
	void setupRTShaderGenerator();
};

