
local JSON = assert(loadfile "LuaScripts/json.lua")()
local keys = assert(loadfile "LuaScripts/keycode.lua")()

local mi_clase = {}

mi_clase["instantiate"] = function (params, entity)
    p = JSON:decode(params)
    local self = {}
    self.hp = p.hp
    --self.name = p.name
    self.rb = nil
    self.entity = entity
    return self
end

mi_clase["start"] = function (_self, lua)
    --local p = lua:instantiate("penguin2")
    --local pRB = lua:getRigidbody(p)
    --pRB:setGravity(Vector3(10, 0, 0))
    --_self.rb = lua:getRigidbody(lua:getEntity("testScene2"))
    print("Start: mi clase")
    print(_self.entity:getName())
    local _printer = lua:getLuaClass(_self.entity, "printer")
    _printer["print"]("probando")
    -- local _nullCamera = lua:getCamera(_self.entity)
    -- camera:setNearClipDistance(40) 

    --local v3 = lua:getTransform(_self.entity):getPosition()
    --local v4 = Vector3(v3) --Constructor por copia

    --print("AntesVector")
    --v4:add(v3) --Esto funciona pero no v3:add(v4)
    --print("DespuesVector")

    --print(v4.x)
    --print(v4.y)
    --print(v4.z)

	--print(_self.hp)
end

mi_clase["update"] = function (_self, lua)

    _self.hp = _self.hp - 10
    -- if lua:getInputManager():keyPressed(Keycode.A) == true then
    --     lua:instantiate("penguin2")
    -- end
    --local collides = _self.rb:onCollisionEnter("penguin2")
    --if input:keyPressed(Keycode.A) == true then
    --if collides == true then
        --print("colisiono")
    --end 
end

return mi_clase