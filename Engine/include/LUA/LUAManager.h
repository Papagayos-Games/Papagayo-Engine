#pragma once

#ifndef _LUA_MANAGER_H
#define _LUA_MANAGER_H

// Link to lua library
#ifdef _WIN64
#pragma comment(lib, "liblua54.a")
#endif
#include <string>
#include "Manager.h"
#include "lua.hpp"

namespace luabridge {
	class LuaRef;
}

class Entity;
class RigidBody;
class InputSystem;
class RigidBody;
class InputSystem;
class MeshComponent;
class Camera;
class LightComponent;
class PlaneComponent;
class Transform;


class LUAManager : public Manager {
private:
	lua_State* L;
	
	LUAManager();
	static LUAManager* instance_;

	int registeredFiles = 0;
	
	bool CheckLua(lua_State* L, int r);
	void buildLuaEngine(const std::string& file);
	void registerClassAndFunctions(lua_State* L);
	bool reloadLuaScript(lua_State* L, const std::string& luafile);

public:
	~LUAManager();

	static LUAManager* getInstance();

	//METODOS DE PRUEBA
	Entity* getEntity(std::string name);
	InputSystem* getInputManager();
	RigidBody* getRigidbody(Entity* ent);
	MeshComponent* getMeshComponent(Entity* ent);
	PlaneComponent* getPlaneComponent(Entity* ent);
	LightComponent* getLightComponent(Entity* ent);
	Camera* getCamera(Entity* ent);
	Transform* getTransform(Entity* ent);
	luabridge::LuaRef getLuaClass(Entity* ent, const std::string& c_name);
	Entity* instantiate(std::string prefabName);

	void addRegistry(const std::string& compName);

	//Obtener el estado de LUA
	lua_State* getLuaState()const;
	//Metodos heredados de la clase padre
	virtual void start() override;
	virtual void update() override;

};

#endif // _LUA_MANAGER_H
