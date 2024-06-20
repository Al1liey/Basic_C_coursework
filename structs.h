#ifndef STRUCT
#define STRUCT
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#define MAX(type, a, b) ((type)(a)>(type)(b)?(type)(a):(type)(b))
#define MIN(type, a, b) ((type)(a)>(type)(b)?(type)(b):(type)(a))
#define ERROR(a) (printf("Ошибка, неизвестное значение аргумента %s\nДля информации: -h\n", a))
#define INFO (printf("|\t\t\tИНФОРМАЦИЯ О ПРОГРАММЕ\t\t\t   |\n|\t\t\tПомощь-h\t\t\t\t   |\n|\t\t\tВывод информации за год -f 'filename.csv'  |\n|\t\t\tВывод информации за месяц -m xx\t\t   |\n"))
#define TABLE_LINE (printf("|# | ГОД  |МЕСЯЦ|  ИЗМЕРЕНИЯ | ОШИБКИ  |СРЕД.ЗНАЧ|  МАКС  |  МИН   |\n"))
#define GRAN (printf("+------------------------------------------------------------------+\n"))
typedef struct database
{
    int16_t year;
    int8_t month;
    int8_t day;
    int8_t hour;
    int8_t minute;
    int8_t temp;
} database;

typedef struct workfile
{
    char* path;
    int8_t month;
    int error[12];
    database* data_base;
    int64_t datacount;
    int64_t size;
} workfile;
void read_com(int argc, char** argv, workfile* table);
int append_table(workfile* table, char* filename, int month);
void init_table(workfile* table, char* filename, int8_t month);
int check_perm(char *filename);
#endif