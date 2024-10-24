#include "FileDialogModule.hpp"
#include <shobjidl.h>

FileDialogModule::DialogResult FileDialogModule::showDialog() {
	DialogResult finalResult = {false, ""};

	//Initialize the COM library
	HRESULT dialogResult = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(dialogResult)) return finalResult;

	//Create FileOpenDialog instance
	IFileOpenDialog* fileDialog;
	dialogResult = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
									IID_IFileOpenDialog, reinterpret_cast<void**>(&fileDialog));

	//Check if Dialog window was successfully instantiated
	if (SUCCEEDED(dialogResult)) {
		//Set dialog options
		FILEOPENDIALOGOPTIONS options;
		fileDialog->GetOptions(&options);
		fileDialog->SetOptions(options | FOS_FORCEFILESYSTEM);	//Enforce return value is a file system item

		//Show dialog window
		dialogResult = fileDialog->Show(nullptr);

		//Check if Dialog window was successfully shown
		if (SUCCEEDED(dialogResult)) {
			//Get the result of the Dialog
			IShellItem* shellItem;
			dialogResult = fileDialog->GetResult(&shellItem);
			
			//Check if the result was successful
			if (SUCCEEDED(dialogResult)) {
				//Get filePath from the completed dialog
				PWSTR filePath;
				dialogResult = shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

				//Store filePath in final result
				if (SUCCEEDED(dialogResult)) {
					finalResult.success = true;
					finalResult.filePath = WStrToStr(filePath);
					CoTaskMemFree(filePath);
				}
				shellItem->Release();
			}
		}
		fileDialog->Release();
	}
	CoUninitialize();

	return finalResult;
}

std::string FileDialogModule::WStrToStr(const std::wstring& wstring) {
	if (wstring.empty()) return {};
	int size = WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int) wstring.size(), nullptr, 0, nullptr, nullptr);
	std::string result(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int) wstring.size(), &result[0], size, nullptr, nullptr);
	return result;
}
