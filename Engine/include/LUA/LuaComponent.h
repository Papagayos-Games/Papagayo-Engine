#include "Component.h"
#include "lua.hpp"
#include <LuaBridge.h>
#include "checkML.h"

struct lua_State;
class LuaRef;
class Rigidbody;


class LuaComponent : public Component {
private:
	//Referencia a la tabla asociada a este componente de LUA
	luabridge::LuaRef* self_;

	//Referencia al LUASTATE
	lua_State* currState = nullptr;
	
	//Gestión de errores
	std::error_code errorCode;

	//Nombre del fichero asociado a este componente
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

	//Getter: Filename
	const std::string& getFileName();
	const std::string& getFileName() const;

	//Getter: tabla de lua asociada a este componente
	const luabridge::LuaRef* getSelf() const;

};
