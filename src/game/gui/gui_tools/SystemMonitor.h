#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include "imgui.h"
#include "src/system/SystemFactory.h"
#include "src/system/SystemController.h"

class SystemMonitor
{
  public:
    void Draw(const char *title, bool *opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, opened);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();

        std::unordered_map<std::string, System*> available_systems = SystemFactory::Instance()->GetAllSystems();
        std::list<System*>& active_systems = SystemController::Instance()->GetSystemInExecutionSequence();
        std::list<System*>& passive_systems = SystemController::Instance()->GetPassiveSystems();

        for(auto it = active_systems.begin(); it != active_systems.end(); it++)
        {
            available_systems.erase((*it)->GetName());
        }

        for(auto it = passive_systems.begin(); it != passive_systems.end(); it++)
        {
            available_systems.erase((*it)->GetName());
        }

        std::vector<std::string> available_systems_vect;

        for(auto it = available_systems.begin(); it != available_systems.end(); it++)
        {
            available_systems_vect.push_back(it->second->GetName());
        }

        ImGui::BeginChild("Available Systems", ImVec2(500,200));
        DrawSystemList(active_systems, "Active");
        DrawSystemList(passive_systems, "Passive");
        ImGui::EndChild();

        ImGui::BeginChild("Available Systems", ImVec2(500,0));
        DrawAvailableSystems(available_systems_vect);
        ImGui::EndChild();

        if(ImGui::Button("Enable"))
        {
            if(selected_system != -1)
            {
                SystemController::Instance()->AddToSystemExecutionSequence(available_systems_vect[selected_system]);
            }
        }

        ImGui::End();
    }

    void DrawAvailableSystems(std::vector<std::string>& systems)
    {
         ImGui::ListBoxVector("", &selected_system, systems);
    }

    void DrawSystemList(std::list<System*>& list, std::string type)
    {
        int i = 0;
        for(auto it = list.begin(); it != list.end(); it++)
        {
          ImGui::Text("%i",i); 
          ImGui::SameLine(30); 
          std::string name = (*it)->GetName();
          ImGui::Text(name.c_str());
          ImGui::SameLine(200);
          ImGui::Text(type.c_str());
          ImGui::SameLine(300);
          ImGui::Text("%.4f", (*it)->GetLastRuntime());
          ImGui::SameLine(380);
          ImGui::Text("ms");
          ImGui::SameLine(400);
          std::string button_name_up = "+##"+name;
          std::string button_name_down = "-##"+name;
          if(ImGui::SmallButton(button_name_up.c_str()))
          {
            SystemController::Instance()->MoveUp(name);
          }

          ImGui::SameLine(420);
          
          if(ImGui::SmallButton(button_name_down.c_str()))
          {
            SystemController::Instance()->MoveDown(name);
          }
          i++;
        }
    }

    bool IsFocused()
    {
        return _focused;
    }

private:
    bool _focused = false;
    int selected_system = -1;
};
#endif