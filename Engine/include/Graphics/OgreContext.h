#pragma once
#include <string>

#ifdef _DEBUG
#include "checkML.h"
#endif
class RTShaderTecnhiqueResolveListener;

namespace Ogre {
	class Root;
	class SceneManager;
	class Camera;
	class SceneNode;
	class FileSystemLayer;

	namespace RTShader {
		class ShaderGenerator;
	}
}



class OgreContext
{
private:
	static OgreContext* instance_;
	Ogre::Root* ogreRoot_ = nullptr;
	Ogre::SceneManager* ogreSceneManager_ = nullptr;
	Ogre::RTShader::ShaderGenerator* mShaderGenerator_;
	Ogre::FileSystemLayer* mFSLayer_;
	RTShaderTecnhiqueResolveListener* mMaterialListener_;
	std::string appName_;


	OgreContext(std::string appName);
	void createRoot();
	void createSceneManager();
	void init();
	void loadFromResourceFile();
public:
	~OgreContext();
	Ogre::Root* getOgreRoot() const;
	Ogre::SceneManager* getSceneManager() const;
	static OgreContext* getInstance();
	static bool setupInstance(std::string appName);
	void setupRTShaderGenerator();
	static void clean();
};

