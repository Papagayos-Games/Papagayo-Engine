#include "LUAManager.h"

#include <iostream>


#include <LuaBridge.h>


#include <Rigidbody.h>
#include <Managers/SceneManager.h>
#include <Scene/Scene.h>
#include <Vector3.h>
#include <PhysicsManager.h>
#include <./Input/InputSystem.h>
#include "LuaComponent.h"




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
	lua_close(L);
	L = nullptr;
}

LUAManager* LUAManager::getInstance()
{
	if (instance_ == nullptr) {
		instance_ = new LUAManager();
	}

	return instance_;
}

void LUAManager::start()
{
}

void LUAManager::update()
{
	for (Component* cmp : _compsList)
	{
		cmp->update();
	}
}


//Aqui van todas las funciones y clases correspondientes 
void LUAManager::registerClassAndFunctions(lua_State* L) {

	getGlobalNamespace(L).beginClass<Vector3>("Vector3")
		.addConstructor<void (*) (float, float, float)>()
		.addProperty("x", &Vector3::x)
		.addProperty("y", &Vector3::y)
		.addProperty("z", &Vector3::z)
		.endClass();


	getGlobalNamespace(L).beginClass<RigidBody>("Rigidbody")
		.addFunction("setPosition", &RigidBody::setPosition)
		.addFunction("addForce1", &RigidBody::addForce)
		.addFunction("setGravity", &RigidBody::setGravity)
		.addFunction("addTorque", &RigidBody::addTorque)
		.endClass();

	getGlobalNamespace(L).beginClass<InputSystem>("InputSystem")
		.addFunction("keyPressed", &InputSystem::isKeyDown)
		.addFunction("mouseButtonPressed", &InputSystem::clickEvent)
		.endClass();


	getGlobalNamespace(L).beginClass<LUAManager>("LuaManager")
		.addFunction("getEntity", &LUAManager::getEntity)
		.addFunction("getInputManager", &LUAManager::getInputManager)
		.endClass();
}

void LUAManager::testCallLua(lua_State* L) {
	std::error_code errorCode;
	using namespace luabridge;


	/*A a;
		lua_getglobal(L, "testA");
		luabridge::push(L,&a,errorCode);
	lua_pcall(L, 1, 0, 0);
	B b;
	lua_getglobal(L, "testAAndB");
	luabridge::push(L, &a, errorCode);
	luabridge::push(L, &b, errorCode);
	lua_pcall(L, 2, 0, 0);
	*/


	/*
	lua_getglobal(L, "setPosition");
	push(L, static_cast<RigidBody*>(SceneManager::getInstance()->getCurrentScene()->entities_.back()
	->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId)), errorCode);
	pcall(L, 1, 0, 0);*/

	/*lua_getglobal(L, "addTorque");
	push(L, static_cast<RigidBody*>(SceneManager::getInstance()->getCurrentScene()->entities_.back()
	->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId)), errorCode);
	lua_pcall(L, 3, 0, 0);*/


	/*lua_getglobal(L, "addForce");
	push(L, static_cast<RigidBody*>(SceneManager::getInstance()->getCurrentScene()->entities_.back()
	->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId)), errorCode);
	pcall(L, 1, 0, 0);*/

	/*lua_getglobal(L, "setgravity");
	push(L, static_cast<RigidBody*>(SceneManager::getInstance()->getCurrentScene()->entities_.back()
	->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId)), errorCode);
	lua_pcall(L, 1, 0, 0);*/

	/*lua_getglobal(L, "pressKeyDoSomething");
	push(L, InputSystem::getInstance(), errorCode);
	lua_pcall(L, 1, 0, 0);
	*/


}

bool LUAManager::reloadLuaScript(lua_State* L, const std::string& luafile) {
	int state = luaL_dofile(L, luafile.c_str());
	if (state != LUA_OK) {
		// std::cout << "ok";
		return false;
	}
	return true;
}

//TEMPORAL
RigidBody* LUAManager::getEntity()
{
	std::error_code errorCode;

	RigidBody* r = static_cast<RigidBody*>(SceneManager::getInstance()->getCurrentScene()->entities_.back()
		->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId));

	push(L, r, errorCode);
	return r;
}
//TEMPORAL
InputSystem* LUAManager::getInputManager()
{
	std::error_code errorCode;
	push(L, InputSystem::getInstance(), errorCode);
	return InputSystem::getInstance();
}

lua_State* LUAManager::getLuaState() const
{
	return L;
}

void LUAManager::buildLuaEngine(const std::string& file) {
	// need check L
	luaL_openlibs(L);
	auto ok = reloadLuaScript(L, file);
	if (!ok) {
		lua_close(L);
		L = nullptr;
	}
}

LUAManager::LUAManager() : Manager(ManID::LUA)
{
	//Registro de componentes
	registerComponent("LuaComponent", []() -> LuaComponent* { return new LuaComponent(); });

	//Inicializacion del estado de LUA
	L = luaL_newstate();
	buildLuaEngine("LuaScripts/script.lua");

	if (L) {
		registerClassAndFunctions(L);
		testCallLua(L);

	}
}