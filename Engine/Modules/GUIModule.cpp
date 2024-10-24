#include "GUIModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"
#include "FileDialogModule.hpp"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <array>
#include <cstring>
#include <sstream>

std::unordered_map<InputModule::Commands, std::pair<std::array<char, 64>, bool>> GUIModule::keyInputs;
bool GUIModule::isTyping = false;

GUIModule::GUIModule(SDL_Window* window, SDL_Renderer* renderer, InputModule& module) :
		renderer(renderer), inputModule{module} {
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
	else infoWindowFocussed = false;

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

void GUIModule::enableInfoWindow() {
	showInfoWindow = true;

	//Init keyInputs
	for (const auto& [command, key]: inputModule.keys) {
		std::string keyName = SDL_GetScancodeName(key.first);
		for (char& c: keyName) c = static_cast<char>(toupper(c));

		auto keyArray = std::array<char, 64>{};

		strncpy(keyArray.data(), keyName.c_str(), keyArray.size() - 1);
		GUIModule::keyInputs[command] = {keyArray, true};
	}
}

void GUIModule::closeWindows() {
	showFileSelectionWindow = false;
	showInfoWindow = false;
}

bool GUIModule::getFileSelectionFocussed() const { return fileSelectionWindowFocussed; }

bool GUIModule::getInfoFocussed() const { return infoWindowFocussed; }

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
			openFileDialog(mapInput, sizeof(mapInput));
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
			openFileDialog(artistInput, sizeof(artistInput));
		}
	}

	//Confirm Lambda
	auto onConfirmClick = [&mapSourceType = mapSourceType, &artistSourceType = artistSourceType,
			&mapInput = mapInput, &artistInput = artistInput]() {
		if (std::strlen(mapInput) > 0) {
			if (mapSourceType == 0) {
				FileReaderTemplate::readFileTemplate(mapInput, SourceType::Web);
			} else {
				FileReaderTemplate::readFileTemplate(mapInput, SourceType::File);
			}
		}

		if (std::strlen(artistInput) > 0) {
			if (artistSourceType == 0) {
				FileReaderTemplate::readFileTemplate(artistInput, SourceType::Web);
			} else {
				FileReaderTemplate::readFileTemplate(artistInput, SourceType::File);
			}
		}
	};

	//Confirm Button
	bool canConfirm = (std::strlen(mapInput) > 0) || (std::strlen(artistInput) > 0);

	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5f);
	ImGui::BeginDisabled(!canConfirm);
	if (ImGui::Button("Confirm", ImVec2(100, 0))) {
		onConfirmClick();
	}
	ImGui::EndDisabled();

	//Enter shortcut for the confirm button
	if (fileSelectionWindowFocussed && ImGui::IsKeyPressed(ImGuiKey_Enter) && canConfirm)
		onConfirmClick();

	//End
	ImGui::End();
}


void GUIModule::_renderInfo() {
	//Begin
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
	ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoResize);
	infoWindowFocussed = ImGui::IsWindowFocused();

	//Header
	ImGui::Text("Command / Key");
	ImGui::Separator();

	bool isTypingAnywhere = false;
	for (const auto& [command, key]: inputModule.keys) {
		//Command
		ImGui::Text(key.second.c_str());
		ImGui::SameLine();

		//Get buffer
		std::pair<std::array<char, 64>, bool> config = GUIModule::keyInputs[command];
		std::array<char, 64>& buffer = config.first;

		//Prefix label with ## to hide it visually
		std::stringstream stringStream;
		stringStream << "##";
		stringStream << key.second;

		//InputText
		//	Fill remaining width and color red if invalid
		ImGui::PushItemWidth(-1);
		if (!config.second) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(225, 25, 25, 255));

		//	InputText
		ImGui::InputText(stringStream.str().c_str(), buffer.data(), buffer.size(),
						 ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CharsUppercase |
						 ImGuiInputTextFlags_AutoSelectAll, [](ImGuiInputTextCallbackData* data) {
					//Retrieve command from InputText user_data
					auto curCommand = *static_cast<InputModule::Commands*>(data->UserData);

					SDL_Scancode scancode = SDL_GetScancodeFromName(data->Buf);

					//Update key
					if (scancode != SDL_SCANCODE_UNKNOWN) {
						SimulationManager::getInstance().inputModule->keys[curCommand].first = scancode;
						GUIModule::keyInputs[curCommand].second = true;
					} else GUIModule::keyInputs[curCommand].second = false;    //Mark InputText red

					//Store new text to buffer for next render
					strncpy(GUIModule::keyInputs[curCommand].first.data(), data->Buf, data->BufSize - 1);


					return 1;
				}, (void*) &command);
		if (ImGui::IsItemActive()) isTypingAnywhere = true;

		//Pop
		if (!config.second)ImGui::PopStyleColor();
		ImGui::PopItemWidth();
	}

	GUIModule::isTyping = isTypingAnywhere;

	//End
	ImGui::End();
}


void GUIModule::openFileDialog(char* inputBuffer, const size_t& bufferSize) {
	FileDialogModule::DialogResult result = FileDialogModule::getInstance().showDialog();

	//Check if result was successful
	if (result.success) {
		std::cout << "File selected: " << result.filePath << std::endl;

		//Copy chosen file path to buffer
		std::strncpy(inputBuffer, result.filePath.c_str(), bufferSize - 1);
		inputBuffer[bufferSize - 1] = '\0'; //Null-termination
	} else {
		std::cerr << "File selection was cancelled or failed." << std::endl;
	}
}
