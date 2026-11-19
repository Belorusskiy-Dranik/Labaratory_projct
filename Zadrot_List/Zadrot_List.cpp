#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
struct Stud_Rec_Book
{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
};
struct Zek
{
    char surname[22]{};
    size_t group = 0;
    size_t number = 0;
};

void Zadrot_List(const std::string& inpath, const std::string& outpath) {
    std::ifstream ifile(inpath, std::ios::binary);
    std::ofstream ofile(outpath, std::ios::binary);
    if (!ifile || !ofile)
        throw "Cannot open files for student list.";
    Stud_Rec_Book begunok;
    Zek z;
    while (ifile.read((char*)&begunok, sizeof(begunok))) {
        if ((begunok.mark_1 > 7) && (begunok.mark_2 > 7) && (begunok.mark_3 > 7)) {
            for (size_t i = 0; i < sizeof(z.surname); ++i)
                z.surname[i] = begunok.surname[i];
            z.group = begunok.group;
            z.number = begunok.number;
            ofile.write((const char*)&z, sizeof(z));
        }
    }
    ofile.close();
}
