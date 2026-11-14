# Labaratory_projct

struct Student{size_t number = 0;char surname[22]{};char name[12]{};char patronymic[22]{};}

struct Stud_Rec_Book{size_t group = 0;size_t number = 0;char subject_1[6]{};uint8_t mark_1 = 0;char subject_2[6]{};uint8_t mark_2 = 0;char subject_3[6]{};uint8_t mark_3 = 0;}

## Входная запись для расчёта среднего балла

Пункт **c)** читает объединённую ведомость из пункта **b)**. Оценки идут в порядке МА, ГЕО, ПРОГ. В `CalAveBal.cpp` входная запись имеет следующий формат.

```cpp
struct Stud_Rec_Book
{
    size_t group = 0;
    char surname[22]{};
    size_t number = 0;
    uint8_t mark_1 = 0;
    uint8_t mark_2 = 0;
    uint8_t mark_3 = 0;
};
```

Пункт **b)** должен записывать эту структуру целиком. В выходном файле пункта **c)** за каждой такой записью следует средний балл типа `double`.
