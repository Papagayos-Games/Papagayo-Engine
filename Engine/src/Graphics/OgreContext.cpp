
#include "OgreContext.h"
#include "RTShaderTecnhiqueResolveListener.h"
#include <Ogre.h>

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_events.h>
#include <iostream>

#include <OgreSTBICodec.h>
#include <checkML.h>
#include <OgreShaderGenerator.h>

/*#include <OgreFileSystemLayer.h>
#include "WindowGenerator.h"
#include <OgreEntity.h>
#include <OgreLight.h>		//TOERASE
*/

OgreContext* OgreContext::instance_ = nullptr;

OgreContext::OgreContext(const std::string& appName) : 
	mResourcesCfg(Ogre::BLANKSTRING),
	mPluginsCfg(Ogre::BLANKSTRING)
{
	appName_ = appName;
	init();
}

OgreContext* OgreContext::getInstance()
{
	return instance_;
}

bool OgreContext::setUpInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		try {
			instance_ = new OgreContext(appName);
		}
		catch (...){
			return false;
		}
	}

	return true;
}

#pragma region INIT_OGRE

void OgreContext::init()
{
	//-------ROOT--------------//
	createRoot();

	//------WINDOW-------------//
	createWindow();

	//----SETTING-RESOURCES----//
	loadFromResourceFile();

	//----WINDOW-GRAB----------//
	const auto g = SDL_bool(grab);
	SDL_SetWindowGrab(native, g);
	SDL_ShowCursor(showCursor);

	//ogreRoot_->addFrameListener(render);
	//----RT-SHADER-SYSTEM-----//
	setupRTShaderGenerator();
}

void OgreContext::createRoot()
{
#ifdef _DEBUG
	mResourcesCfg = "OgreD/resources.cfg";
	mPluginsCfg = "OgreD/plugins.cfg";
	mOgreCfg = "OgreD/ogre.cfg";
#else
	mResourcesCfg = "Ogre/resources.cfg";
	mPluginsCfg = "Ogre/plugins.cfg";
	mOgreCfg =  "Ogre/ogre.cfg";
#endif
	ogreRoot_ = new Ogre::Root(mPluginsCfg, mOgreCfg);

	if (ogreRoot_ == nullptr) {
		throw std::exception("No se ha podido crear el mRoot");
	}

	Ogre::STBIImageCodec::startup();
	ogreRoot_->restoreConfig();
	ogreRoot_->initialise(false);
}

void OgreContext::createWindow()  
{
	Ogre::ConfigOptionMap ropts = ogreRoot_->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> windowWidth;     // width
	mode >> token; // 'x' as separator between width and height
	mode >> windowHeight;     // height

	std::cout << '\n' << windowWidth << " " << windowHeight << '\n';
	if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_TIMER))
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			/*EXCEPCION*/
		}

#ifdef _DEBUG
	int flags = 0;
#else
	int flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

	native = SDL_CreateWindow(appName_.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(native, &wmInfo);

	Ogre::NameValuePairList miscParams;

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;


	miscParams["externalWindowHandle"] =
		Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	render = ogreRoot_->createRenderWindow(appName_, windowWidth, windowHeight, false, &miscParams);

	// create a SceneManager instance
	mSM = ogreRoot_->createSceneManager();
	mSM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreContext::loadFromResourceFile()
{
	// create a Ogre::ConfigFile object and use it to parse our cfg file

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// allow us to iterate through all of the sections discovered by the parser
	Ogre::ConfigFile::SettingsBySection_ secIt = cf.getSettingsBySection();

	// iterate through all of the results.
	for (auto it : secIt) {
		Ogre::String secName = it.first;
		// ask for another iterator that will let us iterate through the items
		// in each section
		Ogre::ConfigFile::SettingsMultiMap* settings = &it.second;
		Ogre::ConfigFile::SettingsMultiMap::iterator it2;

		// scan through each item with this iterator
		for (it2 = settings->begin(); it2 != settings->end(); ++it2) {
			// unpack each pair
			Ogre::String locType = it2->first; // location type of this resource
			Ogre::String name = it2->second;   // the path

			// add this location to our ResourceGroupManager
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				name, locType, secName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreContext::setupRTShaderGenerator()
{
	try {
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			//Cogemos la instancia
			mShaderGenerator_ = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
			mShaderGenerator_->addSceneManager(mSM);

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem");
			//Set the scene manager
			mShaderGenerator_->addSceneManager(mSM);

			//Resolutor de mallas 
			mMaterialListener_ = new RTShaderTecnhiqueResolveListener(mShaderGenerator_);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialListener_);

		}
		else
			throw std::runtime_error("RTShader has not been initialized\n");
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo al inicializar el RTShader\n" + (std::string)e.what() + "\n");
	}
}

#pragma endregion

void OgreContext::clean()
{
	//Destruir SceneManager
	//intance_->mShaderGenerator_->removeSceneManager(instance_->mSM);
	//instance_->mShaderGenerator_->addSceneManager(instance_->mSM); // TO DO: Devolverselo en el cambio de escena
	//instance_->ogreRoot_->destroySceneManager(instance_->mSM);
	OgreContext::getInstance()->getRenderWindow()->removeAllViewports();
}

void OgreContext::destroy()
{
	clean();
	instance_->mShaderGenerator_->removeSceneManager(instance_->mSM);
	//instance_->mShaderGenerator_->addSceneManager(instance_->mSM); // TO DO: Devolverselo en el cambio de escena
	instance_->ogreRoot_->destroySceneManager(instance_->mSM);
	delete instance_;
}

void OgreContext::setSkyPlane(const std::string& materialName, const Ogre::Plane& plane, int width, int height, float bow)
{
	mSM->setSkyPlane(true, plane, materialName, 1, 1, true, bow, width, height);
}

OgreContext::~OgreContext()
{
	if (ogreRoot_ != nullptr)
		ogreRoot_->saveConfig();

	// restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(
		Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// destroy RTShader system.
	if (mShaderGenerator_ != nullptr) {
		Ogre::RTShader::ShaderGenerator::getSingleton().destroy();
		mShaderGenerator_ = nullptr;
	}

	if (render != nullptr) {
		ogreRoot_->destroyRenderTarget(render);
		render = nullptr;
	}

	if (native != nullptr) {
		SDL_DestroyWindow(native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		native = nullptr;
	}

	//Destruir FileSystemLayer
	//delete mFSLayer_;

	delete ogreRoot_;
	ogreRoot_ = nullptr;

	//Destruir RTShaderSystem;
	delete mMaterialListener_;

	Ogre::STBIImageCodec::shutdown();
}

#pragma region GET
Ogre::Root* OgreContext::getOgreRoot()
{
	return ogreRoot_;
}

Ogre::Root* OgreContext::getOgreRoot() const
{
	return ogreRoot_;
}

Ogre::SceneManager* OgreContext::getSceneManager()
{
	return mSM;
}

Ogre::SceneManager* OgreContext::getSceneManager() const
{
	return mSM;
}

Ogre::RenderTarget* OgreContext::getRenderTarget() const {
	return ogreRoot_->getRenderTarget(render->getName());
}

Ogre::RenderWindow* OgreContext::getRenderWindow() const
{
	return render;
}

SDL_Window* OgreContext::getSDLWindow() const
{
	return native;
}


uint32_t OgreContext::getWindowWidth() const
{
	return  windowWidth	;
}
uint32_t OgreContext::getWindowHeight() const
{
	return windowHeight;
}

#pragma endregion
