#include "GUIModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"

GUIModule::GUIModule(SDL_Window* window, SDL_Renderer* renderer)
        : window(window), renderer(renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

GUIModule::~GUIModule() {
    shutdown();
}

void GUIModule::beginFrame() {
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui::NewFrame();
}

void GUIModule::render() {
    if (showFileSelectionWindow) {
        ImGui::SetNextWindowSize(ImVec2(400, 185), ImGuiCond_Once);
        ImGui::Begin("File Selection", nullptr, ImGuiWindowFlags_NoResize);

        ImGui::Text("Museum/Map");
        static int mapSourceType = 1;
        ImGui::RadioButton("Web Source", &mapSourceType, 0);
        ImGui::SameLine();
        ImGui::RadioButton("File Source", &mapSourceType, 1);

        static char mapInput[256] = "";
        if (mapSourceType == 0) {
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##MapInput", mapInput, IM_ARRAYSIZE(mapInput));
            ImGui::PopItemWidth();
        } else {
            ImGui::PushItemWidth(-110);
            ImGui::InputText("##MapInput", mapInput, IM_ARRAYSIZE(mapInput));
            ImGui::PopItemWidth();
            ImGui::SameLine();
            if (ImGui::Button("Open File##Map", ImVec2(100, 0))) {
                openFileDialog();
            }
        }

        ImGui::Separator();

        ImGui::Text("Artist");
        static int artistSourceType = 0;
        ImGui::RadioButton("Web Source##Artist", &artistSourceType, 0);
        ImGui::SameLine();
        ImGui::RadioButton("File Source##Artist", &artistSourceType, 1);

        static char artistInput[256] = "";
        if (artistSourceType == 0) {
            ImGui::PushItemWidth(-1);
            ImGui::InputText("##ArtistInput", artistInput, IM_ARRAYSIZE(artistInput));
            ImGui::PopItemWidth();
        } else {
            ImGui::PushItemWidth(-110);
            ImGui::InputText("##ArtistInput", artistInput, IM_ARRAYSIZE(artistInput));
            ImGui::PopItemWidth();
            ImGui::SameLine();
            if (ImGui::Button("Open File##Artist", ImVec2(100, 0))) {
                openFileDialog();
            }
        }

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5f);
        if (ImGui::Button("Confirm", ImVec2(100, 0))) {
            std::cout << "Selected input for map: " << mapInput << std::endl;
            std::cout << "Selected input for artist: " <<  artistInput << std::endl;

            if (mapSourceType == 0) {
                FileReaderTemplate::readFileTemplate(mapInput, SourceType::Web);
            } else {
                FileReaderTemplate::readFileTemplate(mapInput, SourceType::File);
            }

            if (artistSourceType == 0) {
                FileReaderTemplate::readFileTemplate(artistInput, SourceType::Web);
            } else {
                FileReaderTemplate::readFileTemplate(artistInput, SourceType::File);
            }


        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void GUIModule::shutdown() {
    if (renderer != nullptr) {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        renderer = nullptr;
    }
}

void GUIModule::toggleFileSelectionWindow() {
    showFileSelectionWindow = !showFileSelectionWindow;
}

void GUIModule::openFileDialog() {

}
