#include "PapagayoEngine.h"

#include <stdexcept>

#include "Managers/ResourceManager.h"
#include "Managers/SceneManager.h"

PapagayoEngine* PapagayoEngine::instance_ = nullptr;

PapagayoEngine::PapagayoEngine(const std::string& appName) :appName_(appName) {

}

PapagayoEngine::~PapagayoEngine()
{
}

int main() {}


PapagayoEngine* PapagayoEngine::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;

	return instance_;
}


bool PapagayoEngine::setupInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		instance_ = new PapagayoEngine(appName);
		return true;
	}

	return false;
}

void PapagayoEngine::clean()
{
	delete instance_;
}

void PapagayoEngine::init()
{
	// iniciar resto de singletons/managers
	try { ResourceManager::setupInstance("assets/"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceManager init fail \n" + (std::string)e.what() + "\n");	return;
	}

	try { SceneManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");	return;
	}
}

void PapagayoEngine::initTestScene()
{
	SceneManager::getInstance()->loadScene("test");
}

void PapagayoEngine::update()
{
	SceneManager::getInstance()->update();
}
