cmake_minimum_required(VERSION 3.24)
project(hello_CppHotReload)

set(CMAKE_CXX_STANDARD 17)

set(HSCPP_BUILD_EXAMPLES OFF)
set(HSCPP_BUILD_TESTS OFF)
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

