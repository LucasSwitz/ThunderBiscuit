--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    Update = function(graphics_system,time, engine)
        local drawables = LuaListComponentUser()
        engine:ComponentUsers():GetAll(drawables,{"Graphics","Position"})
        local it = drawables:Iterator()
        while it ~= nil do
            local drawable = it.data
            local e = Event.ComponentUserEvent(EventType.DRAW_REQUEST_EVENT,0,TARGET_WINDOW(),drawable)
            engine:EventManager():LaunchEvent(e)
            it = it.next
        end
    end
}
