#ifndef MAINMENU_H
#define MAINMENU_H

#include "imgui.h"
#include "src/graphics/gui/gui_tools/FolderContents.h"
#include "src/graphics/gui/gui_tools/SaveDialog.h"
#include "src/graphics/gui/gui_tools/MainMenuListener.h"

class MainMenu
{
  public:
    void Draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            _focused = ImGui::IsRootWindowOrAnyChildHovered();

            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Instance"))
            {
                if (ImGui::MenuItem("New Instance", "CTRL+I"))
                {
                    if (_listener)
                    {
                        _listener->NewInstancePressed();
                    }
                }

                if (ImGui::BeginMenu("Load Instance", "CTRL+SHIFT+I"))
                {
                    _focused = true;
                    FolderContents instance_files("/home/pabu/Desktop/LifeSim/build/instances");
                    ImGui::BeginChild("Instance Selection##Menu", ImVec2(300, 200), true, ImGuiWindowFlags_NoScrollbar);
                    std::string file_name = instance_files.Draw();
                    if (!file_name.empty())
                    {
                        if (_listener)
                        {
                            _listener->LoadInstancePressed(file_name);
                        }
                    }

                    ImGui::EndChild();
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Save Instance", "CTRL+SHIFT+I"))
                {
                    ImGui::BeginChild("Select Instance");

                    ImGui::EndChild();
                }
                if (ImGui::BeginMenu("Save As Instance....", "CTRL+SHIFT+I"))
                {
                    ImGui::BeginChild("Save Instance##Menu", ImVec2(250, 50), true, ImGuiWindowFlags_NoScrollbar);
                    std::string file_name = _save_dialog.Draw();

                    if (!file_name.empty())
                    {
                        if (_listener)
                        {
                            _listener->SaveInstancePressed(file_name);
                        }
                    }

                    ImGui::EndChild();
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Stage"))
            {
                if (ImGui::MenuItem("New Stage", "CTRL+S"))
                {
                    if(_listener)
                    {
                        _listener->NewStagePressed();
                    }
                }
                if (ImGui::MenuItem("Load Stage", "CTRL+SHIFT+S"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("World"))
            {
                if (ImGui::MenuItem("New World", "CTRL+W"))
                {
                }
                if (ImGui::MenuItem("Load World", "CTRL+SHIFT+W"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Entity"))
            {
                if (ImGui::MenuItem("New Entity", "ImGui::EndCTRL+E"))
                {
                }
                if (ImGui::MenuItem("Load Entity", "CTRL+SHIFT+E"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    bool IsFocused()
    {
        return _focused || _save_dialog.IsFocused();
    }

    void SetListener(MainMenuListener *listener)
    {
        _listener = listener;
    }

  private:
    MainMenuListener *_listener;
    SaveDialog _save_dialog;
    bool _focused = false;
};
#endif