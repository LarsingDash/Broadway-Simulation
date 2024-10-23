#ifndef BROADWAY_SIMULATION_GUIMODULE_HPP
#define BROADWAY_SIMULATION_GUIMODULE_HPP

#include "InputModule.hpp"
#include <SDL_render.h>
#include <array>
#include <string>
#ifdef _WIN32
#include <windows.h>
#include <shobjidl.h>
#endif

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

    char mapInput[256] = "..\\assets\\grid.txt";
    char artistInput[256] = "..\\assets\\artists.csv";
    std::string selectedFilePath;
    bool isSelectingMapFile = false;

    //<Command, <InputBuffer, ValidBool>>
    static std::unordered_map<InputModule::Commands, std::pair<std::array<char, 64>, bool>> keyInputs;

    void _renderFileSelector();
    void _renderInfo();
    void openFileDialog();

    // Helper function for Windows wide string conversion
#ifdef _WIN32
    std::string wstrToStr(const std::wstring& wstr);
#endif
};

#endif //BROADWAY_SIMULATION_GUIMODULE_HPP