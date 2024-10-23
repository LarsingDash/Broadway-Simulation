#include <vector>
#include "FileDialogModule.hpp"

FileDialogModule::DialogResult FileDialogModule::showDialog(const std::vector<std::pair<std::wstring, std::wstring>>& filters) {
    DialogResult result = {false, ""};

#ifdef _WIN32
    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr))
        return result;

    // Create FileOpenDialog instance
    IFileOpenDialog* pFileDialog;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                          IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileDialog));

    if (SUCCEEDED(hr)) {
        // Set options
        FILEOPENDIALOGOPTIONS options;
        pFileDialog->GetOptions(&options);
        pFileDialog->SetOptions(options | FOS_FORCEFILESYSTEM);

        // Prepare filter specs
        std::vector<COMDLG_FILTERSPEC> fileTypes(filters.size());
        for (size_t i = 0; i < filters.size(); ++i) {
            fileTypes[i] = { filters[i].first.c_str(), filters[i].second.c_str() };
        }

        // Set file types
        pFileDialog->SetFileTypes(static_cast<UINT>(fileTypes.size()), fileTypes.data());

        // Show the dialog
        hr = pFileDialog->Show(NULL);

        if (SUCCEEDED(hr)) {
            // Get the selected file
            IShellItem* pItem;
            hr = pFileDialog->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                PWSTR filePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

                if (SUCCEEDED(hr)) {
                    result.success = true;
                    result.filePath = wstrToStr(filePath);
                    CoTaskMemFree(filePath);
                }
                pItem->Release();
            }
        }
        pFileDialog->Release();
    }
    CoUninitialize();
#endif

    return result;
}

#ifdef _WIN32
std::string FileDialogModule::wstrToStr(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &result[0], size, nullptr, nullptr);
    return result;
}
#endif
