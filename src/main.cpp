#include "mylist.h"
#include <stdio.h>
#include "hash_table.h"
#include <ctype.h>

int main ()
{
    Table* table = TableCtor (1000003);
    LoadingData ("./data/War_and_Peace.txt", table);
    char* a = "clean";
    int n = FindElement (a, table->array[PolynomialHash (a) % table->size]);
    printf ("n = %d\n", n);
    TableDtor (table);
}