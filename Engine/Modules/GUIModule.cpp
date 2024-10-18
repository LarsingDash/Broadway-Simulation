#include "GUIModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

GUIModule::GUIModule(SDL_Window* window, SDL_Renderer* renderer) : renderer(renderer) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void) io;
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
	if (showFileSelectionWindow) _renderFileSelector();
	else fileSelectionWindowFocussed = false;

	if (showInfoWindow) _renderInfo();

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

void GUIModule::enableFileSelectionWindow() { showFileSelectionWindow = true; }

void GUIModule::enableInfoWindow() { showInfoWindow = true; }

void GUIModule::closeWindows() {
	showFileSelectionWindow = false;
	showInfoWindow = false;
}

bool GUIModule::getFileSelectionFocussed() const { return fileSelectionWindowFocussed; }

bool GUIModule::isWindowOpen() const { return showFileSelectionWindow || showInfoWindow; }

void GUIModule::_renderFileSelector() {
	//Begin
	ImGui::SetNextWindowSize(ImVec2(400, 185), ImGuiCond_Once);
	ImGui::Begin("File Selection", nullptr, ImGuiWindowFlags_NoResize);
	fileSelectionWindowFocussed = ImGui::IsWindowFocused();

	//Museum Header
	ImGui::Text("Museum/Map");
	static int mapSourceType = 1;

	//Museum RadioButton
	ImGui::RadioButton("Web Source", &mapSourceType, 0);
	ImGui::SameLine();
	ImGui::RadioButton("File Source", &mapSourceType, 1);

	//Museum InputField
	static char mapInput[256] = "..\\assets\\grid.txt";
	if (mapSourceType == 0) {    //Web
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##MapInput", mapInput, IM_ARRAYSIZE(mapInput));
		ImGui::PopItemWidth();
	} else {    //File
		ImGui::PushItemWidth(-110);
		ImGui::InputText("##MapInput", mapInput, IM_ARRAYSIZE(mapInput));
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Open File##Map", ImVec2(100, 0))) {
			openFileDialog();
		}
	}

	ImGui::Separator();

	//Artist Header
	ImGui::Text("Artist");
	static int artistSourceType = 1;

	//Artist RadioButton
	ImGui::RadioButton("Web Source##Artist", &artistSourceType, 0);
	ImGui::SameLine();
	ImGui::RadioButton("File Source##Artist", &artistSourceType, 1);

	//Artist InputField
	static char artistInput[256] = "..\\assets\\artists.csv";
	if (artistSourceType == 0) {    //Web
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##ArtistInput", artistInput, IM_ARRAYSIZE(artistInput));
		ImGui::PopItemWidth();
	} else {    //File
		ImGui::PushItemWidth(-110);
		ImGui::InputText("##ArtistInput", artistInput, IM_ARRAYSIZE(artistInput));
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Open File##Artist", ImVec2(100, 0))) {
			openFileDialog();
		}
	}

	//Confirm Lambda
	auto onConfirmClick = [&mapSourceType = mapSourceType, &artistSourceType = artistSourceType,
			&mapInput = mapInput, &artistInput = artistInput]() {
		std::cout << "Selected input for map: " << mapInput << std::endl;
		std::cout << "Selected input for artist: " << artistInput << std::endl;

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
	};

	//Confirm Button
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5f);
	if (ImGui::Button("Confirm", ImVec2(100, 0))) onConfirmClick();

	//Enter check (also calls Confirm Lambda)
	if (fileSelectionWindowFocussed && ImGui::IsKeyPressed(ImGuiKey_Enter))onConfirmClick();

	//End
	ImGui::End();
}

void GUIModule::_renderInfo() {}

void GUIModule::openFileDialog() {

}
