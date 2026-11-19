#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>

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


struct Stud_Rec_Book
{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
};

void linking_surname_to_SRB( const std::string& in_path_stud, 
    const std::string& in_path_rec_book, 
    const std::string& out_path){

    std::ifstream fin_stud(in_path_stud, std::ios::binary);
    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
    std::ofstream fout(out_path, std::ios::binary);

    if (!fin_stud || !fin_rec_book || !fout)
        throw "Cannot open files for joining surnames.";

    Student a;
    Stud_Rec_Book c;
    Rec_Book b;

    while(fin_stud.read((char*) &a, sizeof(Student)) ){

        while(fin_rec_book.read((char*) &b, sizeof(Rec_Book) )){

            if(a.number == b.number){
                c.group = b.group;
                for (size_t i = 0; i < sizeof(c.surname); ++i)
                    c.surname[i] = a.surname[i];
                c.number = b.number;
                c.mark_1 = b.mark_1;
                c.mark_2 = b.mark_2;
                c.mark_3 = b.mark_3;
                fout.write((const char*)&c, sizeof(c));

                break;
            }
        }
        fin_rec_book.clear();
        fin_rec_book.seekg(0);
    }
    fout.close();
}
