#include <stdio.h>
#include <ctype.h>
#include <immintrin.h>
#include "mylist.h"
#include "hash_table.h"

int main ()
{
    unsigned long long t1 = __rdtsc ();

    Table* table = TableCtor (SIZE_TABLE);
    ParsingText (INPUT_FILE, table);
    LoadingData (table);

    int n = 0;
    for (int i = 0; i < NUM_TESTS; i++)
        n += Test (table);

    TableDtor (table);

    unsigned long long t2 = __rdtsc ();
    printf ("%d, %lld\n", n, t2-t1);
}
