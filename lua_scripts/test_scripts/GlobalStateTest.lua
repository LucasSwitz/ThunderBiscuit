GlobalStateTest = {
    Enter=function(character)
        character:SetInternalValue("EnterGlobalState",1)
    end,
    Execute=function(character)
        character:SetInternalValue("ExecuteGlobalState",1)
    end,
    Exit=function(character)
        character:SetInternalValue("ExitGlobalState",1)
    end
}