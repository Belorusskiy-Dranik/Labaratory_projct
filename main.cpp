#include "CalAveBal/CalAveBal/CalAveBal.h"
#include "Giga_print/Giga_print.h"
#include "Kazarma_Check/Kazarma_Check.h"
#include "Kazarma_sort/Kazarma_sort.h"
#include "Task_F/Task_F.h"
#include "Zadrot_List/Zadrot_List.h"
#include "generate_rec_book_for_group_sort_alphabet/generate_rec_book_for_group_sort_alphabet.h"
#include "linking_surname_to_SRB/linking_surname_to_SRB.h"
#include "task_H.cpp/taskH.h"
#include "txt_to_bin_convertor/txt_to_bin_convertor.h"

#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(1251);
    int group = 2;

    try
    {
        txt_to_bin_converter("txt_files/student.txt", "bin_files/student.bin",
            "txt_files/marks.txt", "bin_files/marks.bin");

        linking_surname_to_SRB("bin_files/student.bin", "bin_files/marks.bin",
            "bin_files/marks_with_surname.bin");

        add_ave_bal("bin_files/marks_with_surname.bin", "bin_files/average_marks.bin");

        Kazarma_Check("bin_files/marks_with_surname.bin", "bin_files/failing.bin");

        std::cout << "Failing students before sorting\n";
        kazarma_print("bin_files/failing.bin");
        kazarma_sort("bin_files/failing.bin");
        std::cout << "\nFailing students after sorting\n";
        kazarma_print("bin_files/failing.bin");

        generate_rec_book_for_group_sort_alphabet("bin_files/student.bin", "bin_files/marks.bin",
            "bin_files/group_alphabet.bin", group);

        generate_rec_book_for_group_sort_average("bin_files/student.bin", "bin_files/marks.bin",
            "bin_files/group_average.bin", group);

        Zadrot_List("bin_files/marks_with_surname.bin", "bin_files/excellent.bin");

        giga_print("bin_files/marks_with_surname.bin", "bin_files/average_marks.bin",
            "bin_files/group_alphabet.bin", "bin_files/group_average.bin",
            "bin_files/excellent.bin", "bin_files/failing.bin",
            "txt_files/marks_with_surname.txt", "txt_files/average_marks.txt",
            "txt_files/group_alphabet.txt", "txt_files/group_average.txt",
            "txt_files/excellent.txt", "txt_files/failing.txt");

        generate_rec_book_for_group_sort_average("bin_files/student.bin", "bin_files/marks.bin",
            "bin_files/group_average.bin", group);
    }
    catch (const char* e)
    {
        std::cout << "Error: " << e << '\n';
        return 1;
    }

    return 0;
}
