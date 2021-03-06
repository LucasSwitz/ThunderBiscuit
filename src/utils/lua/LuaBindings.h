#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include <LuaBridge/LuaBridge.h>
#include "src/utils/state/ScriptableStateMachine.h"
#include "src/game_objects/EntityManager.h"
#include "src/utils/lua/LuaList.h"
#include "src/event/Subscription.h"
#include "src/event/EventType.h"
#include "src/event/Event.h"
#include "src/game/EngineGlobals.h"
#include "src/game/GameState.h"
#include "src/game_objects/LuaEntity.h"
#include "src/game_objects/LuaEntityFactory.h"
#include "src/component/ComponentUserBase.h"
#include "src/component/ComponentUser.h"
#include "src/world/tile/Tile.h"
#include "src/world/stage/Stage.h"
#include "src/world/stage/Instance.h"
#include "src/utils/debug/DebugFlags.h"
#include "src/world/stage/LuaInstance.h"
#include "src/world/stage/LuaStage.h"
#include "src/graphics/gui/TBWindow.h"
#include "src/event/EventManager.h"
#include "src/event/EngineEventManager.h"
#include "src/controllers/Controller.h"
#include "src/controllers/KeyboardSideScrollerPlayerController.h"
#include "src/controllers/ControllerBase.h"
#include "src/controllers/SideScrollerPlayerInterface.h"
#include "src/controllers/ControllerBase.h"
#include "src/utils/Globals.h"
#include "src/engine/Engine.h"

