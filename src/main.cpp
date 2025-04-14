#include "mylist.h"
#include <stdio.h>
#include "hash_table.h"
#include <ctype.h>

int main ()
{
    Table* table = TableCtor (10000);
    LoadingData ("./data/War_and_Peace.txt", table);
    int n = Test (table);
    printf ("%d\n", n);
    TableDtor (table);
}