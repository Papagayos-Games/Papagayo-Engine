k = loadfile("LuaScripts/keycode.lua")
k()

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

function addTorque(rig)

    vec = Vector3(100, 100, 1000);
    rel = Vector3(0, 0, 0);
    rig:addTorque(vec, rel, 1);
end

