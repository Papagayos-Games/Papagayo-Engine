k = loadfile("LuaScripts/keycode.lua")
k()

i = "Me quiero morir\n"
print("HazCosas\n");


local function prueba()
    print("Soy una funcion de otro script")
end

function setPosition(rig)

    vec = Vector3(200, 0, 0);
    rig:setPosition(vec);
end

function addForce(rig)

    vec = Vector3(100, 100, 1000);
    rel = Vector3(0, 0, 0);
    rig:addForce1(vec, rel, 1);
end

function setgravity(rig)

    vec = Vector3(0, 10, 0);
    rig:setGravity(vec);
end

function pressKeyDoSomething(input, rig)
    if input:keyPressed(Keycode.A) == true then
        print("Pulse A perros");
        print(i);
        vec = Vector3(-10, 0, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.S) == true then
        print("Pulse S perros");
        print(i);
        vec = Vector3(0, -10, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.W) == true then
        print("Pulse W perros");
        print(i);
        vec = Vector3(0, 10, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.D) == true then
        print("Pulse D perros");
        print(i);
        vec = Vector3(10, 0, 0);
        rel = Vector3(0, 0, 0);
        rig:addForce1(vec, rel, 1);
    end
    if input:keyPressed(Keycode.Escape) == true then print("Escape perro") end
    if input:mouseButtonPressed() == MouseButton.Left then print("[LUA] Left Click") end
    if input:mouseButtonPressed() == MouseButton.Right then print("[LUA] Right Click") end
end

function addTorque(rig)

    vec = Vector3(100, 100, 1000);
    rel = Vector3(0, 0, 0);
    rig:addTorque(vec, rel, 1);
end

local miclase = {}

function miclase:instantiate()
    return "Hola"
end

--local function miclase.start(self, lua)
--    self.hp = lua.GetMiFuncionGlobalQueMeCambiaLaVida()
--end

--local function miclase.update(self, lua)
--    if lua.keydown(space) then
--        print(self.damage)
--    end
--end

return miclase
