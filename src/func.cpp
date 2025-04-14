#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"
#include "fileproces.h"
#include <assert.h>
#include "hash_table.h"
#include <ctype.h>

Table* TableCtor (size_t size)
{
    Table* table = (Table*) calloc (1, sizeof (Table));
    assert (table);

    LIST** array = (LIST**) calloc (size, sizeof (LIST*));
    assert (array);

    for (size_t i = 0; i < size; i++)
        array[i] = ListCtor (10);

    table->array = array;
    table->size  = size;
    table->str   = NULL;

    return table;
}

void TableDtor (Table* table)
{
    size_t size = table->size;

    for (size_t i = 0; i < size; i++)
    {
        ListDtor (table->array[i]);
    }

    free (table->array);
    if (table->str)
        free (table->str);
    free (table);
    
}

void LoadingData (const char* name_file, Table* table)
{
    FILE* file = fopen (name_file, "r");
    size_t size_file = 0;
    char* array = ReadFile (file, &size_file);
    table->str = array;

    while (array[0])
    {
        int n = 0;
        sscanf (array, "%*[^ \n]%n", &n);
        array[n] = '\0';

        StrToLower (array);
        int index = PolynomialHash (array);
        Insert (array, table->array[index % table->size]);

        array += n + 1;
        SkipSpace (&array);
    }
}

void SkipSpace (char** str)
{
    int n = 0;
    sscanf (*str, "%*[\r \n]%n", &n);
    *str += n;
}

unsigned int PolynomialHash (char* str)
{
    unsigned int hash = 0;
    unsigned k = 1;

    while (str[0])
    {
        hash += (unsigned) (str[0] - 'a' + 1) * k;
        k *= 103;
        str++;
    }

    return hash;
}

void StrToLower(char* str) 
{
    while (*str) 
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}