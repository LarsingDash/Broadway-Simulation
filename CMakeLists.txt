cmake_minimum_required(VERSION 3.28.1)
project(Broadway_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_MODULE_PATH}/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#GLM
include_directories("${CMAKE_MODULE_PATH}/glm")

#CURL
set(CURL_PATH "${CMAKE_MODULE_PATH}/curl/lib/")
include_directories("${CMAKE_MODULE_PATH}/curl/include")

# ImGui
set(IMGUI_PATH "${CMAKE_MODULE_PATH}/imgui")
include_directories("${IMGUI_PATH}")

#Main
add_executable(${PROJECT_NAME} main.cpp
        Engine/CommandHandling/Command.hpp)

add_subdirectory(Engine)


set(IMGUI_SOURCES
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp
        ${IMGUI_PATH}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_PATH}/backends/imgui_impl_sdlrenderer2.cpp
)
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCES})


target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
        
        "${CURL_PATH}libcurl.dll.a"
)
