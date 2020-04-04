#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <array>

enum
{
    A, // 0000 0000
    C, // 0000 0001
    T, // 0000 0010
    G  // 0000 0011
};

std::unordered_map<unsigned char, unsigned char> charEnum
{
    {'A', A},
    {'C', C},
    {'T', T}, 
    {'G', G}
}

inline unsigned char pos(unsigned char v, unsigned char p)
{
    return v << (p * 2);
};

// i % 4

 int main(int argc, char* argv[])
 {
     if (argc < 2)
        return !printf("Not enough arguments. Usage: %s <filepath>\n", __FILE__ + SOURCE_PATH_SIZE);

    std::string fileName = argv[1];
    const size_t fileSize = std::filesystem::file_size(fileName);

    const size_t newFileSize = fileSize % 4 ? fileSize / 4 + 1 : fileSize / 4;

    std::ifstream f = std::ifstream(fileName, std::ios::binary);

    char* fbuf = malloc(fileSize);
    if (!fbuf)
        return !printf("Failed to allocate %i bytes, block size not yet supported\n", fileSize);
    
    std::vector<unsigned char> datav;
    data.reserve(newFileSize);
    
    unsigned char current = 0b00000000;

    for (uint i = 0; i <= fileSize; i++)
    {
        auto r = pos(fbuf[i], i % 4);

        if (i != 0 && !(i % 4))
        {
            datav.push_back(r);
            current ^= current;
        };

        current | r;
    };

    data.push_back(0);

    unsigned char* data = datav.data();

    printf("%.*s", newFileSize, data); // to /dev/stdout which can be piped into file

    return 0;
 }