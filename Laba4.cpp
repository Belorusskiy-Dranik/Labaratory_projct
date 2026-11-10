#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <cstdio>
#include <exception>
struct Student
{
    char name[20];
    int marks[3];
};
void cbbot(const std::string& path) {
    std::ifstream ifile(path);
    if (!ifile)
        throw "Файл не открылся или не существует";
    if (ifile.peek() == EOF)
        throw "Файл пустой";
    std::ofstream ofile("bin.bin", std::ios::binary);
    if (!ofile)
        throw "Файл для вывода не открылся";
    std::string del;
    std::getline(ifile, del);
    std::string s;
    while (std::getline(ifile, s)) {
        Student p{};
        size_t nw = s.find_first_not_of(del, 0);
        for(int i = 0; i < 4; ++i) {
            size_t ew = s.find_first_of(del, nw);
            std::string word = s.substr(nw, ew - nw);
            nw = s.find_first_not_of(del, ew);
            if (i == 0) {
                std::snprintf(p.name, sizeof(p.name), "%s", word.c_str());
            }
                
            else
                p.marks[i - 1] = std::stoi(word);
        }
        ofile.write(reinterpret_cast<const char*>(&p), sizeof(p));
    }
    ofile.close();
    if (!ofile)
        throw "Не удалось записать бинарный файл";
}
void swapStudent(const std::string& path, size_t pos1, size_t pos2) {
    Student a{}, b{};
    std::fstream f(path, std::ios::in | std::ios::out | std::ios::binary);
    const size_t size = sizeof(Student);
    f.seekg(pos1 * size);
    f.read(reinterpret_cast<char*>(&a), size);
    f.seekg(pos2 * size);
    f.read(reinterpret_cast<char*>(&b), size);
    f.seekp(pos1 * size);
    f.write(reinterpret_cast<const char*>(&b), size);
    f.seekp(pos2 * size);
    f.write(reinterpret_cast<const char*>(&a), size);
    f.close();
}
int main()
{
    setlocale(LC_ALL, "Rus");
    std::string path = "in.txt";
    size_t pos1 = 1; size_t pos2 = 3;
    try {
        cbbot(path);
        swapStudent("bin.bin", pos1, pos2);
        std::cout << "bin.bin swap(" << pos1 << ", " << pos2 << ") OK";
    }
    catch (const char* e) {
        std::cout << e;
        return 1;
    }
    return 0;
}
