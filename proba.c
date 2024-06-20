#include "structs.h"
int main(int argc, char** argv)
{
    workfile table = {0};
    read_com(argc, argv, &table);
    free(table.path);
    free(table.data_base);
    return 0;
}









