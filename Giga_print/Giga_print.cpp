#include "../Kazarma_sort/Kazarma_sort.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

struct Stud_Rec_Book
{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
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

struct Zek
{
    char surname[22]{};
    size_t group = 0;
    size_t number = 0;
};

static bool before(Zek const& zek_1, Zek const& zek_2)
{
    if (zek_1.group == zek_2.group)
    {
        return strcmp(zek_1.surname, zek_2.surname) < 0;
    }
    else return (zek_1.group < zek_2.group);
}

static bool before(Stud_Rec_Book const& zek_1, Stud_Rec_Book const& zek_2)
{
    if (zek_1.group == zek_2.group)
    {
        return strcmp(zek_1.surname, zek_2.surname) < 0;
    }
    else return (zek_1.group < zek_2.group);
}

static bool before(Stud_Rec_Book_with_aver_marks const& zek_1, Stud_Rec_Book_with_aver_marks const& zek_2)
{
    if (zek_1.group == zek_2.group)
    {
        return strcmp(zek_1.surname, zek_2.surname) < 0;
    }
    else return (zek_1.group < zek_2.group);
}
template <class T>
static void kazarma_sort(const std::string& in_path)
{
    std::fstream finit(in_path, std::ios::out | std::ios::binary | std::ios::in);
    if (!finit) throw "Cannot open file for sorting.";
    T zek_1, zek_2;
    finit.seekg(0, std::ios::end);
    size_t m_1 = finit.tellg();
    finit.seekg(0);
    size_t m_2 = finit.tellg();
    if ((m_1 - m_2) % sizeof(T) != 0)
        throw "Incomplete record in export file.";
    size_t size = (m_1 - m_2) / sizeof(T);
    finit.seekp(0);
    for (size_t i = 0; i + 1 < size; ++i)
    {
        finit.clear();
        finit.seekg(0, std::ios::beg);
        finit.seekp(0, std::ios::beg);
        for (size_t j = 0; j + 1 < size - i; ++j)
        {
            finit.seekg(j * ((int)sizeof(T)), std::ios::beg);
            finit.read((char*)&zek_1, sizeof(T));
            finit.read((char*)&zek_2, sizeof(T));


            if (before(zek_2, zek_1))
            {
                finit.seekp(j * ((int)sizeof(T)), std::ios::beg);
                finit.write((const char*)&zek_2, sizeof(T));
                finit.write((const char*)&zek_1, sizeof(T));
                finit.flush();
            }
        }
    }
    finit.close();
    if (!finit)
        throw "Cannot write sorted records.";
}

void giga_print(const std::string& marks_with_surname_bin_path,
    const std::string& aver_marks_bin_path, const std::string& sorted_SRB_by_alp_bin_path,
    const std::string& sorted_SRB_by_aver_marks_bin_path, const std::string& zadrot_list_bin_path,
    const std::string& kazarma_bin_path,
    const std::string& marks_with_surname_txt_path, 
    const std::string& aver_marks_txt_path, const std::string& sorted_SRB_by_alp_txt_path,
    const std::string& sorted_SRB_by_aver_marks_txt_path, const std::string& zadrot_list_txt_path,
    const std::string& kazarma_txt_path)
{

    for (int method = 0; method < 2; ++method)
    {
        if (method == 0)
            std::cout << "\nStandard sorting\n";
        else
            std::cout << "\nOwn sorting\n";

        Stud_Rec_Book SRB;
        Stud_Rec_Book_with_aver_marks SRB_wam;
        Zek zek;
        std::string bin_path_1 = marks_with_surname_bin_path;
        std::string txt_path_1 = marks_with_surname_txt_path;
        if (method == 0)
        {
            bin_path_1.insert(bin_path_1.find_last_of('.'), "_std");
            txt_path_1.insert(txt_path_1.find_last_of('.'), "_std");
            kazarma_sort<Stud_Rec_Book>(marks_with_surname_bin_path, bin_path_1, before);
        }
        else
            kazarma_sort<Stud_Rec_Book>(marks_with_surname_bin_path);
        std::ifstream finit_1(bin_path_1, std::ios::binary);
        std::ofstream fonit_1(txt_path_1);
        if (!finit_1 || !fonit_1)
            throw "Cannot open export files.";

        std::cout << "Marks_with_surname:\n";
        while (finit_1.read((char*)&SRB, sizeof(SRB)))
        {
            std::cout << std::left
                << std::setw(2) << SRB.group
                << std::setw(23) << SRB.surname
                << std::setw(7) << SRB.number
                << std::setw(3) << (int)SRB.mark_1
                << std::setw(3) << (int)SRB.mark_2
                << std::setw(3) << (int)SRB.mark_3 << '\n';
            fonit_1 << std::left
                << std::setw(2) << SRB.group
                << std::setw(23) << SRB.surname
                << std::setw(7) << SRB.number
                << std::setw(3) << (int)SRB.mark_1
                << std::setw(3) << (int)SRB.mark_2
                << std::setw(3) << (int)SRB.mark_3 << '\n';
        }
        std::cout << '\n';
        std::string bin_path_2 = aver_marks_bin_path;
        std::string txt_path_2 = aver_marks_txt_path;
        if (method == 0)
        {
            bin_path_2.insert(bin_path_2.find_last_of('.'), "_std");
            txt_path_2.insert(txt_path_2.find_last_of('.'), "_std");
            kazarma_sort<Stud_Rec_Book_with_aver_marks>(aver_marks_bin_path, bin_path_2, before);
        }
        else
            kazarma_sort<Stud_Rec_Book_with_aver_marks>(aver_marks_bin_path);
        std::ifstream finit_2(bin_path_2, std::ios::binary);
        std::ofstream fonit_2(txt_path_2);
        if (!finit_2 || !fonit_2)
            throw "Cannot open export files.";

        std::cout << "Student_Record_Book_with_average_marks:\n";
        while (finit_2.read((char*)&SRB_wam, sizeof(SRB_wam)))
        {
            std::cout << std::left
                << std::setw(2) << SRB_wam.group
                << std::setw(23) << SRB_wam.surname
                << std::setw(7) << SRB_wam.number
                << std::setw(3) << (int)SRB_wam.mark_1
                << std::setw(3) << (int)SRB_wam.mark_2
                << std::setw(3) << (int)SRB_wam.mark_3
                << std::setw(12) << std::setprecision(5) << SRB_wam.average << '\n';
            fonit_2 << std::left
                << std::setw(2) << SRB_wam.group
                << std::setw(23) << SRB_wam.surname
                << std::setw(7) << SRB_wam.number
                << std::setw(3) << (int)SRB_wam.mark_1
                << std::setw(3) << (int)SRB_wam.mark_2
                << std::setw(3) << (int)SRB_wam.mark_3
                << std::setw(12) << std::setprecision(5) << SRB_wam.average << '\n';
        }
        std::cout << '\n';

        std::string bin_path_3 = sorted_SRB_by_alp_bin_path;
        std::string txt_path_3 = sorted_SRB_by_alp_txt_path;
        if (method == 0)
        {
            bin_path_3.insert(bin_path_3.find_last_of('.'), "_std");
            txt_path_3.insert(txt_path_3.find_last_of('.'), "_std");
            kazarma_sort<Stud_Rec_Book>(sorted_SRB_by_alp_bin_path, bin_path_3, before);
        }
        else
            kazarma_sort<Stud_Rec_Book>(sorted_SRB_by_alp_bin_path);
        std::ifstream finit_3(bin_path_3, std::ios::binary);
        std::ofstream fonit_3(txt_path_3);
        if (!finit_3 || !fonit_3)
            throw "Cannot open export files.";

        std::cout << "Student_Record_Book_sorted_by_alphabet:\n";
        while (finit_3.read((char*)&SRB, sizeof(SRB)))
        {
            std::cout << std::left
                << std::setw(2) << SRB.group
                << std::setw(23) << SRB.surname
                << std::setw(7) << SRB.number
                << std::setw(3) << (int)SRB.mark_1
                << std::setw(3) << (int)SRB.mark_2
                << std::setw(3) << (int)SRB.mark_3 << '\n';
            fonit_3 << std::left
                << std::setw(2) << SRB.group
                << std::setw(23) << SRB.surname
                << std::setw(7) << SRB.number
                << std::setw(3) << (int)SRB.mark_1
                << std::setw(3) << (int)SRB.mark_2
                << std::setw(3) << (int)SRB.mark_3 << '\n';
        }
        std::cout << '\n';

        std::string bin_path_4 = sorted_SRB_by_aver_marks_bin_path;
        std::string txt_path_4 = sorted_SRB_by_aver_marks_txt_path;
        if (method == 0)
        {
            bin_path_4.insert(bin_path_4.find_last_of('.'), "_std");
            txt_path_4.insert(txt_path_4.find_last_of('.'), "_std");
            kazarma_sort<Stud_Rec_Book_with_aver_marks>(sorted_SRB_by_aver_marks_bin_path, bin_path_4, before);
        }
        else
            kazarma_sort<Stud_Rec_Book_with_aver_marks>(sorted_SRB_by_aver_marks_bin_path);
        std::ifstream finit_4(bin_path_4, std::ios::binary);
        std::ofstream fonit_4(txt_path_4);
        if (!finit_4 || !fonit_4)
            throw "Cannot open export files.";

        std::cout << "Student_Record_Book_sorted_by_average_marks:\n";
        while (finit_4.read((char*)&SRB_wam, sizeof(SRB_wam)))
        {
            std::cout << std::left
                << std::setw(2) << SRB_wam.group
                << std::setw(23) << SRB_wam.surname
                << std::setw(7) << SRB_wam.number
                << std::setw(3) << (int)SRB_wam.mark_1
                << std::setw(3) << (int)SRB_wam.mark_2
                << std::setw(3) << (int)SRB_wam.mark_3
                << std::setw(12) << std::setprecision(5) << SRB_wam.average << '\n';
            fonit_4 << std::left
                << std::setw(2) << SRB_wam.group
                << std::setw(23) << SRB_wam.surname
                << std::setw(7) << SRB_wam.number
                << std::setw(3) << (int)SRB_wam.mark_1
                << std::setw(3) << (int)SRB_wam.mark_2
                << std::setw(3) << (int)SRB_wam.mark_3
                << std::setw(12) << std::setprecision(5) << SRB_wam.average << '\n';
        }
        std::cout << '\n';

        std::string bin_path_5 = kazarma_bin_path;
        std::string txt_path_5 = kazarma_txt_path;
        if (method == 0)
        {
            bin_path_5.insert(bin_path_5.find_last_of('.'), "_std");
            txt_path_5.insert(txt_path_5.find_last_of('.'), "_std");
            kazarma_sort<Zek>(kazarma_bin_path, bin_path_5, before);
        }
        else
            kazarma_sort<Zek>(kazarma_bin_path);
        std::ifstream finit_5(bin_path_5, std::ios::binary);
        std::ofstream fonit_5(txt_path_5);
        if (!finit_5 || !fonit_5)
            throw "Cannot open export files.";

        std::cout << "Na_Kazarme:\n";
        while (finit_5.read((char*)&zek, sizeof(zek)))
        {
            std::cout << std::left
                << std::setw(23) << zek.surname
                << std::setw(2) << zek.group
                << std::setw(7) << zek.number << '\n';
            fonit_5 << std::left
                << std::setw(23) << zek.surname
                << std::setw(2) << zek.group
                << std::setw(7) << zek.number << '\n';
        }
        std::cout << '\n';

        std::string bin_path_6 = zadrot_list_bin_path;
        std::string txt_path_6 = zadrot_list_txt_path;
        if (method == 0)
        {
            bin_path_6.insert(bin_path_6.find_last_of('.'), "_std");
            txt_path_6.insert(txt_path_6.find_last_of('.'), "_std");
            kazarma_sort<Zek>(zadrot_list_bin_path, bin_path_6, before);
        }
        else
            kazarma_sort<Zek>(zadrot_list_bin_path);
        std::ifstream finit_6(bin_path_6, std::ios::binary);
        std::ofstream fonit_6(txt_path_6);
        if (!finit_6 || !fonit_6)
            throw "Cannot open export files.";

        std::cout << "List_Lyudey_S_Povishkoi:\n";
        while (finit_6.read((char*)&zek, sizeof(zek)))
        {
            std::cout << std::left
                << std::setw(23) << zek.surname
                << std::setw(2) << zek.group
                << std::setw(7) << zek.number << '\n';
            fonit_6 << std::left
                << std::setw(23) << zek.surname
                << std::setw(2) << zek.group
                << std::setw(7) << zek.number << '\n';
        }
        std::cout << '\n';

        finit_1.close();
        fonit_1.close();

        finit_2.close();
        fonit_2.close();

        finit_3.close();
        fonit_3.close();

        finit_4.close();
        fonit_4.close();

        finit_5.close();
        fonit_5.close();

        finit_6.close();
        fonit_6.close();

    }
}
