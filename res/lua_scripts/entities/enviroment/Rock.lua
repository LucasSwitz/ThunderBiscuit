--PREAMBLE_START
ScriptType = "Entity"
Name = "Rock"
PrototypeID = 888
--PREAMBLE_END

Rock = 
{
    Components = 
    {
        Position = 
        {
            x = 0,
            y = 0
        },
        Graphics = 
        {
            sprite = Res("rock.png"),
            width = 100,
            height = 100,
            layer = 1
        },
        Mass = 
        {
            mass = 10000
        },
        Collision = 
        {
            width = 24,
            height = 24,
            collision_script = Res("ZeroRestitutionWallCollision.lua"),
        },
        Velocity =
        {
            x = 0,
            y = 0
        }
    }
}