
local JSON = assert(loadfile "LuaScripts/json.lua")()
local keys = assert(loadfile "LuaScripts/keycode.lua")()

local mi_clase = {}

mi_clase["instantiate"] = function (params)
    p = JSON:decode(params)
    local self = {}
    self.hp = p.hp
    self.name = p.name
    return self
end

mi_clase["start"] = function (_self, lua)
    lua:instantiate("penguin2")
end

mi_clase["update"] = function (_self, lua)

    _self.hp = _self.hp - 10
    if lua:getInputManager():keyPressed(Keycode.A) == true then
        lua:instantiate("penguin2")
    end
end

return mi_clase