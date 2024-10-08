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

#Main
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
        Engine/Tiles/TileStates/Red.cpp
        Engine/Tiles/TileStates/Red.hpp
        Engine/Tiles/TileStates/Yellow.cpp
        Engine/Tiles/TileStates/Yellow.hpp
        Engine/Tiles/TileStates/Blue.cpp
        Engine/Tiles/TileStates/Blue.hpp
        Engine/Tiles/TileStates/Grey.cpp
        Engine/Tiles/TileStates/Grey.hpp
        Engine/Tiles/TileStates/White.cpp
        Engine/Tiles/TileStates/White.hpp
        Engine/Tiles/Tile.cpp
        Engine/Tiles/Tile.hpp
        Engine/Tiles/Museum.cpp
        Engine/Tiles/Museum.hpp
        Engine/FileReading/FileReaderTemplate.cpp
        Engine/FileReading/FileReaderTemplate.hpp
        Engine/FileReading/Source.hpp
        Engine/FileReading/SourceStrategy/ISourceStrategy.hpp
        Engine/FileReading/SourceStrategy/WebSourceStrategy.cpp
        Engine/FileReading/SourceStrategy/WebSourceStrategy.hpp
        Engine/FileReading/SourceStrategy/FileSourceStrategy.cpp
        Engine/FileReading/SourceStrategy/FileSourceStrategy.hpp
        Engine/FileReading/TileStrategy/TileStrategy.hpp
        Engine/FileReading/ArtistStrategy/IArtistStrategy.hpp
        Engine/FileReading/MapStrategy/IMapStrategy.hpp
        Engine/FileReading/MapStrategy/XmlMapStrategy.cpp
        Engine/FileReading/MapStrategy/XmlMapStrategy.hpp
        Engine/FileReading/MapStrategy/TxtMapStrategy.cpp
        Engine/FileReading/MapStrategy/TxtMapStrategy.hpp
        Engine/FileReading/ArtistStrategy/CsvArtistStrategy.cpp
        Engine/FileReading/ArtistStrategy/CsvArtistStrategy.hpp
        Engine/Tiles/MuseumBuilder.cpp
        Engine/Tiles/MuseumBuilder.hpp
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
        
        "${CURL_PATH}libcurl.dll.a"
)
