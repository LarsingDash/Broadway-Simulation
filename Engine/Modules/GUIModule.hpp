//
// Created by 11896 on 16/10/2024.
//

#ifndef BROADWAY_SIMULATION_GUIMODULE_HPP
#define BROADWAY_SIMULATION_GUIMODULE_HPP

#include <SDL_render.h>

class GUIModule {
	public:
		GUIModule(SDL_Window* window, SDL_Renderer* renderer);
		~GUIModule();

		static void beginFrame();
		void render();
		void shutdown();
		void toggleFileSelectionWindow();

		[[nodiscard]] bool getFileSelectionFocussed() const;
		[[nodiscard]] bool isWindowOpen() const;;

	private:
		SDL_Renderer* renderer;
		bool showFileSelectionWindow = false;
		bool fileSelectionWindowFocussed = false;

		void _renderFileSelector();
		void openFileDialog();
};


#endif //BROADWAY_SIMULATION_GUIMODULE_HPP
