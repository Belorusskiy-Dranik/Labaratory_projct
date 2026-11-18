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


void linking_surname_to_SRB( const std::string& in_path_stud, 
    const std::string& in_path_rec_book, 
    const std::string& out_path){

    std::ifstream fin_stud(in_path_stud, std::ios::binary);
    std::ifstream fin_rec_book(in_path_rec_book, std::ios::binary);
    std::ofstream fout(out_path, std::ios::binary);

    Student a;
    Rec_Book b;

    while(fin_stud.read((char*) &a, sizeof(Student)) ){

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
}