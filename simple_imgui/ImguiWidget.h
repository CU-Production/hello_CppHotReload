//
// Created by Admin on 2023/2/25.
//

#pragma once

#include "sokol/sokol_gfx.h"
#include "hscpp/module/Tracker.h"
//#include "Common.h"
#include "imgui/imgui.h"

class ImguiWidget
{
    HSCPP_TRACK(ImguiWidget, "ImguiWidget");

public:
    hscpp_virtual ~ImguiWidget() = default;
    ImguiWidget();
    hscpp_virtual void Init();
    hscpp_virtual void Frame();

    static sg_pass_action pass_action;

private:
//    sg_pass_action pass_action;
    bool m_show_test_window = true;
    bool m_show_another_window = false;
    ImGuiContext* m_ImGuiContext;
};


