--PREAMBLE_START
ScriptType = "Entity"
Name = "Mario"
PrototypeID = 1000
--PREAMBLE_END

Mario = 
{
        id = 0,
        Components = 
        {
            Player = 
            {   
                id = 1,
                controller_id = 1,
                controller_type = 0
            },
            Position = 
            {
                x = 90,
                y = 90,
                heading = 0
            },
            Graphics = 
            {
                sprite = Res("mario_1.png"),
                layer = 1,
                width = 32,
                height = 32
            },
            Velocity =
            {
                x = 0, -- px/second
                y = 0,
                max = 100,
            },
            Acceleration = 
            {
                force_x = 0,
                force_y = 0,
                x = 0,
                y= 0
            },
            Mass = 
            {
                mass = 10
            },
            Collision = 
            {
                width = 32,
                height = 32,
                collision_script = Res("CharacterCollision.lua")
            },
            State = 
            {
                state = Res("CharacterIdleState.lua"),
                stage = "Start",
                time = 0
            },
            Animation =
            {
                animation = "Idle",
                current_frame = "Still",
                current_frame_time_left = 0.0,
                next_frame = "Still",
                started = false,
                is_finished = false,
                Animations = 
                {
                    Walking = 
                    {
                        start_frame = "Frame1",
                        Frames  =
                        {
                            Frame1 = 
                            {
                                duration = 0.1,
                                sprite= Res("mario_1.png"),
                                next = "Frame2"
                            },
                            Frame2 = 
                            {
                                duration = 0.1,
                                sprite = Res("mario_2.png"),
                                next = "Frame3"
                            },
                            Frame3 = 
                            {
                                duration = 0.1,
                                sprite= Res("mario_3.png"),
                                next = "Frame4"
                            },
                            Frame4 = 
                            {
                                duration = 0.1,
                                sprite= Res("mario_4.png"),
                                next = "Frame5"
                            },
                            Frame5 = 
                            {
                                duration = 0.1,
                                sprite = Res("mario_5.png"),
                                next = "Frame6"
                            },
                            Frame6 = 
                            {
                                duration = 0.1,
                                sprite= Res("mario_6.png"),
                                next = "Frame7"
                            },
                            Frame7 = 
                            {
                                duration = 0.1,
                                sprite = Res("mario_7.png"),
                                next = "Frame1"
                            }
                        }
                    },
                    Idle = 
                    {
                        start_frame = "Still",
                        Frames = 
                        {
                            Still =
                            {
                                duration = 0,
                                sprite = Res("mario_1.png"),
                                next = "Still"
                            }
                        }
                    }
                }
            }
    }
}