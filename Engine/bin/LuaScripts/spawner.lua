local JSON = assert(loadfile "LuaScripts/json.lua")()
local spawner = {}

local function createfunc (_self, lua, object) 
    local pos = lua:getTransform(_self.entity):getPosition()
    lua:getTransform(object):setPosition(Vector3(pos.x, pos.y, pos.z - 100))
end

spawner["instantiate"] = function (params, entity)
    p = JSON:decode(params)
    local self = {}
    --Objeto a spawnear
    if p.spawnObject ~= nil then
        self.spawnObject = p.spawnObject
    else
        self.spawnObject = "meteor"
    end

    --Cada cuantos segundos spawnea
    if p.timeToSpawn ~= nil then
        self.timeToSpawn = p.timeToSpawn
    else
        self.timeToSpawn = 1.5
    end
    
    self.entity =  entity
    return self
end

spawner["start"] = function (_self, lua)
    _self.timeSinceSpawn = lua:getInputManager():getTicks()
end

spawner["update"] = function (_self, lua)
    if (lua:getInputManager():getTicks() - _self.timeSinceSpawn)/1000  >= _self.timeToSpawn then
        print(_self.spawnObject)
        local objectSpawned = lua:instantiate(_self.spawnObject)
        createfunc(_self,lua, objectSpawned)
        
        objectSpawned:start();

        _self.timeSinceSpawn = lua:getInputManager():getTicks()
    end 
end

return spawner