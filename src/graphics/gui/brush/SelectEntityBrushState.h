#ifndef SELECTENITITYBRUSHSTATE_H
#define SELECTENITITYBRUSHSTATE_H

#include "src/game_objects/Entity.h"
#include "src/graphics/gui/brush/BrushState.h"
#include "src/graphics/gui/gui_tools/CurrentSelectionWindow.h"

class SelectEntityBrushState : public BrushState
{
  public:
    enum SelectionState
    {
        RELEASED,
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

    bool PaintWindow(PMIDGWindow &window) override
    {
        switch (_selection_state)
        {
        case RELEASED:
            return false;
        case MOVING:
            MoveEntity(window);
            return false;
        }

        
    }

    bool OnInstanceMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, Instance *instance, 
        ComponentUser* c = nullptr) override
    {
        if (c == _selected)
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
                _selection_state = MOVING;
                return true;
            }
            else if (e.type == sf::Event::MouseButtonReleased)
            {
                _selection_state = RELEASED;
                return true;
            }
        }
        _selection_state = RELEASED;
        return false;
    }

    bool OnKeyboardEvent(sf::Event &e, Instance *instance) override
    {
        if (_selected)
        {
            if (e.key.code == sf::Keyboard::Delete)
            {
                delete _selected;
                _selected = nullptr;
            }
        }
    }


    void DrawExtras() override
    {
        if(_selected)
            selection_window.Draw(_selected);
    }

  private:
    Entity *_selected = nullptr;
    SelectionState _selection_state;
    CurrentSelectionWindow selection_window;
};

#endif