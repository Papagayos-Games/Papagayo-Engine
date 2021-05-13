loadfile("LuaScripts/keycode.lua")()
b = loadfile("LuaScripts/prueba.lua")()
miclase = loadfile("LuaScripts/mi_clase.lua")()
a = function () print(b.instantiate()) end
print("me cargo")
sj = {}

--EJEMPLOS
--local input_ = nil--Pillar desde c++
--local rig_ = nil--Pillar desde c++

--function start(lua)
--    input_ = lua:getInputManager();
--    print(input_);
--    rig_ = lua:getEntity();
--    print(rig_);
--end

--Metodo por defecto para cuando no asignen ninguno
function default(lua)

end

function start()
    sj["vida"] = 50

    print("Principio start")
    prueba()

    print("Ejecuto bien start")
end

function patata(tabla)
    sj = tabla
    print(sj["vida"])
    sj["vida"] = tabla["vida"] -2
    print(sj["vida"])
end

function creaPinguino(lua)
    lua:instantiate("penguin2")
end


-- function update(tabla,lua)
--     --print("Coso del update")
--     --print(tabla["vida"])
--     pressKeyDoSomething(lua:getInputManager(), lua:getRigidbody1())
--     --print("Final update");
-- end

function pressKeyDoSomething(input, rig)
    if input:keyPressed(Keycode.A) == true then
        print("Pulse A perros");
        vec = Vector3(-10, 0, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.S) == true then
        print("Pulse S perros");
        vec = Vector3(0, -10, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.W) == true then
        print("Pulse W perros");
        vec = Vector3(0, 10, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.D) == true then
        print("Pulse D perros");
        vec = Vector3(10, 0, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end

    if input:keyPressed(Keycode.Escape) == true then print("Escape perro") end
    if input:mouseButtonPressed() == MouseButton.Left then print("[LUA] Left Click") end
    if input:mouseButtonPressed() == MouseButton.Right then print("[LUA] Right Click") end
   
end