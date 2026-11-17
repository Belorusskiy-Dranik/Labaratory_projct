#include <iostream>
#include <fstream>
#include <string>

struct Zek
{
    char surname[22]{};
    size_t group = 0;
    size_t number = 0;
};

bool before(Zek const& zek_1, Zek const& zek_2)
{
    if (zek_1.group == zek_2.group)
    {
        return strcmp(zek_1.surname, zek_2.surname) > 0;
    }
    else return (zek_1.group > zek_2.group);
}

void kazarma_sort(const std::string& in_path)
{
    std::fstream finit(in_path, std::ios::out | std::ios::binary | std::ios::in);
    if (!finit) return;
    Zek zek_1, zek_2;
    finit.seekg(0, std::ios::end);
    size_t m_1 = finit.tellg();
    finit.seekg(0);
    size_t m_2 = finit.tellg();
    size_t size = (m_1 - m_2) / sizeof(Zek);
    finit.seekp(0);
    for (size_t i = 0; i + 1 < size; ++i)
    {
        finit.clear();
        finit.seekg(0, std::ios::beg);
        finit.seekp(0, std::ios::beg);
        for (size_t j = 0; j + 1 < size - i; ++j)
        {
            finit.seekg(j * ((int)sizeof(Zek)), std::ios::beg);
            finit.read((char*)&zek_1, sizeof(Zek));
            finit.read((char*)&zek_2, sizeof(Zek));


            if (before(zek_1, zek_2))
            {
                finit.seekp(j * ((int)sizeof(Zek)), std::ios::beg);
                finit.write((const char*)&zek_2, sizeof(Zek));
                finit.write((const char*)&zek_1, sizeof(Zek));
                finit.flush();
            }
        }
    }
    finit.close();
}

//"..\\bin_files\\marks.bin"
//"..\\bin_files\\student.bin"
//"..\\bin_files\\marks_with_surname.bin"
//"..\\bin_files\\kazarma.bin"