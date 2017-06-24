#include "EntityManager.h"
#include "src/game_objects/Entity.h"

Entity *EntityManager::GetEntityByID(int id)
{
    auto it = _entity_map.find(id);

    if (it == _entity_map.end())
    {
        //TODO: Throw exception
    }

    return _entity_map.at(id);
}

void EntityManager::RegisterEntity(Entity *entity)
{
    _entity_map.insert(std::make_pair(entity->_id, entity));
}

EntityManager* EntityManager::Instance()
{
    static EntityManager instance;
    return &instance;
}

std::map<int, Entity *> EntityManager::GetAllEntities()
{
    return _entity_map;
}

int EntityManager::GetNumberOfEntities()
{
    return _entity_map.size();
}

LuaList<Entity*>* EntityManager::AsLuaList()
{
    return LuaList<Entity*>::FromMapToLuaList<int, Entity*>(_entity_map);
}

void EntityManager::Clear()
{
    _entity_map.clear();
}

EntityManager::~EntityManager()
{
    /*for(auto it = _entity_map.begin(); it != _entity_map.end(); it++)
        {
            delete it->second;
        }*/
}