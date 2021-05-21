local JSON = assert(loadfile "LuaScripts/json.lua")()
local bullet = {}

bullet["instantiate"] = function (params, entity)
    p = JSON:decode(params)
    local self = {}
    
    --En segundos el tiempo
    if p.lifetime ~= nil then
        self.lifetime = p.speed
    else
        self.lifetime = 3
    end
    
    self.entity =  entity
    return self
end

bullet["start"] = function (_self, lua)
    _self.startTime = lua:getInputManager():getTicks()
end

bullet["update"] = function (_self, lua)

    if (lua:getInputManager():getTicks() - _self.startTime)/1000  >= _self.lifetime then
        lua:getCurrentScene():destroyEntity(_self.entity)
        print("ded")
    end 
end

return bullet