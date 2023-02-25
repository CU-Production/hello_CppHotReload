//
// Created by Admin on 2023/2/25.
//

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_log.h"
#include "sokol/sokol_glue.h"
#include "imgui/imgui.h"
#include "sokol/util/sokol_imgui.h"

#include "hscpp/Hotswapper.h"
#include "GlobalUserData.h"
#include "ImguiWidget.h"

static hscpp::Hotswapper* swapper;
static GlobalUserData* globalUserData;

//static sg_pass_action pass_action;

static bool show_test_window = true;
static bool show_another_window = false;

void init() {
    // setup sokol-gfx, sokol-time and sokol-imgui
    sg_desc desc = { };
    desc.context = sapp_sgcontext();
    desc.logger.func = slog_func;
    sg_setup(&desc);

    // use sokol-imgui with all default-options (we're not doing
    // multi-sampled rendering or using non-default pixel formats)
    simgui_desc_t simgui_desc = { };
    simgui_setup(&simgui_desc);

    // initial clear color
    ImguiWidget::pass_action.colors[0].action = SG_ACTION_CLEAR;
    ImguiWidget::pass_action.colors[0].value = { 0.0f, 0.5f, 0.7f, 1.0f };

    // Init hscpp
    swapper = new hscpp::Hotswapper();

    auto srcPath = HELLO_HSCPP_ROOT_PATH"/simple_imgui";
    auto includePath = HELLO_HSCPP_ROOT_PATH"/simple_imgui";
    auto imguiIncludePath = HELLO_HSCPP_ROOT_PATH"/simple_imgui/imgui";
    auto sokolIncludePath = HELLO_HSCPP_ROOT_PATH"/simple_imgui/sokol";
    auto sokolUtilIncludePath = HELLO_HSCPP_ROOT_PATH"/simple_imgui/sokol/util";

#ifdef _WIN32
    auto imguiLibraryName = "imgui.lib";
    auto sokolLibraryName = "sokol.lib";
#else
    auto imguiLibraryName = "imgui.a";
    auto sokolLibraryName = "sokol.a";
#endif

    swapper->AddSourceDirectory(srcPath);
    swapper->AddIncludeDirectory(includePath);
    swapper->AddIncludeDirectory(imguiIncludePath);
    swapper->AddIncludeDirectory(sokolIncludePath);
    swapper->AddIncludeDirectory(sokolUtilIncludePath);
    swapper->LocateAndAddLibrary(HELLO_HSCPP_BUILD_PATH, imguiLibraryName);
    swapper->LocateAndAddLibrary(HELLO_HSCPP_BUILD_PATH, sokolLibraryName);

    globalUserData = new GlobalUserData();
    swapper->SetGlobalUserData(globalUserData);

    globalUserData->pObj = swapper->GetAllocationResolver()->Allocate<ImguiWidget>();

    // Init ImguiWidget sokol_imgui
    const int width = sapp_width();
    const int height = sapp_height();
    simgui_new_frame({ width, height, sapp_frame_duration(), sapp_dpi_scale() });
    globalUserData->pObj->Init();
    sg_begin_default_pass(&ImguiWidget::pass_action, width, height);
    simgui_render();
    sg_end_pass();
    sg_commit();
}

void frame() {
    const int width = sapp_width();
    const int height = sapp_height();
    simgui_new_frame({ width, height, sapp_frame_duration(), sapp_dpi_scale() });

    // Swapper Update
    globalUserData->pObj->Frame();

    // the sokol_gfx draw pass
    sg_begin_default_pass(&ImguiWidget::pass_action, width, height);
    simgui_render();
    sg_end_pass();
    sg_commit();

    swapper->Update();
}

void cleanup() {
//    globalUserData->pObj->Cleanup();
    simgui_shutdown();
    sg_shutdown();

    // Swapper Cleanup
    delete swapper;
    delete globalUserData;
}

void input(const sapp_event* event) {
//    globalUserData->pObj->Input(event);
    simgui_handle_event(event);
}

int main() {
    sapp_desc desc = { };
    desc.init_cb = init;
    desc.frame_cb = frame;
    desc.cleanup_cb = cleanup;
    desc.event_cb = input;
    desc.window_title = "Dear ImGui (sokol-app)";
    desc.ios_keyboard_resizes_canvas = false;
    desc.icon.sokol_default = true;
    desc.enable_clipboard = true;
    desc.logger.func = slog_func;
    sapp_run(desc);
    return 0;
}
