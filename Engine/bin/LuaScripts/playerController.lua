local JSON = assert(loadfile "LuaScripts/json.lua")()
local keys = assert(loadfile "LuaScripts/keycode.lua")()

--CLASE PLAYERCONTROLLER
local playerController = {}

playerController["instantiate"] = function (params, entity)
    print("Instantiate: playerController")
    p = JSON:decode(params)
    local self = {}
    self.entity = entity
    --Si se olvida asignar la velocidad se pone 1 por defecto
    if p.speed ~= nil then
        self.speed = p.speed
    else
        self.speed = 1
    end
    
    return self
end

playerController["start"] = function (_self, lua)
    print("Start: playerController")

    --Cogemos el transform y el rigidbody del objeto
    _self.transform =  lua:getTransform(_self.entity)
    _self.rigidbody = lua:getRigidbody(_self.entity)
    _self.position = _self.transform:getPosition()

    --Tamaño de la ventana en Y
    _self.limitY = lua:getOgreContext():getWindowHeight()

    --Camara principal de la escena
    _self.mainCamera = lua:getCamera(lua:getEntity("defaultCamera"))

end

playerController["update"] = function (_self, lua)
    
    --Cogemos la posicion del raton
    _self.mouseX = lua:getInputManager():getMouseX()
    _self.mouseY = lua:getInputManager():getMouseY()
    print("me muevo")

    --Calculamos la posicion del pinguino en el viewport
    local screenPosition = _self.mainCamera:getScreenCoordinates(_self.position)

    --Direccion hacia la que tenemos que mover al jugador
    --Hay que invertir las coordenadas del raton en el eje Y
    local dir =  Vector3( _self.mouseX - screenPosition.x,  (_self.limitY - _self.mouseY) - screenPosition.y, 0)
    local mag = dir:normalize()

    --Desplazamos si la magnitud es mayor que la velocidad
    if mag > _self.speed then 
        local newPos = Vector3(_self.position.x + dir.x * _self.speed, _self.position.y + dir.y * _self.speed  ,_self.position.z)
        _self.rigidbody:setPosition(newPos)
    end
end

return playerController