#include "LUAManager.h"
#include <iostream>

//physics
#include <Rigidbody.h>
#include <PhysicsManager.h>

//Papagayo
#include <Managers/SceneManager.h>
#include <Scene/Scene.h>

//common
#include <Vector3.h>
#include <Transform.h>
#include <Entity.h>
#include <CommonManager.h>

//input
#include <./Input/InputSystem.h>

//graphics
#include <MeshComponent.h>
#include <Camera.h>
#include <LightComponent.h>
#include <PlaneComponent.h>
#include <RenderManager.h>
#include <OgreContext.h>

//UI
#include "UIButton.h"
#include "UILabel.h"
#include "UIManager.h"

//LUA
#include "LuaComponent.h"
#include <LuaBridge.h>

//Papagayo
#include "LoaderSystem.h"
#include "Managers/SceneManager.h"
#include "PapagayoEngine.h"

//Audio
#include "AudioSystem.h"

using namespace luabridge;

LUAManager* LUAManager::instance_ = nullptr;


bool LUAManager::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK) {
		std::string err = lua_tostring(L, -1);
		std::cout << err << "\n";
		return false;
	}
	return true;
}

LUAManager::~LUAManager()
{
	classes_.clear();
	lua_close(L);
	L = nullptr;
}

LUAManager* LUAManager::getInstance()
{
	return instance_;
}

bool LUAManager::setUpInstance()
{
	if (instance_ == nullptr) {
		try {
			instance_ = new LUAManager();
		}
		catch (...) {
			return false;
		}
	}
	return true;
}

void LUAManager::start()
{
	for (Component* cmp : _compsList)
	{
		cmp->setUp();
	}
}

void LUAManager::update(float deltaTime)
{
	for (Component* cmp : _compsList)
	{
		cmp->update(deltaTime);
	}
}

void LUAManager::fixedUpdate(float deltaTime)
{
	for (Component* cmp : _compsList)
	{
		static_cast<LuaComponent*>(cmp)->fixedUpdate(deltaTime);
	}
}

void LUAManager::clean()
{
	instance_->destroyAllComponents();
}

void LUAManager::destroy() {
	instance_->clean();
	delete instance_;
}

