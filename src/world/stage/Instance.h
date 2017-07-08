#ifndef INSTANCE_H
#define INSTANCE_H

#include "src/event/EventSubscriber.h"
#include "src/world/tile/TileMap.h"
#include "src/game_objects/Entity.h"
#include "src/event/Event.h"

/*Manages a specific game level, Can load and unload systems from the SystemController*/

class Instance : public EventSubscriber
{

 public:
    Instance(int id) : _id(id){}

    virtual void Load()
    {
        //load all local entites, do a cutscene, whatevs
        _tile_map.LoadFromFile(_tile_map_name);
        _loaded = true;
    }

    virtual void Unload()
    {
        //delete all local entities
        _tile_map.Unload();
        _loaded = false;
    }

    virtual void Open()
    {
        _tile_map.Show();

        for(Entity* e: _local_entities)
        {
            e->EnableComponent("Graphics");
        }
        _open = true;   
    }

    virtual void Update(float seconds_elapsed)
    {
        
    }

    virtual void Close()
    {
        _tile_map.Hide();

        //should have different options for what components to remove at different levels of closing.
        for(Entity* e : _local_entities)
        {
            e->DisableComponent("Graphics");
        }        
        _open = false;
    }

    virtual void OnEvent(Event& e)
    {
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
    }

    std::list<Subscription> GetSubscriptions()
    {

    }

    void SetTileMap(std::string file_name)
    {
        _tile_map.LoadFromFile(file_name);
    }

    int GetID()
    {
        return _id;
    }

    bool IsOpen()
    {
        return _open;
    }

    bool IsLoaded()
    {
        return _loaded;
    }


    protected:
        std::string name;
        std::string _tile_map_name;
        int _id;
    private:
        TileMap _tile_map;
        std::list<Entity*> _local_entities;
        bool _loaded;
        bool _open;
        
};


#endif