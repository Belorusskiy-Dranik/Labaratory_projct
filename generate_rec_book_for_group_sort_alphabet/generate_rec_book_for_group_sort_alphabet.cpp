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

struct Stud_Rec_Book{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
};

size_t group_size( 
    const std::string& in_path_rec_book,
    const size_t group){

    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
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

bool compare(Stud_Rec_Book const& Stud_Rec_Book_1, Stud_Rec_Book const& Stud_Rec_Book_2)
{
    return strcmp(Stud_Rec_Book_1.surname, Stud_Rec_Book_2.surname) < 0;
}

void sort(const std::string& in_path)
{
    std::fstream finit(in_path, std::ios::out | std::ios::binary | std::ios::in);
    if (!finit) return;
    Stud_Rec_Book Stud_Rec_Book_1, Stud_Rec_Book_2;
    finit.seekg(0, std::ios::end);
    size_t m_1 = finit.tellg();
    finit.seekg(0);
    size_t m_2 = finit.tellg();
    size_t size = (m_1 - m_2) / sizeof(Stud_Rec_Book);
    finit.seekp(0);
    for (size_t i = 0; i + 1 < size; ++i)
    {
        finit.clear();
        finit.seekg(0, std::ios::beg);
        finit.seekp(0, std::ios::beg);
        for (size_t j = 0; j + 1 < size - i; ++j)
        {
            finit.seekg(j * ((int)sizeof(Stud_Rec_Book)), std::ios::beg);
            finit.read((char*)&Stud_Rec_Book_1, sizeof(Stud_Rec_Book));
            finit.read((char*)&Stud_Rec_Book_2, sizeof(Stud_Rec_Book));


            if (compare(Stud_Rec_Book_1, Stud_Rec_Book_2))
            {
                finit.seekp(j * ((int)sizeof(Stud_Rec_Book)), std::ios::beg);
                finit.write((const char*)&Stud_Rec_Book_2, sizeof(Stud_Rec_Book));
                finit.write((const char*)&Stud_Rec_Book_1, sizeof(Stud_Rec_Book));
                finit.flush();
            }
        }
    }
    finit.close();
}


void generate_rec_book_for_group_sort_alphabet(
    const std::string& in_path_stud,
    const std::string& in_path_rec_book,
    const std::string& out_path,
    const int32_t group){

    std::ifstream fin_stud(in_path_stud, std::ios::binary);
    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
    std::ofstream fout(out_path, std::ios::binary);


    Student a;
    Rec_Book b;

    while(fin_stud.read((char*) &a, sizeof(Student)) ){

        if(a.number != group){
            continue;
        }

        while(fin_rec_book.read((char*) &b, sizeof(Rec_Book) )){

            if(a.number == b.number){
                fout.write( (const char*) &b.group, sizeof(b.group));
                fout.write( (const char*) &a.surname, sizeof(a.surname));
                fout.write( (const char*) &b.number, sizeof(b.number));
                fout.write( (const char*) &b.mark_1, sizeof(b.mark_1));
                fout.write( (const char*) &b.mark_2, sizeof(b.mark_2));
                fout.write( (const char*) &b.mark_3, sizeof(b.mark_3));

                break;
            }
        }
        fin_rec_book.clear();
        fin_rec_book.seekg(0);
    }

    sort(out_path);

}