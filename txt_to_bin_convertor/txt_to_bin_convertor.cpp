#include <iostream>
#include <fstream>
#include <string>

struct Student
{
    size_t number = 0;
    char surname[22]{};
    char name[12]{};
    char patronymic[22]{};

    void operator<< (const char* str)
    {
        size_t size = std::min(strlen(str), sizeof(surname) - 1);
        if (str[0] != ';')
        {
            for (size_t i = 0; i < size - 1; ++i)
            {
                surname[i] = str[i];
            }
            surname[size - 1] = 0;
        }
        else
        {
            if (str[size - 1] != ';')
            {
                for (size_t i = 1; i <= size; ++i)
                {
                    patronymic[i - 1] = str[i];
                }
            }
            else
            {
                for (size_t i = 1; i < size - 1; ++i)
                {
                    name[i - 1] = str[i];
                }
                name[size - 2] = 0;
            }
        }
    }
};

struct Stud_Rec_Book
{
    size_t group = 0;
    size_t number = 0;
//    char subject_1[6]{};
    uint8_t mark_1 = 0;
//    char subject_2[6]{};
    uint8_t mark_2 = 0;
//    char subject_3[6]{};
    uint8_t mark_3 = 0;

    //void write_sudject(size_t number_of_subj, const char* str)
    //{
    //    size_t size = strlen(str);
    //    switch (number_of_subj)
    //    {
    //    case 1:
    //        for (uint8_t i = 0; i < size; ++i)
    //        {
    //            subject_1[i] = str[i];
    //        }
    //        subject_1[size] = 0;
    //        break;
    //    case 2:
    //        for (uint8_t i = 0; i < size; ++i)
    //        {
    //            subject_2[i] = str[i];
    //        }
    //        subject_2[size] = 0;
    //        break;
    //    case 3:
    //        for (uint8_t i = 0; i < size; ++i)
    //        {
    //            subject_3[i] = str[i];
    //        }
    //        subject_3[size] = 0;
    //        break;
    //    default:
    //        break;
    //    }
    //}

    void write_mark(uint8_t number_of_subj, uint8_t mark)
    {
        switch (number_of_subj)
        {
        case 1:
            mark_1 = mark;
            break;
        case 2:
            mark_2 = mark;
            break;
        case 3:
            mark_3 = mark;
            break;
        default:
            break;
        }
    }
};

void txt_to_bin_converter(const std::string& in_path_stud,
    const std::string& out_path_stud,
    const std::string& in_path_mark,
    const std::string& out_path_mark)
{
    uint8_t count_of_subjects = 3;
    Student buf_student;
    std::string buf_str;
    Stud_Rec_Book buf_srb;
    size_t pos = 0, next_pos = 0;

    setlocale(LC_ALL, "Russian");

    std::ifstream fin_s(in_path_stud);
    std::ofstream fout_s(out_path_stud, std::ios::binary);
    while (fin_s.peek() != EOF)
    {
        std::getline(fin_s, buf_str, '\n');
        pos = buf_str.find_first_of(';');
        buf_student.number = atoi(buf_str.substr(0, pos).c_str());
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos + 1, next_pos - pos).c_str();
        pos = next_pos;
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos, next_pos + 1 - pos).c_str();
        pos = next_pos;
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos, next_pos - pos).c_str();

        fout_s.write((const char*)&buf_student, sizeof(buf_student));

    }
    fout_s.close();
    fin_s.close();


    std::ifstream fin_m(in_path_mark);
    std::ofstream fout_m(out_path_mark, std::ios::binary);

    while (fin_m.peek() != EOF)
    {
        std::getline(fin_m, buf_str, '\n');
        pos = buf_str.find_first_of(';');
        buf_srb.group = atoi(buf_str.substr(0, pos).c_str());
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_srb.number = atoi(buf_str.substr(pos + 1, next_pos - pos - 1).c_str());
        for (uint8_t i = 1; i <= count_of_subjects; ++i)
        {
            pos = next_pos;
            next_pos = buf_str.find_first_of(';', pos + 1);
            //buf_srb.write_sudject(i, buf_str.substr(pos + 1, next_pos - pos - 1).c_str());
            pos = next_pos;
            next_pos = buf_str.find_first_of(';', pos + 1);
            buf_srb.write_mark(i, atoi(buf_str.substr(pos + 1, next_pos - pos - 1).c_str()));
        }
        fout_m.write((const char*)&buf_srb, sizeof(buf_srb));
    }
    fout_m.close();
    fin_m.close();
}

int main()
{
    txt_to_bin_converter("..\\txt_files\\student.txt",
        "..\\bin_files\\student.bin",
        "..\\txt_files\\marks.txt",
        "..\\bin_files\\marks.bin");
}