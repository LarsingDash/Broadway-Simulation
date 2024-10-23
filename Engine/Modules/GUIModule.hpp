//
// Created by 11896 on 16/10/2024.
//

#ifndef BROADWAY_SIMULATION_GUIMODULE_HPP
#define BROADWAY_SIMULATION_GUIMODULE_HPP

#include "InputModule.hpp"
#include <SDL_render.h>
#include <array>

class GUIModule {
	public:
		GUIModule(SDL_Window* window, SDL_Renderer* renderer, InputModule& inputModule);
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

		static bool isTyping;
	private:
		SDL_Renderer* renderer;
		InputModule& inputModule;
		
		bool showFileSelectionWindow = false;
		bool showInfoWindow = false;
		bool fileSelectionWindowFocussed = false;
		bool infoWindowFocussed = false;
		
		//<Command, <InputBuffer, ValidBool>>
		static std::unordered_map<InputModule::Commands, std::pair<std::array<char, 64>, bool>> keyInputs;

		void _renderFileSelector();
		void _renderInfo();
		void openFileDialog();
};


#endif //BROADWAY_SIMULATION_GUIMODULE_HPP
