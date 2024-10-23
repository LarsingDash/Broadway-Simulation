//
// Created by 11896 on 23/10/2024.
//

#include <string>
#ifdef _WIN32
#include <windows.h>
#include <shobjidl.h>
#endif

class FileDialogModule {
public:
    struct DialogResult {
        bool success;
        std::string filePath;
    };

    static FileDialogModule& getInstance() {
        static FileDialogModule instance;
        return instance;
    }

    DialogResult showDialog();

private:
    FileDialogModule() = default;
    ~FileDialogModule() = default;


    FileDialogModule(const FileDialogModule&) = delete;
    FileDialogModule& operator=(const FileDialogModule&) = delete;

#ifdef _WIN32
    std::string wstrToStr(const std::wstring& wstr);
#endif
};
