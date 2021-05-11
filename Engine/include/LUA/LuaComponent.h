#include "Component.h"
#include "lua.hpp"
#include <LuaBridge.h>

struct lua_State;
class LuaRef;

class LuaComponent : public Component {
private:
	//String que identifica al nombre del METODO DE LUA
	//que llamará este componente en su update
	std::string methodName_;

	//Referencia al LUASTATE
	lua_State* currState = nullptr;
	luabridge::LuaRef* tabla;

	//Gestión de errores
	std::error_code errorCode;

public:
	LuaComponent();
	virtual ~LuaComponent();

	//Inicialización del componente
	virtual void init()override;
	//Carga desde archivo JSON
	virtual void load(const nlohmann::json& params) override;
	//Llamada a funciones de LUA
	virtual void update() override;

};
