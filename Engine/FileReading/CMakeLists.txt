target_sources(${PROJECT_NAME} PRIVATE
        FileReaderTemplate.cpp
)

add_subdirectory(ArtistStrategy)
add_subdirectory(MapStrategy)
add_subdirectory(SourceStrategy)
