#include <stdio.h>
#include <stdlib.h>

int get_operation(FILE *fp, int op_size)
{

    char option[op_size];
    int op;

    if (fgets(option, op_size, fp) != NULL)
    {
        return atoi(option);
    }
}