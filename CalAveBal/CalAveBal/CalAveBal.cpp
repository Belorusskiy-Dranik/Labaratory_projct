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
struct Stud_Rec_Book_with_aver_marks
{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
    double average = 0;
};

void add_ave_bal(const std::string& inpath, const std::string& outpath) {
	std::ifstream ifile(inpath, std::ios::binary);
    std::ofstream ofile(outpath, std::ios::binary);
    if (!ifile || !ofile)
        throw "Cannot open files for average marks.";
    Stud_Rec_Book a;
    Stud_Rec_Book_with_aver_marks b;
    while (ifile.read((char*)&a, sizeof(a))) {
        double ave_mark = ((double)a.mark_1 + (double)a.mark_2 + (double)a.mark_3) / 3;
        b.group = a.group;
        for (size_t i = 0; i < sizeof(b.surname); ++i)
            b.surname[i] = a.surname[i];
        b.number = a.number;
        b.mark_1 = a.mark_1;
        b.mark_2 = a.mark_2;
        b.mark_3 = a.mark_3;
        b.average = ave_mark;
        ofile.write((const char*)&b, sizeof(b));
    }   
    ofile.close();
}
