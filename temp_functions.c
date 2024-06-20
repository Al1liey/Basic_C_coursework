#include "temp_functions.h"
void statistic_for_all_year(workfile* work_file)
{
    GRAN;
    TABLE_LINE;
    GRAN;
    float average = 0;
    int year_max = -999;
    int year_min = 999;
    int count = 0;
    int16_t year = work_file->data_base[0].year;
    for (int i = 1; i <= 12 ; i++)
    {
        int month_max = -999;
        int month_min = 999;
        int month_count = 0;
        int month_average = 0;
        for(int j = 0; j < work_file->datacount; j++)
        {
            if(work_file->data_base[j].month == i)
            {
                month_max = MAX(int, month_max, work_file->data_base[j].temp);
                month_min = MIN(int, month_min, work_file->data_base[j].temp);
                month_average += work_file->data_base[j].temp;
                month_count++;
            }
        }
        year_max = MAX(int,year_max, month_max);
        year_min = MIN(int, year_min, month_min);
        if(month_count)
        {
        average += month_average/month_count;
        printf("|%-2d| %-2d | %3d |  %8d  |   %3d   |  %5d  |  %4d  |  %4d  |\n", i-1, year, i, month_count,work_file->error[i-1],month_average/month_count, month_max, month_min);
        count++;
        GRAN;
        }
        else{
        printf("|%-2d| %4d | %3d |  %8d  |   %3d   |  %5d  |  %4d  |  %4d  |\n", i-1, year, i, 0,0,0,0,0);
        GRAN;
        }
    }
    printf("|\t\t\tСТАТИСТИКА ЗА ГОД\t\t\t   |\n");
    GRAN;
    count != 0 ? printf("|\t\tСреднее значение %0.2f\t\t\t\t   |\n", average/count):printf("|\t\tСреднее значение 0.00\t\t\t\t   |\n");
    GRAN;
    year_max != -999 ? printf("|\t\tМаксимальная температура %d\t\t\t   |\n", year_max): printf("|\t\tМаксимальная температура 0\t\t\t   |\n") ;
    GRAN;
    year_min != 999 ? printf("|\t\tМинимальная температура %d\t\t\t   |\n", year_min) : printf("|\t\tМинимальная температура 0\t\t\t   |\n");
    GRAN;
}


void statistic_for_month(workfile* work_file)
{
    int max = -999;
    int min = 999;
    int average = 0;
    int count = 0;
    int16_t year = work_file->data_base[0].year;
    for(int i = 0; i < work_file->datacount; i++)
    {
        if (work_file->data_base[i].month == work_file->month)
        {
            max = MAX(int,max, work_file->data_base[i].temp);
            min = MIN(int, min, work_file->data_base[i].temp);
            average += work_file->data_base[i].temp;
            count++;
        }
    }
    if(count)
    {
        GRAN;
        TABLE_LINE;
        GRAN;
        printf("|%-2d| %-2d | %3d |  %8d  |   %3d   |  %5d  |  %4d  |  %6d  |\n", work_file->month-1, year, work_file->month, count, work_file->error[work_file->month-1], average/count, max, min);
        GRAN;
    }
    else
    {
        printf("Нет измерений за данный месяц\n");
    }
}