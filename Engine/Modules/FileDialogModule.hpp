//
// Created by 11896 on 23/10/2024.
//

#include <string>

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

		static DialogResult showDialog();

		FileDialogModule(const FileDialogModule&) = delete;
		FileDialogModule& operator=(const FileDialogModule&) = delete;
	private:
		FileDialogModule() = default;
		~FileDialogModule() = default;

		static std::string WStrToStr(const std::wstring& wstring);
};
