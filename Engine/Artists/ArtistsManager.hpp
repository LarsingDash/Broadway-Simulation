//
// Created by larsv on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_ARTISTSMANAGER_HPP
#define BROADWAY_SIMULATION_ARTISTSMANAGER_HPP

#include "Artist.hpp"
#include "../Tiles/Museum.hpp"
#include <vector>
#include <memory>

class ArtistsManager {
public:
    void render(SDL_Renderer *renderer) const;

    void update(Museum &museum, float delta);

    void clearArtists();

    void addArtist(glm::ivec2 tile, glm::vec2 dir);

    std::vector<std::unique_ptr<Artist>> &getArtists() {
        return artists;
    }

    void toggleRendering();

private:
    bool isRenderingActive = true;
    std::vector<std::unique_ptr<Artist>> artists;
};


#endif //BROADWAY_SIMULATION_ARTISTSMANAGER_HPP
