ScriptType = "State"
StateOwner = "Character"
StateName = "Global"

CharacterGlobalState = {
    Enter=function(character)
    end,
    Execute=function(character)
        character:SetInternalValue("ExecuteGlobalState",1)
    end,
    Exit=function(character)
    end
}