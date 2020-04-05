#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <bitset>
#include <iostream>

enum
{
    A, // 0000 0000
    C, // 0000 0001
    T, // 0000 0010
    G  // 0000 0011
};

std::unordered_map<unsigned char, unsigned char> enumChar
{
    {A, 'A'},
    {C, 'C'},
    {T, 'T'},
    {G, 'G'}
};



int main(int argc, char* argv[])
{
    if (argc < 2)
        return !printf("Not enough arguments\nUsage: %s <filename>\n", __FILE__);
    
    std::string fileName = argv[1];
    std::ifstream f = std::ifstream(fileName, std::ios::binary);

    const size_t fileSize = std::filesystem::file_size(fileName);
    //const size_t newFileSize = fileSize * 4; 

    char* fbuf = (char*)malloc(fileSize);

    f.read(fbuf, fileSize);

    /* note: use std::bitset if else fails */

    for (uint i = 0; i <= fileSize; i++)
    {
        unsigned char current = *(unsigned char*)(fbuf + i);
        for (int u = 0; u <= 3; u++)
        {
            printf("%c", enumChar[( (current & (0b11 << (u * 2))) >> (u * 2))]);
        };
    }

    return 0;
}