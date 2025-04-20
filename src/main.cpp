#include "mylist.h"
#include <stdio.h>
#include "hash_table.h"
#include <ctype.h>
#include <immintrin.h>

int main ()
{
    // unsigned long long t1 = __rdtsc ();
    // Table* table = TableCtor (10000);
    // ParsingText ("./data/war.txt", table);
    // LoadingData (table);

    // int n = 0;
    // for (int i = 0; i < 100; i++)
    //     n += Test (table);

    // printf ("%d\n", n);
    // TableDtor (table);
    // unsigned long long t2 = __rdtsc ();
    // printf ("%lld\n", t2-t1);

    Table* table = TableCtor (1483);
    ParsingText ("./data/war.txt", table);
    LoadingData (table);
    double n = 0;
    for (int i = 0; i < 1483; i++)
    {
        n += (double) table->array[i]->size * (double) table->array[i]->size;
        printf ("%u\n", table->array[i]->size);
    }
    TableDtor (table);
    n = n / 1483;
    n -= 225;
    // printf ("n = %lf\n", n);
}

// RISC CICS 