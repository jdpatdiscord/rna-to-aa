#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>
#include <array>
#include <map>

enum { A, C, U, G };

enum
{
    Ala,
    Arg,
    Asn,
    Asp,
    Cys,
    Gln,
    Glu,
    Gly,
    His,
    Ile,
    Leu,
    Lys,
    Met,
    Phe,
    Pro,
    Ser,
    Thr,
    Trp,
    Tyr,
    Val,
    STP
};

std::array<std::string, 21> AAS {
    "Ala",
    "Arg",
    "Asn",
    "Asp",
    "Cys",
    "Gln",
    "Glu",
    "Gly",
    "His",
    "Ile",
    "Leu",
    "Lys",
    "Met",
    "Phe",
    "Pro",
    "Ser",
    "Thr",
    "Trp",
    "Tyr",
    "Val",
    "STP"
};

std::unordered_map<unsigned char, int> LtoBP
{
    {'a', A},
    {'c', C},
    {'t', U}, {'u', U},
    {'g', G}
};

const char* AAL = "ARNDCQEGHILKMFPSTWYV|";

struct Codon
{
    union
    {
        struct
        {
            unsigned char A;
            unsigned char B;
            unsigned char C;
        };
        unsigned int Value : 24;
    };

    Codon(unsigned char A, unsigned char B, unsigned char C) :
        A(A), B(B), C(C) { }
    Codon() : A(0), B(0), C(0) { }

    bool operator==(const Codon& c) const 
    {
        return c.Value == Value;
    }
    bool operator<(const Codon& c) const 
    {
        return Value < c.Value;
    }

    ~Codon() { }
};

std::map<Codon, uint> Tripair
{
    {Codon(U, U, U), Phe},    {Codon(U, C, U), Ser},    {Codon(U, A, U), Tyr},    {Codon(U, G, U), Cys},
    {Codon(U, U, C), Phe},    {Codon(U, C, C), Ser},    {Codon(U, A, C), Tyr},    {Codon(U, G, C), Cys},
    {Codon(U, U, A), Leu},    {Codon(U, C, A), Ser},    {Codon(U, A, A), STP},    {Codon(U, G, A), STP},
    {Codon(U, U, G), Leu},    {Codon(U, C, G), Ser},    {Codon(U, A, G), STP},    {Codon(U, G, G), Trp},

    {Codon(C, U, U), Leu},    {Codon(C, C, U), Pro},    {Codon(C, A, U), His},    {Codon(C, G, U), Arg},
    {Codon(C, U, C), Leu},    {Codon(C, C, C), Pro},    {Codon(C, A, C), His},    {Codon(C, G, C), Arg},
    {Codon(C, U, A), Leu},    {Codon(C, C, A), Pro},    {Codon(C, A, A), Gln},    {Codon(C, G, A), Arg},
    {Codon(C, U, G), Leu},    {Codon(C, C, G), Pro},    {Codon(C, A, G), Gln},    {Codon(C, G, G), Arg},

    {Codon(A, U, U), Ile},    {Codon(A, C, U), Thr},    {Codon(A, A, U), Asn},    {Codon(A, G, U), Ser},
    {Codon(A, U, C), Ile},    {Codon(A, C, C), Thr},    {Codon(A, A, C), Asn},    {Codon(A, G, C), Ser},
    {Codon(A, U, A), Ile},    {Codon(A, C, A), Thr},    {Codon(A, A, A), Lys},    {Codon(A, G, A), Arg},
    {Codon(A, U, G), Met},    {Codon(A, C, G), Thr},    {Codon(A, A, G), Lys},    {Codon(A, G, G), Arg},

    {Codon(G, U, U), Val},    {Codon(G, C, U), Ala},    {Codon(G, A, U), Asp},    {Codon(G, G, U), Gly},
    {Codon(G, U, C), Val},    {Codon(G, C, C), Ala},    {Codon(G, A, C), Asp},    {Codon(G, G, C), Gly},
    {Codon(G, U, A), Val},    {Codon(G, C, A), Ala},    {Codon(G, A, A), Glu},    {Codon(G, G, A), Gly},
    {Codon(G, U, G), Val},    {Codon(G, C, G), Ala},    {Codon(G, A, G), Glu},    {Codon(G, G, G), Gly},
};

int main(int argc, char* argv[])
{
    if (argc < 2)
        return 0;
    
    std::string fileName = argv[1];
    size_t fileSize = std::filesystem::file_size(fileName);

    fileSize = fileSize % 3 ? fileSize - (fileSize % 3) : fileSize;
    
    std::ifstream f = std::ifstream(fileName, std::ios::in);

    char* buf = (char*)malloc(fileSize + 1);

    f.read(buf, fileSize);

    uint loc = 1;

    std::string translation = "";

    while (loc < fileSize)
    {
        Codon c = Codon(
            LtoBP[*(unsigned char*)(buf + loc + 0)],
            LtoBP[*(unsigned char*)(buf + loc + 1)],
            LtoBP[*(unsigned char*)(buf + loc + 2)]
        );

        loc += 3;
        translation += AAL[Tripair[c]];
    };

    printf("%s\n", translation.c_str());

    f.close();

    free(buf);

    return 0;
}