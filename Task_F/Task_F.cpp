#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
struct Zek
{
    char surname[22]{};
    size_t group = 0;
    size_t number = 0;
};

void kazarma_print(const std::string& path)
{
    std::ifstream fin(path, std::ios::binary);
    if (!fin)
        throw "Cannot open list for printing.";

    std::cout << std::left
        << std::setw(24) << "surname"
        << std::setw(8) << "group"
        << std::setw(10) << "number" << '\n';

    Zek z;
    size_t i = 0;
    while (fin.read((char*)&z, sizeof(Zek))) {
        std::cout << std::left
            << std::setw(24) << z.surname
            << std::setw(8) << z.group
            << std::setw(10) << z.number << '\n';
        ++i;
    }
}
