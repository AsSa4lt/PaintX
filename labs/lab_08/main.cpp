#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

namespace fs = std::filesystem;

void searchInFile(const std::string& filePath, const std::string& query) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(query) != std::string::npos) {
            std::cout << "[" << filePath << "] " << line << std::endl;
        }
    }
}

void searchInDirectory(const fs::path& dirPath, const std::string& query) {
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry) && !fs::is_symlink(entry)) {
            searchInFile(entry.path().string(), query);
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv , argv + argc);
    if (args.size() != 3) {
        std::cerr << "Usage: " << args[0] << " <query> <directory>" << std::endl;
        return 1;
    }

    std::string query = args[1];
    fs::path dirPath = args[2];

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        std::cerr << "Provided path is not a directory or does not exist." << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    searchInDirectory(dirPath, query);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << duration << " milliseconds" << std::endl;

    return 0;
}
