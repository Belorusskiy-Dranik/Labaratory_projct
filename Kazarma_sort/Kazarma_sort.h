#pragma once

#include <algorithm>
#include <fstream>
#include <string>

void kazarma_sort(const std::string& in_path);

template<class T>
void kazarma_sort(const std::string& in_path, const std::string& out_path,
    bool (*before)(const T&, const T&))
{
    std::ifstream fin(in_path, std::ios::binary);
    if (!fin)
        throw "Cannot open list for standard sorting.";

    fin.seekg(0, std::ios::end);
    std::streamoff file_size = fin.tellg();
    if (file_size < 0 || file_size % sizeof(T) != 0)
        throw "Incomplete student list record.";
    size_t size = (size_t)(file_size / sizeof(T));
    fin.seekg(0);

    T* records = new T[size];
    for (size_t i = 0; i < size; ++i)
        fin.read((char*)&records[i], sizeof(T));
    if (!fin)
    {
        delete[] records;
        throw "Cannot read list for standard sorting.";
    }
    fin.close();

    std::sort(records, records + size, before);

    std::ofstream fout(out_path, std::ios::binary);
    if (!fout)
    {
        delete[] records;
        throw "Cannot create standard sorted list.";
    }
    for (size_t i = 0; i < size; ++i)
        fout.write((const char*)&records[i], sizeof(T));
    delete[] records;

    fout.close();
    if (!fout)
        throw "Cannot write standard sorted list.";
}
