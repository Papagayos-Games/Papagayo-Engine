#include "Component.h"
#include "lua.hpp"
#include <LuaBridge.h>

struct lua_State;
class LuaRef;

class LuaComponent : public Component {
private:
	luabridge::LuaRef* class_;
	luabridge::LuaRef* self_;

	//Referencia al LUASTATE
	lua_State* currState = nullptr;
	

	//Gesti�n de errores
	std::error_code errorCode;

	std::string fileName_;

public:
	LuaComponent(const std::string& fileName = "default", int id = 0);
	virtual ~LuaComponent();

	//Inicializaci�n del componente
	virtual void init()override;
	//Carga desde archivo JSON
	virtual void load(const nlohmann::json& params) override;
	// 
	virtual void setUp() override;
	//Llamada a funciones de LUA
	virtual void update() override;

	const std::string& getFileName();
	const std::string& getFileName() const;

	const luabridge::LuaRef& getClass();
};