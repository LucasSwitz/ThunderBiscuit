#ifndef SELECTENITITYBRUSHSTATE_H
#define SELECTENITITYBRUSHSTATE_H

#include "src/game_objects/Entity.h"
#include "src/game/gui/brush/BrushState.h"

class SelectEntityBrushState : public BrushState
{
  public:
    enum SelectionState
    {
        SELECTED,
        MOVING
    };

    SelectEntityBrushState(Entity *selected) : _selected(selected)
    {

    }

    void MoveEntity(PMIDGWindow &window)
    {
        if (_selected)
        {
            sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(window.SFWindow());
            sf::Vector2f world_mouse_position = window.SFWindow().mapPixelToCoords(screen_mouse_position);

            _selected->SetComponentValueFloat("Position", "x", world_mouse_position.x);
            _selected->SetComponentValueFloat("Position", "y", world_mouse_position.y);
        }
    }

    void PaintWindow(PMIDGWindow &window) override
    {

        switch (_selection_state)
        {
        case SELECTED:
            break;

        case MOVING:
            MoveEntity(window);
        break;
        }
    }

    bool OnInstanceMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, Instance *instance) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            _selection_state = MOVING;
            return true;
        }
        else if(e.type == sf::Event::MouseButtonReleased)
        {
            _selection_state = SELECTED;
            return true;
        }
    }

  private:
    Entity *_selected = nullptr;
    SelectionState _selection_state;
};

#endif