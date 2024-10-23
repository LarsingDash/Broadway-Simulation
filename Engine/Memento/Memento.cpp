//
// Created by 11896 on 22/10/2024.
//

#include "Memento.hpp"

Memento::Memento(const std::vector<std::vector<TileState>>& tiles,
                 const std::vector<ArtistState>& artists)
        : tileStates(tiles), artistStates(artists) {}
