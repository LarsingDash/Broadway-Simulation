#ifndef RENDERING_MODULE_HPP
#define RENDERING_MODULE_HPP

#include "../Tiles/Museum.hpp"
#include "../Artists/ArtistsManager.hpp"
#include "Alga/PathfindingModule.hpp"

class RenderingModule {
	public:
		explicit RenderingModule(SDL_Window* window);
		~RenderingModule();
		void init(Museum* mus, ArtistsManager* artM, PathfindingModule* path);
		void clear();
		void draw();
		[[maybe_unused]]void drawRectangle(const SDL_Rect& rect, bool isRed);
		[[maybe_unused]]void drawRectangleF(const SDL_FRect& rect, bool isRed);
		void present();
		[[nodiscard]] SDL_Renderer* getRenderer() const { return renderer; }

		void toggleRendering();
		void recalculateTileSize() const;
		static glm::vec2 tileSize;
	private:
		bool isRenderingActive = true;
		
		void _red();
		void _white();
		void _darkGrey();
		
		SDL_Renderer* renderer;
		Museum* museum{nullptr};
		ArtistsManager* artistsManager{nullptr};
		PathfindingModule* pathfindingModule{nullptr};

		void drawMuseum();
		void drawArtists();
		void drawPath();
		void drawVisitedTiles();
};

#endif /* RENDERING_MODULE_HPP */
