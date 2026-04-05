#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "\033[1;31mUsage: " << argv[0] << " <file path>\033[0m" << '\n';
        return 1;
    }
    std::string FilePath = argv[1];
    for (int i = 2; i < argc; ++i) {
        FilePath += " ";
        FilePath += argv[i];
    }

    const int HashSize = 32;
    const size_t ChunkSize = 4096; // 4kb

    int ArrayIndex = 0;
    uint8_t HashArray[HashSize] = {0};
    std::vector<char> BufferChunk(ChunkSize);
    std::ifstream File(FilePath, std::ios::in | std::ios::binary);
    while (File.read(BufferChunk.data(), ChunkSize) || File.gcount() > 0) {
        std::streamsize BytesRead = File.gcount();
        for (std::streamsize i = 0; i < BytesRead; i++) {
            uint8_t ByteValue = static_cast<uint8_t>(BufferChunk[i]);
            ArrayIndex = (ArrayIndex + ByteValue + i) % HashSize;
            HashArray[ArrayIndex] ^= (ByteValue * 31);
        }
    }
    File.close();
    for (uint8_t B : HashArray) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(B);
    }
    std::cout << '\n' << std::dec;
    return 0;
}
