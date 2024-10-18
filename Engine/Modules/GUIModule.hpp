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
		void enableFileSelectionWindow();
		void enableInfoWindow();
		void closeWindows();

		[[nodiscard]] bool getFileSelectionFocussed() const;
		[[nodiscard]] bool getInfoFocussed() const;
		[[nodiscard]] bool isWindowOpen() const;

	private:
		SDL_Renderer* renderer;
		bool showFileSelectionWindow = false;
		bool showInfoWindow = false;
		bool fileSelectionWindowFocussed = false;
		bool infoWindowFocussed = false;

		void _renderFileSelector();
		void _renderInfo();
		void openFileDialog();
};


#endif //BROADWAY_SIMULATION_GUIMODULE_HPP
