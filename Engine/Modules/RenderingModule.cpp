#include "RenderingModule.hpp"
#include "../SimulationManager.hpp"
#include <iostream>

glm::vec2 RenderingModule::tileSize;

RenderingModule::RenderingModule(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        return;
    }
}

RenderingModule::~RenderingModule() {
    SDL_DestroyRenderer(renderer);
}

void RenderingModule::init(Museum* mus, ArtistsManager* artM, PathfindingModule* path) {
    museum = mus;
    artistsManager = artM;
    pathfindingModule = path;
}

void RenderingModule::clear() {
    _darkGrey();
    SDL_RenderClear(renderer);
}

void RenderingModule::draw() {
    if (WindowModule::recalculateTileSize) recalculateTileSize();

    drawMuseum();
    if (isRenderingActive) drawArtists();
    if (pathfindingModule->getRenderPath()) drawPath();
    if (pathfindingModule->getRenderVisited()) drawVisitedTiles();
}

void RenderingModule::drawMuseum() {
    for (int y = 0; y < museum->getRows(); ++y) {
        for (int x = 0; x < museum->getCols(); ++x) {
            TileState& state = *museum->getTile(x, y).currentState;

            SDL_FRect tileRect = {
                    static_cast<float>(x) * tileSize.x,
                    static_cast<float>(y) * tileSize.y,
                    tileSize.x, tileSize.y
            };

            SDL_SetRenderDrawColor(renderer, state.config.first.r, state.config.first.g,
                                   state.config.first.b, state.config.first.a);
            SDL_RenderFillRectF(renderer, &tileRect);
        }
    }
}

void RenderingModule::drawArtists() {
    for (const auto& artist : artistsManager->getArtists()) {
        SDL_FRect artistRect = {
                artist->pos.x + Artist::offset.x,
                artist->pos.y + Artist::offset.y,
                Artist::size.x,
                Artist::size.y
        };

        artist->isColliding ? _red() : _darkGrey();
        SDL_RenderFillRectF(renderer, &artistRect);
    }
}

void RenderingModule::drawPath() {
    auto renderPathTile = [&](const auto& pos) {
        SDL_FRect tileRect = {
                (pos.x / static_cast<float>(museum->getCols())) * static_cast<float>(WindowModule::width) + Artist::offset.x,
                (pos.y / static_cast<float>(museum->getRows())) * static_cast<float>(WindowModule::height) + Artist::offset.y,
                Artist::size.x,
                Artist::size.y
        };
        SDL_RenderFillRectF(renderer, &tileRect);
    };

    // Start
    _white();
    if (pathfindingModule->start) renderPathTile(pathfindingModule->start->getPos());

    // Path (including Target)
    _darkGrey();
    for (const auto& tile : pathfindingModule->path) renderPathTile(tile->getPos());
    if (pathfindingModule->target) renderPathTile(pathfindingModule->target->getPos());
}

void RenderingModule::drawVisitedTiles() {
    for (const auto& tile : pathfindingModule->visited) {
        const glm::vec2& pos = tile->getPos();
        SDL_FRect tileRect = {
                (pos.x / static_cast<float>(museum->getCols())) * static_cast<float>(WindowModule::width),
                (pos.y / static_cast<float>(museum->getRows())) * static_cast<float>(WindowModule::height),
                tileSize.x,
                tileSize.y
        };

        _darkGrey();
        SDL_RenderDrawRectF(renderer, &tileRect);
    }
}

void RenderingModule::drawRectangle(const SDL_Rect& rect, bool isRed) {
    isRed ? _red() : _darkGrey();
    SDL_RenderDrawRect(renderer, &rect);
}

void RenderingModule::present() {
    SDL_RenderPresent(renderer);
}

void RenderingModule::toggleRendering() {
    isRenderingActive = !isRenderingActive;
}

void RenderingModule::recalculateTileSize() const {
    // Remove scaling
    for (const auto& artist : artistsManager->getArtists())
        artist->pos /= tileSize;

    // Recalculate scaling
    tileSize = glm::vec2{
            static_cast<float>(WindowModule::width) / static_cast<float>(museum->getCols()),
            static_cast<float>(WindowModule::height) / static_cast<float>(museum->getRows()),
    };
    WindowModule::recalculateTileSize = false;

    Artist::offset = tileSize / 4.f;
    Artist::size = tileSize / 2.f;

    // Reapply scaling
    for (const auto& artist : artistsManager->getArtists())
        artist->pos *= tileSize;
}

void RenderingModule::_red() { SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255); }
void RenderingModule::_white() { SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); }
void RenderingModule::_darkGrey() { SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); }


