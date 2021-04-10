#include "Graphics/OgreContext.h"
#include "OgreShaderGenerator.h"
#include "Graphics/RTShaderTecnhiqueResolveListener.h"
#include "Ogre.h"
#include "Graphics/WindowGenerator.h"

OgreContext* OgreContext::instance_ = nullptr;

OgreContext::OgreContext(std::string appName) {
	appName_ = appName;
	createRoot();
	init();
	createSceneManager();
 }
OgreContext* OgreContext::getInstance()
{
	if (instance_ == nullptr)
		if (!setupInstance("PAPAGAYO ENGINE"))
			throw "ERROR: PapagayoEngine couldn't be created\n";
	return instance_;
}


bool OgreContext::setupInstance(std::string appName)
{
	if (instance_ == nullptr) {
		instance_ = new OgreContext(appName);
		return true;
	}

	return false;
}

void OgreContext::createRoot()
{
#ifdef _DEBUG
	ogreRoot_ = new Ogre::Root("OgreD/plugins.cfg");
#else
	ogreRoot_ = new Ogre::Root("Ogre/plugins.cfg");
#endif

	if (ogreRoot_ == nullptr) {
		throw std::exception("No se ha podido crear el mRoot");
	}

}

void OgreContext::createSceneManager()
{
	ogreSceneManager_ = ogreRoot_->createSceneManager();
	ogreSceneManager_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreContext::setupRTShaderGenerator()
{
	try {
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			//Cogemos la instancia
			Ogre::RTShader::ShaderGenerator* mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
			mShaderGenerator->addSceneManager(ogreSceneManager_);

			//Resolutor de mallas 
			RTShaderTecnhiqueResolveListener* mMaterialListener_ = new RTShaderTecnhiqueResolveListener(mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialListener_);

		}
		else throw std::runtime_error("RTShader has not been initialized\n");
	}
	catch (const std::exception & e)
	{
		throw std::runtime_error("Fallo al inicializar el RTShader\n" + (std::string)e.what() + "\n");
	}
}

void OgreContext::init()
{
	try { WindowGenerator::setupInstance(getOgreRoot(), appName_); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("WindowGenerator init fail \n" + (std::string)e.what() + "\n");
	}
}

 Ogre::Root* OgreContext::getOgreRoot() const
{
	return ogreRoot_;
}

 Ogre::SceneManager* OgreContext::getSceneManager() const
{
	return ogreSceneManager_;
}


