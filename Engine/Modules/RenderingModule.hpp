#ifndef RENDERING_MODULE_HPP
#define RENDERING_MODULE_HPP

#include "../Tiles/Museum.hpp"
#include "../Artists/ArtistsManager.hpp"

class RenderingModule {
	public:
		explicit RenderingModule(SDL_Window* window);
		~RenderingModule();
		void clear();
		void draw();
		void present();

		[[maybe_unused]] [[nodiscard]] SDL_Renderer* getRenderer() const { return renderer; }

	private:
		SDL_Renderer* renderer;
		Museum& museum;
		ArtistsManager& artistsManager;
};

#endif /* RENDERING_MODULE_HPP */
