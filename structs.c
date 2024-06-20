#include "temp_functions.h"
int check_perm(char* filename)
{
    int s = strlen(filename) - 1;
    if(filename[s-3] == '.' && filename[s-2] == 'c' && filename[s-1] == 's' && filename[s] == 'v' && s >= 4)
    {   
        return 1;
    }
    return 0;
}


void init_table(workfile* table, char* filename, int8_t month)
{
    table->path = strdup(filename);
    table->month = month;
    table->size = 4;
    table->data_base = (database*)malloc(table->size * sizeof(database));
    table->datacount = 0;
    for(int i = 0; i < 12; i++)
    {
        table->error[i] = 0;
    }
} 


int append_table(workfile* table, char* filename, int month)
{
    init_table(table, filename, month);
    FILE *input = fopen(table->path, "r");
    if(input == NULL || !check_perm(table->path))
    {
        ERROR(table->path);
        return 0;
    }
    char line[32];
    while(fgets(line, sizeof(line), input))
    {
        if(table->datacount >= table->size)
        {
            table->data_base = realloc(table->data_base, sizeof(database) * table->size * 2);
            table->size = table->size * 2;
        }
        database* db = &table->data_base[table->datacount];
        if(sscanf(line, "%" SCNd16 ";%" SCNd8 ";%" SCNd8 ";%" SCNd8 ";%" SCNd8 ";%" SCNd8, &db->year, &db->month, &db->day, &db->hour, &db->minute, &db->temp) != 6)
        {
            printf("Ошибка в строке %d\n", table->datacount + 1);
            table->error[db->month-1]++;
            continue;
        }

        table->datacount++;
    }
    fclose(input);
    return 1;
}


void read_com(int argc, char** argv, workfile* table)
{
    int res = 0;
    opterr = 0;
    if(argc > 1)
    {
        while((res = getopt(argc, argv, "hf:m:")) != -1)
        {
            switch(res)
            {
                case 'h':
                    GRAN;
                    INFO;
                    GRAN;
                    return;
                case 'f':
                    if(optind < argc && argv[optind][1] != 'm')
                    {
                        ERROR(argv[optind]);
                        return;
                    }
                    else if(optind < argc && argv[optind][1] == 'm')
                    {
                        break;
                    }
                    else
                    {
                        if(append_table(table, optarg, 0))
                        {
                            statistic_for_all_year(table);
                        }
                        return;
                    }
                case 'm':
                    if(optind < argc && argv[optind][0])
                    {
                        ERROR(argv[optind]);
                        return;
                    }
                    if (0 < atoi(optarg) && atoi(optarg) <= 12)
                    {
                        if(append_table(table, argv[optind-3], atoi(optarg)))
                        {
                            statistic_for_month(table);
                        }
                        return;
                    }
                    else
                    {
                        ERROR(optarg);
                        return;
                    }
                case '?':
                    ERROR(argv[optind-1]);
                    return;
            }
        }
        if(optind < argc)
        {
            ERROR(optarg);
            return;
        }
    }
    else
    {
        GRAN;
        INFO;
        GRAN;
        return;
    }
}