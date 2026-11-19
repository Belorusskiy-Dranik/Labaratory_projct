#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <fstream>
#include <string>

struct Student_bin
{
    size_t number = 0;
    char surname[22]{};
    char name[12]{};
    char patronymic[30]{};

    void operator<< (const char* str)
    {
        size_t size = strlen(str);
        if (size < 2)
            throw "Empty name field.";
        if (str[0] != ';')
        {
            if (size - 1 >= sizeof(surname))
                throw "Surname is too long.";
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
                if (size - 1 >= sizeof(patronymic))
                    throw "Patronymic is too long.";
                for (size_t i = 1; i < size; ++i)
                {
                    patronymic[i - 1] = str[i];

                }
                patronymic[size - 1] = 0;
            }
            else
            {
                if (size < 3 || size - 2 >= sizeof(name))
                    throw "Name is empty or too long.";
                for (size_t i = 1; i < size - 1; ++i)
                {
                    name[i - 1] = str[i];
                }
                name[size - 2] = 0;
            }
        }
    }
};

struct Rec_Book_bin
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
    Student_bin buf_student;
    std::string buf_str;
    Rec_Book_bin buf_srb;
    size_t pos = 0, next_pos = 0;

    setlocale(LC_ALL, "Russian");

    std::ifstream fin_s(in_path_stud);
    std::ofstream fout_s(out_path_stud, std::ios::binary);
    if (!fin_s || !fout_s)
        throw "Cannot open student files.";
    while (std::getline(fin_s, buf_str))
    {
        if (buf_str.empty())
            continue;
        if (buf_str[buf_str.size() - 1] == '\r')
            buf_str.erase(buf_str.size() - 1);
        size_t separators = 0;
        for (size_t i = 0; i < buf_str.size(); ++i)
            if (buf_str[i] == ';')
                ++separators;
        if (separators != 3)
            throw "Student line must contain four fields.";
        buf_student = Student_bin();
        pos = buf_str.find_first_of(';');
        buf_student.number = atoi(buf_str.substr(0, pos).c_str());
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos + 1, next_pos - pos).c_str();
        pos = next_pos;
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos, next_pos + 1 - pos).c_str();
        pos = next_pos;
        next_pos = buf_str.find_first_of(';', pos + 1);
        buf_student << buf_str.substr(pos).c_str();

        fout_s.write((const char*)&buf_student, sizeof(buf_student));

    }
    fout_s.close();
    fin_s.close();


    std::ifstream fin_m(in_path_mark);
    std::ofstream fout_m(out_path_mark, std::ios::binary);

    if (!fin_m || !fout_m)
        throw "Cannot open marks files.";
    while (std::getline(fin_m, buf_str))
    {
        if (buf_str.empty())
            continue;
        if (buf_str[buf_str.size() - 1] == '\r')
            buf_str.erase(buf_str.size() - 1);
        size_t separators = 0;
        for (size_t i = 0; i < buf_str.size(); ++i)
            if (buf_str[i] == ';')
                ++separators;
        if (separators != 7)
            throw "Marks line must contain eight fields.";
        buf_srb = Rec_Book_bin();
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
            std::string mark_str = buf_str.substr(pos + 1, next_pos - pos - 1);
            if (mark_str.empty() || mark_str.find_first_not_of("0123456789") != std::string::npos ||
                mark_str.size() > 2)
                throw "Invalid mark.";
            int mark = atoi(mark_str.c_str());
            if (mark < 0 || mark > 10)
                throw "Mark must be between 0 and 10.";
            buf_srb.write_mark(i, (uint8_t)mark);
        }
        fout_m.write((const char*)&buf_srb, sizeof(buf_srb));
    }
    fout_m.close();
    fin_m.close();
}
