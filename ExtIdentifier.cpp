#include "includes.h"

std::string solvePathFile(std::string path) {

    if (!std::filesystem::exists(path)) {
        std::cout << "\nCould not find file" << std::endl;
        return "";
    }

    size_t fSize = std::filesystem::file_size(path);
    if (fSize > 64) { fSize = 64; }

    char* fBuffer = new char[fSize];
    std::ifstream fStream(path, std::ios::in || std::ios::binary);
    fStream.read(fBuffer, fSize);
    fStream.close();

    for (size_t x = 0; x < fileEIVec.size(); x++) {
        for (size_t i = 0; i < fSize; i++) {
            if (memcmp(fileEIVec.at(x).id.c_str(), &fBuffer[i], fileEIVec.at(x).id.length()) == 0) {
                std::cout << "\nThe original file extension is " << fileEIVec.at(x).ext;
                std::filesystem::rename(path, path.substr(0, (path.find_last_of(".")+1)) + fileEIVec.at(x).ext);
                return fileEIVec.at(x).ext;
            }
        }
    }

    std::cout << "\nCould not detect extension";

    return "";
}

int main(int argc, char** argv) {

    // Patterns
    fileEIVec.push_back({ "mp4", "mp4" });
    fileEIVec.push_back({ "PNG", "png" });
    fileEIVec.push_back({ "ID3", "mp3" });
    fileEIVec.push_back({ "GIF", "gif" });
    fileEIVec.push_back({ "JFIF", "jpg" });
    fileEIVec.push_back({ "WEBP", "webp" });
    fileEIVec.push_back({ "\x50\x4B\x03", "zip" });
    fileEIVec.push_back({ "Rar", "rar" });
    fileEIVec.push_back({ "\xD0\xCF\x11\xE0", "msi" });
    fileEIVec.push_back({ "<svg", "svg" });

    if(argc >= 2) {
        for (int x = 1; x < argc; x++) {
            solvePathFile(argv[x]);
        }
    }
    else {
        std::cout << "Please drop a file: ";
        std::string fileDir = "";
        std::cin >> fileDir; 
        std::system("cls");
        solvePathFile(fileDir);
    }
    
    return EXIT_SUCCESS;
}