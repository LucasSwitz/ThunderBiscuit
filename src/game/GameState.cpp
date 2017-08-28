#include "src/game/GameState.h"

GameState::GameState()
{
    _message_dispatch.RegisterSubscriber(&_system_controller);
    _system_controller.AssignToDispatch(&_message_dispatch);
}

GameState::GameState(const GameState &game_state) : _message_dispatch(),
                                                    _system_controller(game_state._system_controller),
                                                    _current_stage(game_state._current_stage)
{
    _message_dispatch.RegisterSubscriber(&_system_controller);
    _system_controller.AssignToDispatch(&_message_dispatch);
    //all the things need to add themselves to the component user base
}

void GameState::Load()
{
}

void GameState::Setup()
{

}

void GameState::Tick(float seconds_elapsed)
{

    if (_current_stage && _current_stage->GetCurrentInstance())
    {
        _system_controller.Update(seconds_elapsed, this);
        _current_stage->Tick(seconds_elapsed);
    }
    //if using lua
    LuaUniversal::Instance()->CollectGarbage();
}

void GameState::Unload()
{
}

void GameState::SetStage(Stage *stage)
{
    _current_stage = stage;
    _current_stage->AssignToDispatch(&_message_dispatch);
    _current_stage->GetComponentUserBaseMutable().AddSubscriber(&_player_base, "Player");
    _current_stage->Load();
    _current_stage->Enter();
}

void GameState::ChangeState(Stage *new_stage)
{
    if (_current_stage)
    {
        _current_stage->Exit();
        _current_stage->Unload();
    }

    SetStage(new_stage);
}

void GameState::AddSystem(std::string system_name)
{
    _system_controller.AddToSystemExecutionSequence(system_name);
}

void GameState::AddSystem(System *system)
{
    _system_controller.AddToSystemExecutionSequence(system);
}

void GameState::AddEntity(Entity *e)
{
    if (e->GetInstance() != -1)
    {
        Instance *i = _current_stage->GetInstance(e->GetInstance());
        _current_stage->AddEntity(e);
        i->AddLocalEntity(e->ID());
    }
    else
    {
        std::cout << "Entity has no instance...can't add" << std::endl;
    }
}

Stage *GameState::GetStage()
{
    return _current_stage;
}

EntityManager* GameState::GetEntityManager()
{
    if(_current_stage)
        return &_current_stage->GetEntityManager();
    return nullptr;
}

ComponentUserBase* GameState::GetComponentUserBase()
{
    if(_current_stage)
        return &_current_stage->GetComponentUserBaseMutable();
    return nullptr;
}

SystemController& GameState::GetSystemController()
{
    return _system_controller;
}

MessageDispatch &GameState::GetMessageDispatch()
{
    return _message_dispatch;
}

 PlayerBase& GameState::GetPlayerBase()
 {
     return _player_base;
 }