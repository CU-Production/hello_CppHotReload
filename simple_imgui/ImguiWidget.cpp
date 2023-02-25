//
// Created by Admin on 2023/2/25.
//

#include "sokol/sokol_app.h"
#include "imgui/imgui.h"
#include "ImguiWidget.h"
#include "GlobalUserData.h"

#include <iostream>

sg_pass_action ImguiWidget::pass_action;

ImguiWidget::ImguiWidget()
{
    hscpp::GlobalUserData::GetAs<GlobalUserData>()->pObj = this;

    auto cb = [this](hscpp::SwapInfo& info) {
        info.Save("show_test_window", m_show_test_window);
        info.Save("show_another_window", m_show_another_window);
        info.Save("ImGuiContext", m_ImGuiContext);
    };

    Hscpp_SetSwapHandler(cb);
}

void ImguiWidget::Init()
{
//    m_ImGuiContext = ImGui::CreateContext();
    m_ImGuiContext = ImGui::GetCurrentContext();
}

void ImguiWidget::Frame()
{
    // When a module is recompiled, ImGui's static context will be empty. Setting it every frame
    // ensures that the context remains set.
    ImGui::SetCurrentContext(m_ImGuiContext);

    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    static float f = 0.0f;
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", &pass_action.colors[0].value.r);
    if (ImGui::Button("Test Window")) m_show_test_window ^= 1;
    if (ImGui::Button("Another Window")) m_show_another_window ^= 1;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("w: %d, h: %d, dpi_scale: %.1f", sapp_width(), sapp_height(), sapp_dpi_scale());
    if (ImGui::Button(sapp_is_fullscreen() ? "Switch to windowed" : "Switch to fullscreen")) {
        sapp_toggle_fullscreen();
    }

    // 2. Show another simple window, this time using an explicit Begin/End pair
    if (m_show_another_window) {
        ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiCond_FirstUseEver);
        ImGui::Begin("Another Window", &m_show_another_window);
        ImGui::Text("Hello");
        ImGui::End();
    }

    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowDemoWindow()
    if (m_show_test_window) {
        ImGui::SetNextWindowPos(ImVec2(460, 20), ImGuiCond_FirstUseEver);
        ImGui::ShowDemoWindow();
    }
}

