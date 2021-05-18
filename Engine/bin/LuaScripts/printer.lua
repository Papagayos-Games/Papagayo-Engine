local printer = {}

printer["instantiate"] = function (params, entity)
    local self = {}
    self.entity = entity
    return self
end

printer["start"] = function (_self, lua)
end

printer["update"] = function (_self, lua)
end

printer["print"] = function (sth)
    print(sth)
end
return printer