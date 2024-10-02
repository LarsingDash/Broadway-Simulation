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
        Engine/WindowModule.cpp
        Engine/WindowModule.h
        Engine/RenderingModule.cpp
        Engine/RenderingModule.h
        Engine/InputModule.cpp
        Engine/InputModule.h
        Engine/SimulationManager.cpp
        Engine/SimulationManager.h
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
)
