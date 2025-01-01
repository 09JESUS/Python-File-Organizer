#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void organize_files(const std::string& source_dir, const std::string& target_dir, const std::string& file_extension) {
    try {
        // Check if target directory exists, if not create it
        if (!fs::exists(target_dir)) {
            fs::create_directory(target_dir);
        }

        for (const auto& entry : fs::directory_iterator(source_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == file_extension) {
                fs::path target_path = target_dir / entry.path().filename();
                fs::rename(entry.path(), target_path);
                std::cout << "Moved: " << entry.path() << " to " << target_path << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::string source_dir = "path/to/source_directory";
    std::string target_dir = "path/to/target_directory";
    std::string file_extension = ".txt"; // Change to the file extension you want to organize

    organize_files(source_dir, target_dir, file_extension);

    return 0;
}
