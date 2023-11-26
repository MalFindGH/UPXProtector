#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_name>" << std::endl;
        return 1;
    }
    std::ifstream inputFile(argv[1], std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    std::vector<char> fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    std::vector<char> searchPattern = { 'U', 'P', 'X' };
    auto upxPosition = std::search(fileContent.begin(), fileContent.end(), searchPattern.begin(), searchPattern.end());
    if (upxPosition != fileContent.end()) {
        std::fill(upxPosition, upxPosition + searchPattern.size(), 0x00);
    }
    else {
        std::cerr << "File is not packed with UPX." << std::endl;
        return 1;
    }
    std::ofstream outputFile(argv[1], std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error opening file for writing: " << argv[1] << std::endl;
        return 1;
    }
    outputFile.write(&fileContent[0], fileContent.size());
    outputFile.close();
    std::cout << "First occurrence of 'UPX' successfully replaced with '00 00 00' and file saved: " << argv[1] << std::endl;
    return 0;
}