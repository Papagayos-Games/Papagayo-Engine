#include <iostream>
#include "LUAManager.h"


#include <LuaBridge.h>

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
	//std::cout << "updating\n";
}


class A {
public:
	void action() { std::cout << "hello I'm A\n"; }
	virtual void doPrint(int a, int b) {
		std::cout << "in A a : " << a << " b : " << b << std::endl;
	}
	std::string goodMan() const { return "goodman"; }
};


class B : public A {
public:
	void hello(const std::string& info) const {
		std::cout << "hello: " << info << std::endl;
	}
	virtual void doPrint(int a, int b) override {
		std::cout << "in B just " << (a + b) << std::endl;
	}
};

void globalFunction() {
	std::cout << "hello this is a global func\n";
}


//Aqui van todas las funciones y clases correspondientes 
void registerClassAndFucntions(lua_State* L) {
	using namespace luabridge;
	getGlobalNamespace(L).addFunction("globalFunction", globalFunction);
	getGlobalNamespace(L)
		.beginClass<A>("A")
		.addFunction("action", &A::action)
		.addFunction("doPrint", &A::doPrint)
		.addFunction("goodMan", &A::goodMan)
		.endClass()
		.deriveClass<B, A>("B")
		.addFunction("hello", &B::hello)
		.endClass();

	//getGlobalNamespace(L).beginClass();


}

void testCallLua(lua_State* L) {
	std::error_code errorCode;

	A a;
		lua_getglobal(L, "testA");
		luabridge::push(L,&a,errorCode);
	lua_pcall(L, 1, 0, 0);
	B b;
	lua_getglobal(L, "testAAndB");
	luabridge::push(L, &a, errorCode);
	luabridge::push(L, &b, errorCode);
	lua_pcall(L, 2, 0, 0);

}

bool reloadLuaScript(lua_State* L, const std::string& luafile) {
	int state = luaL_dofile(L, luafile.c_str());
	if (state != LUA_OK) {
		// std::cout << "ok";
		return false;
	}
	return true;
}
void registerClassAndFucntions(lua_State* L);
void testCallLua(lua_State* L);

lua_State* buildLuaEngine(const std::string& file) {
	lua_State* L = luaL_newstate();
	// need check L
	luaL_openlibs(L);
	auto ok = reloadLuaScript(L, file);
	if (!ok) {
		lua_close(L);
		L = nullptr;
	}
	return L;
}


LUAManager::LUAManager() : Manager(ManID::LUA)
{

	auto L = buildLuaEngine("LuaScripts/prueba.lua");
	if (L) {
		registerClassAndFucntions(L);
		testCallLua(L);
	}
	if (L) {
		lua_close(L);
		L = nullptr;
	}
}