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
    uint8_t mark_3 = 0;//размер 48
};
void add_ave_bal(const std::string& inpath, const std::string& outpath) {
	std::ifstream ifile(inpath, std::ios::binary);
    std::ofstream ofile(outpath, std::ios::binary);
    Stud_Rec_Book a;
    while (ifile.read((char*)&a, sizeof(a))) {
        double ave_mark = ((double)a.mark_1 + (double)a.mark_2 + (double)a.mark_3) / 3;
        ofile.write((const char*)&a, sizeof(a));
        ofile.write((const char*)&ave_mark, sizeof(double));
    }   
}