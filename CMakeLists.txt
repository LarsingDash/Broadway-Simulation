cmake_minimum_required(VERSION 3.28.1)
project(Broadway_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_MODULE_PATH}/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#GLM
include_directories("${CMAKE_MODULE_PATH}/glm")

add_executable(${PROJECT_NAME} main.cpp
        Engine/Modules/WindowModule.cpp
        Engine/Modules/WindowModule.hpp
        Engine/Modules/RenderingModule.cpp
        Engine/Modules/RenderingModule.hpp
        Engine/Modules/InputModule.cpp
        Engine/Modules/InputModule.hpp
        Engine/SimulationManager.cpp
        Engine/SimulationManager.hpp
        Engine/Tiles/TileState.hpp
        Engine/Tiles/Red.cpp
        Engine/Tiles/Red.hpp
        Engine/Tiles/Yellow.cpp
        Engine/Tiles/Yellow.hpp
        Engine/Tiles/Blue.cpp
        Engine/Tiles/Blue.hpp
        Engine/Tiles/Grey.cpp
        Engine/Tiles/Grey.hpp
        Engine/Tiles/White.cpp
        Engine/Tiles/White.hpp
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
)
