target_sources(${PROJECT_NAME} PRIVATE
        SimulationManager.cpp
)

add_subdirectory(FileReading)
add_subdirectory(Modules)
add_subdirectory(Tiles)