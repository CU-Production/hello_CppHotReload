cmake_minimum_required(VERSION 3.24)
project(hello_CppHotReload)

set(CMAKE_CXX_STANDARD 17)

option(HSCPP_BUILD_EXAMPLES OFF)
option(HSCPP_BUILD_TESTS OFF)
add_subdirectory(3rdparty/hscpp)

add_executable(simple_hotsawp
        simple_hotsawp/main.cpp
        simple_hotsawp/GlobalUserData.h
        simple_hotsawp/HotSwapObject.h
        simple_hotsawp/HotSwapObject.cpp)
target_include_directories(simple_hotsawp PRIVATE 3rdparty/hscpp/include)
target_link_libraries(simple_hotsawp hscpp)
target_compile_definitions(simple_hotsawp PRIVATE
        HELLO_HSCPP_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_library(imgui STATIC
        simple_imgui/imgui/imgui.cpp
        simple_imgui/imgui/imgui_demo.cpp
        simple_imgui/imgui/imgui_draw.cpp
        simple_imgui/imgui/imgui_tables.cpp
        simple_imgui/imgui/imgui_widgets.cpp)

add_library(sokol STATIC
        simple_imgui/sokol.cpp
        simple_imgui/sokol/sokol_gfx.h
        simple_imgui/sokol/sokol_app.h
        simple_imgui/sokol/sokol_glue.h
        simple_imgui/sokol/sokol_log.h
        simple_imgui/sokol/util/sokol_imgui.h)
target_link_libraries(sokol PUBLIC imgui)

add_executable(simple_imgui_sokol
        simple_imgui/ImguiWidget.h
        simple_imgui/ImguiWidget.cpp
        simple_imgui/GlobalUserData.h
        simple_imgui/main.cpp)
target_include_directories(simple_imgui_sokol PRIVATE 3rdparty/hscpp/include)
target_link_libraries(simple_imgui_sokol hscpp sokol imgui)
target_compile_definitions(simple_imgui_sokol PRIVATE
        HELLO_HSCPP_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
        HELLO_HSCPP_BUILD_PATH="${CMAKE_BINARY_DIR}")
