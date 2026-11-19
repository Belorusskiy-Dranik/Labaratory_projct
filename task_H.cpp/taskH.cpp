#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

struct Student{
    size_t number = 0;
    char surname[22]{};
    char name[12]{};
    char patronymic[30]{};
};

struct Rec_Book{
    size_t group = 0;
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
};

struct Stud_Rec_Book_with_aver_marks{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
    double average = 0;
};

static size_t group_size(
    const std::string& in_path_rec_book,
    const size_t group){

    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
    if (!fin_rec_book)
        throw "Cannot open group marks.";
    Rec_Book a;
    size_t counter = 0;
    while(fin_rec_book.read((char*) &a, sizeof(Rec_Book)) ){
        if(a.group == group){
            ++counter;
        }
    }
    fin_rec_book.close();
    return counter;
}

static bool compare(Stud_Rec_Book_with_aver_marks const& Stud_Rec_Book_with_aver_marks_1, Stud_Rec_Book_with_aver_marks const& Stud_Rec_Book_with_aver_marks_2)
{
    return Stud_Rec_Book_with_aver_marks_1.average < Stud_Rec_Book_with_aver_marks_2.average;
}

static void sort(const std::string& in_path)
{
    std::fstream finit(in_path, std::ios::out | std::ios::binary | std::ios::in);
    if (!finit) throw "Cannot open group report for sorting.";
    Stud_Rec_Book_with_aver_marks Stud_Rec_Book_with_aver_marks_1, Stud_Rec_Book_with_aver_marks_2;
    finit.seekg(0, std::ios::end);
    size_t m_1 = finit.tellg();
    finit.seekg(0);
    size_t m_2 = finit.tellg();
    if ((m_1 - m_2) % sizeof(Stud_Rec_Book_with_aver_marks) != 0)
        throw "Incomplete group report record.";
    size_t size = (m_1 - m_2) / sizeof(Stud_Rec_Book_with_aver_marks);
    finit.seekp(0);
    for (size_t i = 0; i + 1 < size; ++i)
    {
        finit.clear();
        finit.seekg(0, std::ios::beg);
        finit.seekp(0, std::ios::beg);
        for (size_t j = 0; j + 1 < size - i; ++j)
        {
            finit.seekg(j * ((int)sizeof(Stud_Rec_Book_with_aver_marks)), std::ios::beg);
            finit.read((char*)&Stud_Rec_Book_with_aver_marks_1, sizeof(Stud_Rec_Book_with_aver_marks));
            finit.read((char*)&Stud_Rec_Book_with_aver_marks_2, sizeof(Stud_Rec_Book_with_aver_marks));


            if (compare(Stud_Rec_Book_with_aver_marks_1, Stud_Rec_Book_with_aver_marks_2))
            {
                finit.seekp(j * ((int)sizeof(Stud_Rec_Book_with_aver_marks)), std::ios::beg);
                finit.write((const char*)&Stud_Rec_Book_with_aver_marks_2, sizeof(Stud_Rec_Book_with_aver_marks));
                finit.write((const char*)&Stud_Rec_Book_with_aver_marks_1, sizeof(Stud_Rec_Book_with_aver_marks));
                finit.flush();
            }
        }
    }
    finit.close();
}


void generate_rec_book_for_group_sort_average(
    const std::string& in_path_stud,
    const std::string& in_path_rec_book,
    const std::string& out_path,
    const size_t group){

    std::ifstream fin_stud(in_path_stud, std::ios::binary);
    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
    std::ofstream fout(out_path, std::ios::binary);

    if (!fin_stud || !fin_rec_book || !fout)
        throw "Cannot open files for group report.";
    if (group_size(in_path_rec_book, group) == 0)
    {
        fout.close();
        return;
    }

    Student a;
    Rec_Book b;
    Stud_Rec_Book_with_aver_marks c;

    while(fin_stud.read((char*) &a, sizeof(Student)) ){

        while(fin_rec_book.read((char*) &b, sizeof(Rec_Book) )){

            if(a.number == b.number && b.group == group){
                c.group = b.group;
                for(size_t i = 0; i < sizeof(c.surname); ++i){
                    c.surname[i] = a.surname[i];
                }
                c.number = b.number;
                c.mark_1 = b.mark_1;
                c.mark_2 = b.mark_2;
                c.mark_3 = b.mark_3;
                c.average = (b.mark_1 + b.mark_2 + b.mark_3) / 3.0;

                fout.write((const char*) &c, sizeof(c));
                break;
            }
        }
        fin_rec_book.clear();
        fin_rec_book.seekg(0);
    }
    fout.close();
    sort(out_path);

}
