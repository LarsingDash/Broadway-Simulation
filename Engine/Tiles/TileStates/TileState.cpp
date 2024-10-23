//
// Created by larsv on 09/10/2024.
//

#include "TileState.hpp"
#include "../Museum.hpp"

TileState::TileState(const char& c) : letter{c}, config{Museum::colors[c]}, interactionCount{0} {}