//Aqui van todas las funciones y clases correspondientes 
void LUAManager::registerClassAndFunctions(lua_State* L) {

	getGlobalNamespace(L).beginClass<Entity>("Entity")
		.addFunction("getName", &Entity::getName)
		.addFunction("start", &Entity::start)
		.endClass();

	getGlobalNamespace(L).beginClass<Vector3>("Vector3")
		.addConstructor<void (*) (const float, const float, const float)>()
		.addProperty("x", &Vector3::x)
		.addProperty("y", &Vector3::y)
		.addProperty("z", &Vector3::z)
		.addFunction("normalize", &Vector3::normalize)
		.endClass();
	
	//input
	getGlobalNamespace(L).beginClass<InputSystem>("InputSystem")
		.addFunction("keyPressed", &InputSystem::isKeyDown)
		.addFunction("mouseButtonPressed", &InputSystem::clickEvent)
		.addFunction("getMouseX", &InputSystem::getMouseX)
		.addFunction("getMouseY", &InputSystem::getMouseY)
		.addFunction("getTicks", &InputSystem::getTicks)
		.endClass();
	
	//common
	getGlobalNamespace(L).beginClass<Component>("Component")
		.addFunction("isActive", &Component::isActive)
		.addFunction("getEntity", &Component::getEntity)
		.endClass();

	
	getGlobalNamespace(L).deriveClass<Transform, Component>("Transform")
		.addFunction("getPosition", &Transform::getPos)
		.addFunction("setPosition", &Transform::setPos)
		.addFunction("getRotation", &Transform::getRot)
		.addFunction("setRotation", &Transform::setRot)
		.addFunction("getDimensions", &Transform::getDimensions)
		.addFunction("setDimensions", &Transform::setDimensions)
		.endClass();

	//phisics
	getGlobalNamespace(L).deriveClass<RigidBody, Component>("Rigidbody")
		.addFunction("setPosition", &RigidBody::setPosition)
		.addFunction("addForce1", &RigidBody::addForce)
		.addFunction("setGravity", &RigidBody::setGravity)
		.addFunction("addTorque",&RigidBody::addTorque)
		.addFunction("setGravity", &RigidBody::setGravity)
		.addFunction("setTrigger", &RigidBody::setTrigger)
		.addFunction("isTrigger", &RigidBody::isTrigger)
		.addFunction("setKinematic", &RigidBody::setKinematic)
		.addFunction("isKinematic", &RigidBody::isKinematic)
		.addFunction("setStatic", &RigidBody::setStatic)
		.addFunction("isStatic", &RigidBody::isStatic)
		.addFunction("setLinearVelocity",& RigidBody::setLinearVelocity)
		.addFunction("getLinearVelocity", &RigidBody::getLinearVelocity)
		.addFunction("onCollisionEnter", &RigidBody::onCollisionEnter)
		.addFunction("collidesWithTag", &RigidBody::collidesWithTag)
		.addFunction("getGroup", &RigidBody::getGroup)
		.addFunction("getMask", &RigidBody::getMask)
		.addFunction("setLinearFactor", &RigidBody::setLinearFactor)
		.addFunction("setAngularFactor", &RigidBody::setAngularFactor)
		.endClass();

	//graphics
	getGlobalNamespace(L).deriveClass<MeshComponent,Component>("Mesh")
		.addFunction("setActive", &MeshComponent::setActive)
		.addFunction("setMaterial", &MeshComponent::setMaterial)
		.endClass();

	getGlobalNamespace(L).deriveClass<Camera,Component>("Camera")
		.addFunction("setCameraPos", &Camera::setCameraPosition)
		.addFunction("getCameraPos", &Camera::getCameraPosition)
		.addFunction("setCameraDir", &Camera::setCameraDir)
		.addFunction("setBackgroundColor", &Camera::setBackgroundColor)
		.addFunction("setNearClipDistance", &Camera::setNearClipDistance)
		.addFunction("setFarClipDistance", &Camera::setFarClipDistance)
		.addFunction("getScreenCoordinates", &Camera::getScreenCoordinates)
		.endClass();

	getGlobalNamespace(L).deriveClass<LightComponent,Component>("Light")
		.addFunction("turnOn", &LightComponent::turnOn)
		.addFunction("turnOff", &LightComponent::turnOff)
		.addFunction("setColor", &LightComponent::setColor)
		.addFunction("setLightPower", &LightComponent::setLightPower)
		.addFunction("setCastShadow", &LightComponent::setCastShadow)
		.endClass();
	getGlobalNamespace(L).deriveClass<PlaneComponent, Component>("Plane")
		.addFunction("setMaterial", &PlaneComponent::setMaterial)
		.endClass();

	getGlobalNamespace(L).beginClass<OgreContext>("OgreContext")
		.addFunction("getWindowWidth", &OgreContext::getWindowWidth)
		.addFunction("getWindowHeight", &OgreContext::getWindowHeight)
		.addFunction("setSkyPlane", &OgreContext::setSkyPlane)
		.addFunction("changeMaterialScroll", &OgreContext::changeMaterialScroll)
		.addFunction("createZPlane", &OgreContext::createZPlane)
		.endClass();
	//UI
	getGlobalNamespace(L).deriveClass<UIButton, Component>("Button")
		.addFunction("getButtonPressed", &UIButton::getButtonPressed)
		.addFunction("buttonWasPressed", &UIButton::buttonWasPressed)
		.addFunction("buttonNotPressed", &UIButton::buttonNotPressed)
		.addFunction("setText", &UIButton::setText)
		.endClass();

	getGlobalNamespace(L).deriveClass<UILabel, Component>("Label")
		.addFunction("setText", &UILabel::setText)
		.endClass();

	getGlobalNamespace(L).beginClass<Scene>("Scene")
		.addFunction("clean", &Scene::clean)
		.addFunction("addEntity", &Scene::addEntity)
		.addFunction("setName", &Scene::setName)
		.addFunction("getName", &Scene::getName)
		.addFunction("getEntity", &Scene::getEntity)
		.addFunction("destroyEntity", &Scene::killEntity)
		.addFunction("destroyEntityByName", &Scene::killEntityByName)
		.endClass();		

	getGlobalNamespace(L).beginClass<LUAManager>("LuaManager")
		.addFunction("getEntity", &LUAManager::getEntity)
		.addFunction("getInputManager", &LUAManager::getInputManager)
		.addFunction("getLight", &LUAManager::getLightComponent)
		.addFunction("getRigidbody", &LUAManager::getRigidbody)
		.addFunction("getCamera", &LUAManager::getCamera)
		.addFunction("getPlane", &LUAManager::getPlaneComponent)
		.addFunction("getMesh", &LUAManager::getMeshComponent)
		.addFunction("getTransform", &LUAManager::getTransform)
		.addFunction("getLuaClass", &LUAManager::getLuaClass)
		.addFunction("instantiate", &LUAManager::instantiate)
		.addFunction("getCurrentScene", &LUAManager::getCurrentScene)
		.addFunction("getUIButton", &LUAManager::getUIButton)
		.addFunction("getUILabel", &LUAManager::getUILabel)
		.addFunction("getLuaSelf", &LUAManager::getLuaSelf)
		.addFunction("getOgreContext", &LUAManager::getOgreContext)
		.addFunction("changeScene", &LUAManager::changeScene)
		.addFunction("closeApp", &LUAManager::closeApp)
		.addFunction("setMusic", &LUAManager::setMusic)
		.endClass();
}

void LUAManager::setMusic(std::string music) {

	try {
		AudioSystem::getInstance()->stopAllChannels();
		AudioSystem::getInstance()->playSound(music, { 0, 0, 0 });
	}
	catch (std::exception& e) {
		std::cout << "El nombre /" << music << "/ es inapropiado.\n" << e.what() << std::endl;
	}
}

