#include "Component.h"
#include "CollisionObject.h"
#include "lua.hpp"
#include <LuaBridge.h>

#include "checkML.h"

struct lua_State;
class LuaRef;
class Rigidbody;

class LuaComponent : public Component, public CollisionObject {
private:
	//luabridge::LuaRef* class_;
	luabridge::LuaRef* self_;

	//Referencia al LUASTATE
	lua_State* currState = nullptr;
	

	//Gestión de errores
	std::error_code errorCode;

	std::string fileName_;

public:
	LuaComponent(const std::string& fileName = "default", int id = 0);
	virtual ~LuaComponent();

	//Inicialización del componente
	virtual void init()override;
	//Carga desde archivo JSON
	virtual void load(const nlohmann::json& params) override;
	// 
	virtual void setUp() override;
	//Llamada a funciones de LUA
	virtual void update(float deltaTime) override;

	void fixedUpdate(float deltaTime);

	// Callbacks de colision
	void onCollisionEnter(Entity* other) override;


	const std::string& getFileName();
	const std::string& getFileName() const;
	const luabridge::LuaRef* getSelf() const;


};
