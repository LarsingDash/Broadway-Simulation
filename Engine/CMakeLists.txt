target_sources(${PROJECT_NAME} PRIVATE
        SimulationManager.cpp
        SingletonRandom.cpp
)

add_subdirectory(Artists)
add_subdirectory(CommandHandling)
add_subdirectory(FileReading)
add_subdirectory(Modules)
add_subdirectory(Tiles)
