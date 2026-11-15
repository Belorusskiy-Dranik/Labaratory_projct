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
void Kazarma_Check(const std::string& inpath, const std::string& outpath) {
    std::ifstream ifile(inpath, std::ios::binary);
    std::ofstream ofile(outpath, std::ios::binary);
    Stud_Rec_Book begunok;
    while (ifile.read((char*)&begunok, sizeof(begunok))) {
        if (begunok.mark_1 < 4 || begunok.mark_2 < 4 || begunok.mark_3 < 4) {
            ofile.write((const char*)&begunok.surname, sizeof(begunok.surname));
            ofile.write((const char*)&begunok.group, sizeof(begunok.group));
            ofile.write((const char*)&begunok.number, sizeof(begunok.number));
        }
    }
}
