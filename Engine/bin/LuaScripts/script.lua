k = loadfile("LuaScripts/keycode.lua")
k()

local input_ = nil--Pillar desde c++
local rig_ = nil--Pillar desde c++

function start(input, rig)
    input_ = input;
    print(input_);
    rig_ = rig;
    print(rig_);
end

function update()
    print("Coso del update");
    pressKeyDoSomething(input_, rig_);
    print("Final update");
end

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
    print("KeyPressed");
    if input:keyPressed(Keycode.Escape) == true then print("Escape perro") end
    if input:mouseButtonPressed() == MouseButton.Left then print("[LUA] Left Click") end
    if input:mouseButtonPressed() == MouseButton.Right then print("[LUA] Right Click") end
   
end