bool LUAManager::reloadLuaScript(lua_State* L, const std::string& luafile) {
	int state = luaL_dofile(L, luafile.c_str());
	
	if (state != LUA_OK) {
		return false;
	}
	return true;
}

Entity* LUAManager::getEntity(std::string name)
{
	Entity* ent = SceneManager::getInstance()->getCurrentScene()->getEntity(name);
	return ent;
}

void LUAManager::changeScene(std::string name)
{
	SceneManager::getInstance()->changeScene(name);
}

RigidBody* LUAManager::getRigidbody(Entity* ent)
{
	RigidBody* r = nullptr;
	if(ent->hasComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId))
		r = static_cast<RigidBody*>(ent->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId));
	return r;
}

InputSystem* LUAManager::getInputManager()
{
	return InputSystem::getInstance();
}

MeshComponent* LUAManager::getMeshComponent(Entity* ent)
{
	MeshComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh))
		m = static_cast<MeshComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh));
	return m;
}

PlaneComponent* LUAManager::getPlaneComponent(Entity* ent)
{
	PlaneComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Plane))
		m = static_cast<PlaneComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Plane));
	return m;
}

LightComponent* LUAManager::getLightComponent(Entity* ent)
{
	LightComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Light))
		m = static_cast<LightComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Light));
	return m;
}

Camera* LUAManager::getCamera(Entity* ent)
{
	Camera* m = nullptr;
	if (ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Camera))
		m = static_cast<Camera*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Camera));
	return m;
}

Transform* LUAManager::getTransform(Entity* ent)
{
	Transform* m = nullptr;
	if (ent->hasComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId))
		m = static_cast<Transform*>(ent->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	return m;
}

luabridge::LuaRef LUAManager::getLuaClass(const std::string& c_name)
{
	luabridge::LuaRef m = luabridge::LuaRef(L);//nil
	auto it = classes_.find(c_name);
	if (it != classes_.end()) {
		m = it->second;
	}
	return m;
}

Entity* LUAManager::instantiate(std::string prefabName)
{
	Entity* e = new Entity();
	LoaderSystem s;

	s.loadPrefabByName(prefabName, e);
	SceneManager::getCurrentScene()->addEntity(prefabName, e);
	//e->start();
	return e;
}

UIButton* LUAManager::getUIButton(Entity* ent)
{
	UIButton* b = nullptr;
	if (ent->hasComponent((int)ManID::UI, (int)UIManager::UICmpId::Button))
		b = static_cast<UIButton*>(ent->getComponent((int)ManID::UI, (int)UIManager::UICmpId::Button));
	return b;
}

UILabel* LUAManager::getUILabel(Entity* ent)
{
	UILabel* b = nullptr;
	if (ent->hasComponent((int)ManID::UI, (int)UIManager::UICmpId::Label))
		b = static_cast<UILabel*>(ent->getComponent((int)ManID::UI, (int)UIManager::UICmpId::Label));
	return b;
}

luabridge::LuaRef LUAManager::getLuaSelf(Entity* ent, const std::string& c_name)
{
	luabridge::LuaRef b = luabridge::LuaRef(L);
	if (ent->hasComponent((int)ManID::LUA, enum_map_[c_name]))
		b = static_cast<LuaComponent*>(ent->getComponent((int)ManID::LUA, enum_map_[c_name]))->getSelf();
	return b;
}

void LUAManager::addRegistry(const std::string& compName)
{
	auto ok = reloadLuaScript(L, SCRIPTS_FILE_PATH + compName + FILE_EXTENSION);
	if (ok) {
		lua_setglobal(L, compName.c_str());
		classes_.emplace(compName, luabridge::getGlobal(L, compName.c_str()));
		int id = registeredFiles;
		registerComponent(compName, registeredFiles, [compName, id]() -> LuaComponent* { return new LuaComponent(compName, id); });
		registeredFiles++;
	}
	else {
		throw std::runtime_error("ERROR: Couldn't load component " + compName);
	}
}

OgreContext* LUAManager::getOgreContext()
{
	return OgreContext::getInstance();
}

Scene* LUAManager::getCurrentScene()
{
	return SceneManager::getInstance()->getCurrentScene();
}

lua_State* LUAManager::getLuaState() const
{
	return L;
}

void LUAManager::closeApp() {
	PapagayoEngine::getInstance()->closeApp();
}

LUAManager::LUAManager() : Manager(ManID::LUA), registeredFiles(0)
{
	//Inicializacion del estado de LUA
	L = luaL_newstate();
	//buildLuaEngine("LuaScripts/clases.lua");
	luaL_openlibs(L);
	
	//Registro de las funciones
	if (L) {
		registerClassAndFunctions(L);
	}
	else throw std::exception("ERROR: LUA is not compiling correctly\n");
	
	//Registro de componentes
	//registerComponent("default", registeredFiles++, []() -> LuaComponent* { return new LuaComponent(); });
	addRegistry("default");
}