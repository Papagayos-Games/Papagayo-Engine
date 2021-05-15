#pragma once

#ifndef _GRAPHICS_OGRECONT_H
#define _GRAPHICS_OGRECONT_H

#include <string>
class RTShaderTecnhiqueResolveListener;
class SDL_Window;

namespace Ogre {
	class RenderWindow;
	class RenderTarget;
	class Root;
	class ViewPort;
	class SceneManager;
	class SceneNode;

	class Camera;
	class FileSystemLayer;
	class Plane;

	typedef std::string _StringBase;
	typedef _StringBase String;

	namespace RTShader {
		class ShaderGenerator;
	}
}

class OgreContext
{
private:
	static OgreContext* instance_;
	//OGRE ROOT
	Ogre::Root* ogreRoot_ = nullptr;
	
	//CFG FILES
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::String mOgreCfg;
	Ogre::String mRTShaderLibPath;
	
	//SCENE MANAGER
	Ogre::SceneManager* mSM = nullptr;
	
	//WINDOW RENDER
	Ogre::RenderWindow* render = nullptr;
	
	//SDL WINDOW
	SDL_Window* native = nullptr;

	//La instancia generadora de Shader
	Ogre::RTShader::ShaderGenerator* mShaderGenerator_;
	
	//Shader Listener generador de materiales
	RTShaderTecnhiqueResolveListener* mMaterialListener_;

	Ogre::FileSystemLayer* mFSLayer_;
	std::string appName_;

	bool grab = false;
	bool showCursor = false;
	bool exit;

	OgreContext(const std::string& appName);

//------INIT OGRE--------//

	void createRoot();
	void createWindow();
	void createSceneManager();
	void init();
	void loadFromResourceFile();
public:
	~OgreContext();
	static bool setupInstance(const std::string& appName);
	static void clean();
	//Hay que poner en el material un lighting off
	void setSkyPlane(const std::string& materialName, const Ogre::Plane& plane, int width, int height, float bow);
	void setupRTShaderGenerator();

//--------------GET-----------//
	static OgreContext* getInstance();
	
	Ogre::Root* getOgreRoot();
	Ogre::Root* getOgreRoot() const;

	Ogre::SceneManager* getSceneManager();
	Ogre::SceneManager* getSceneManager() const;
	
	Ogre::RenderTarget* getRenderTarget() const;
	Ogre::RenderWindow* getRenderWindow() const;
	

	SDL_Window* getSDLWindow() const;
};

#endif