using namespace luabridge;
class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .addFunction("Res",&Globals::GetResource)
            .addFunction("TARGET_WINDOW",&EngineGlobals::GetTargetWindow)
            .addFunction("GetController",&ControllerBase::GetController)
            .addFunction("SSPIDowncast",&SideScrollerPlayerInterface::Downcast)
            .beginClass<ComponentUser>("ComponentUser")
                .addFunction("GetNumber", &ComponentUser::GetComponentValueFloat)
                .addFunction("SetNumber", &ComponentUser::SetComponentValueFloat)
                .addFunction("GetString", &ComponentUser::GetComponentValueString)
                .addFunction("SetString", &ComponentUser::SetComponentValueString)
                .addFunction("SetBool", &ComponentUser::SetComponentValueBool)
                .addFunction("GetBool", &ComponentUser::GetComponentValueBool)
                .addFunction("GetComponent", &ComponentUser::GetComponentUnshared)
                .addFunction("HasComponent",&ComponentUser::HasComponent)
                .addProperty("id",&ComponentUser::ID)
            .endClass()
            .deriveClass<Entity, ComponentUser>("Entity")
                .addConstructor<void(*)(void)>()
                .addFunction("IsType", &Entity::IsType)
                .addFunction("Call", &Entity::CallFunction)
                .addStaticData("CPP_DEFINED_ENTITY", &Entity::CPP_DEFINED_ENTITY)
                .addStaticData("LUA_DEFINED_ENTITY", &Entity::LUA_DEFINED_ENTITY)
                .addStaticFunction("Downcast",&Entity::DowncastFromComponentUser)
                .addProperty("instance",&Entity::GetInstance,&Entity::SetInstance)
            .endClass()
            .deriveClass<LuaEntity, Entity>("LuaEntity")
                .addStaticFunction("Downcast",&LuaEntity::DownCastFromEntity)
                .addFunction("Add", &LuaEntity::AddComponent)
                .addFunction("Remove", &LuaEntity::RemoveComponent)
                .addFunction("AsTable",&LuaEntity::AsTable)
                .addFunction("Call",&LuaEntity::CallFunction)
                .addFunction("SetNumberL", &LuaEntity::SetNumber)
            .endClass()
            .beginClass<LuaListNode<ComponentUser*>>("LuaListComponentUserIterator")
                .addData("data",&LuaListNode<ComponentUser*>::data)
                .addData("next", &LuaListNode<ComponentUser*>::next)
            .endClass()
            .beginClass<LuaListNode<Entity*>>("LuaListEntityIterator")
                .addData("data",&LuaListNode<Entity*>::data)
                .addData("next", &LuaListNode<Entity*>::next)
            .endClass()
            .beginClass<LuaList<ComponentUser*>>("LuaListComponentUser")
                .addConstructor<void (*)(void)>()
                .addFunction("Iterator", &LuaList<ComponentUser*>::Iterator)
                .addFunction("Size",&LuaList<ComponentUser*>::Size)
                .addFunction("Free",&LuaList<ComponentUser*>::Free)
            .endClass()
            .beginClass<LuaList<Entity*>>("LuaListEntity")
                .addConstructor<void (*)(void)>()
                .addFunction("Iterator", &LuaList<Entity*>::Iterator)
                .addFunction("Size",&LuaList<Entity*>::Size)
            .endClass()
            .beginClass<EntityManager>("EntityManager")
                .addFunction("size", &EntityManager::GetNumberOfEntities)
                .addFunction("Get", &EntityManager::GetEntityByID)
                .addFunction("AsLuaList", &EntityManager::AsLuaList)
                .addFunction("Last",&EntityManager::GetNewestUnshared)
            .endClass()
            .beginClass<Component>("Component")
                .addFunction("GetNumber", &Component::GetFloatValue)
                .addFunction("GetString", &Component::GetStringValue)
                .addFunction("SetNumber", &Component::SetFloatValue)
                .addFunction("SetString", &Component::SetStringValue)
                .addFunction("GetBool",&Component::GetBoolValue)
                .addFunction("SetBool",&Component::SetBoolValue)
                .addFunction("GetSubcomponent", &Component::GetSubcomponentUnshared)
            .endClass()
            .beginClass<Subscription>("Subscription")
                .addConstructor<void (*)(int)>()
            .endClass()
            .beginClass<EventType>("EventType")
                .addStaticData("HEALTH_UPDATE_EVENT", &EventType::HEALTH_UPDATE_EVENT, false)
                .addStaticData("COLLISION_EVENT", &EventType::COLLISION_EVENT, false)
                .addStaticData("DAMAGE_EVENT", &EventType::DAMAGE_EVENT, false)
                .addStaticData("DELETE_ENTITY_EVENT", &EventType::DELETE_ENTITY_EVENT, false)
                .addStaticData("CONDITION_ADD_EVENT", &EventType::CONDITION_ADD_EVENT, false)
                .addStaticData("W_DOWN_EVENT", &EventType::W_DOWN_EVENT, false)
                .addStaticData("W_UP_EVENT", &EventType::W_UP_EVENT, false)
                .addStaticData("S_DOWN_EVENT", &EventType::S_DOWN_EVENT, false)
                .addStaticData("S_UP_EVENT", &EventType::S_UP_EVENT, false)
                .addStaticData("DRAW_REQUEST_EVENT",&EventType::DRAW_REQUEST_EVENT,false)
                .addStaticData("SPAWN_ENTITY_EVENT_PROTOTYPE",&EventType::SPAWN_ENTITY_EVENT_PROTOTYPE,false)
                .addStaticData("RECENTER_VIEW_EVENT",&EventType::RECENTER_VIEW_EVENT,false)
                .addStaticData("START_SYSTEM_EVENT",&EventType::START_SYSTEM_EVENT,false)
                .addStaticData("STOP_SYSTEM_EVENT",&EventType::STOP_SYSTEM_EVENT,false)
            .endClass()
            .beginClass<Event>("Event")
                .addConstructor<void (*)(int,int,int)>()
                .addStaticFunction("ComponentUserEvent",&Event::Create<ComponentUser>)
                .addStaticFunction("EntityEvent",&Event::Create<Entity>)
                .addStaticFunction("FloatsEvent",&Event::CreateTFloats)
                .addStaticFunction("StringsEvent",&Event::CreateTStrings)
                .addData("id", &Event::id)
                .addData("sender", &Event::sender_id)
                .addData("target", &Event::target_id)
            .endClass()
            .beginClass<EventManager>("EventManager")
                .addFunction("LaunchEvent",&EventManager::LaunchEvent)
            .endClass()
            .deriveClass<EngineEventManager,EventManager>("EngineEventManager")
                .addStaticFunction("Instance",&EngineEventManager::Instance)
            .endClass()
            .beginClass<ComponentUserBase>("ComponentUsers")
                .addFunction("GetAll",&ComponentUserBase::GetAllUsersWithComponentsAsLuaList)
                .addFunction("GetAllEntities",&ComponentUserBase::GetAllEntitesWithComponentAsLuaList)
            .endClass()
            .beginClass<LuaRef>("LuaRef")
            .endClass()
            .beginClass<Controller>("Controller")
            .endClass()
            .beginClass<SideScrollerPlayerInterface>("SSPI")
                .addStaticFunction("Downcast",&SideScrollerPlayerInterface::Downcast)
                .addFunction("Jump",&SideScrollerPlayerInterface::Jump)
                .addFunction("Left",&SideScrollerPlayerInterface::Left)
                .addFunction("Right",&SideScrollerPlayerInterface::Right)
                .addFunction("Action",&SideScrollerPlayerInterface::Action)
            .endClass()
            .beginClass<Instance>("Instance")
                .addProperty("y", &Instance::GetY)
                .addProperty("x", &Instance::GetX)
                .addProperty("height",&Instance::GetHeight)
                .addProperty("width",&Instance::GetWidth)
            .endClass()
            .deriveClass<LuaInstance,Instance>("LuaInstance")
            .endClass()
            .beginClass<Stage>("Stage")
            .endClass()
            .deriveClass<LuaStage, Stage>("LuaStage")
            .endClass()
            .beginClass<Tile>("Tile")
            .endClass()
            .beginClass<DebugFlags>("DebugFlags")
                .addStaticFunction("Instance", &DebugFlags::Instance)
                .addFunction("Set", &DebugFlags::Set)
            .endClass()
            .beginClass<GameState>("GameState")
                .addFunction("Msg", &GameState::GetMessageDispatch)
                .addFunction("SystemController",&GameState::GetSystemController)
                .addFunction("EntityManager", &GameState::GetEntityManager)
                .addFunction("ComponentUsers",&GameState::GetComponentUserBase)
            .endClass()
            .beginClass<Engine>("Engine")
                .addFunction("ComponentUsers",&Engine::GetComponentUserBase)
                .addFunction("EventManager",&Engine::GetEngineEventManager)
            .endClass();
    } 
 };

 #endif