#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <vector>

enum
{
    A, // 0000 0000
    C, // 0000 0001
    T, // 0000 0010
    G  // 0000 0011
};

std::unordered_map<unsigned char, unsigned char> charEnum
{
    {'A', A}, {'a', A},
    {'C', C}, {'c', C},
    {'T', T}, {'t', T},
    {'G', G}, {'g', G} 
};

inline unsigned char pos(unsigned char v, unsigned char p)
{
    return v << (p * 2);
}

// i % 4

 int main(int argc, char* argv[])
 {
     if (argc < 2)
        return !printf("Not enough arguments. Usage: %s <filepath>\n", __FILE__);

    std::string fileName = argv[1];
    const size_t fileSize = std::filesystem::file_size(fileName);

    const size_t newFileSize = fileSize % 4 ? fileSize / 4 + 1 : fileSize / 4;
    
    //printf("filesize: %zu\nnew filesize: %zu\n", fileSize, newFileSize);

    std::ifstream f = std::ifstream(fileName, std::ios::binary);

    char* fbuf = (char*)malloc(fileSize);
    if (!fbuf)
        return !printf("Failed to allocate %zu bytes, block size not yet supported\n", fileSize);
    
    f.read(fbuf, fileSize);
    f.close();

    std::vector<unsigned char> datav;
    datav.reserve(newFileSize);
    
    unsigned char current = 0b00000000;

    for (uint i = 0; i <= fileSize; i++)
    {
        unsigned char r = pos(charEnum[fbuf[i]], i % 4);

        if (i != 0 && !(i % 4))
        {
            printf("%c", current);
            current = 0;
        };

        current |= r;
    };

    free(fbuf);

    return 0;
 }