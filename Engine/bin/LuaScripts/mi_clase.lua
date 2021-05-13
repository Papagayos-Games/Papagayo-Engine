local mi_clase = {}

-- function mi_clase:instantiate(param)
--     local self = {}
--     self.hp = param
--     self.name = "xd"
--     self.func = function (s) print(s) end
--     return self
-- end

mi_clase["instantiate"] = function (params)
    local self = {}
    self.hp = params
    self.name = "xd"
    self.func = function (s) print(s) end
    return self
end

--local function miclase.start(self, lua)
--    self.hp = lua.GetMiFuncionGlobalQueMeCambiaLaVida()
--end

-- function mi_clase:update(_self)
--     --print(_self.name)
--     return _self
-- end

mi_clase["update"] = function (_self)
    _self.hp = _self.hp - 10
    return _self 
end

return mi_clase