#include "mylist.h"
#include "fileproces.h"
#include "hash_table.h"

Table* TableCtor (size_t size)
{
    Table* table = (Table*) calloc (1, sizeof (Table));
    assert (table);

    LIST** array = (LIST**) calloc (size, sizeof (LIST*));
    assert (array);

    for (size_t i = 0; i < size; i++)
        array[i] = ListCtor (INITIAL_LIST_SIZE);

    table->array = array;
    table->size  = size;
    table->str   = NULL;

    return table;
}

void TableDtor (Table* table)
{
    free (table->num);

    size_t size = table->size;

    for (size_t i = 0; i < size; i++)
        ListDtor (table->array[i]);

    free (table->array);

    if (table->str)
        free (table->str);

    free (table);
}

void ParsingText (const char* name_file, Table* table)
{
    FILE* file = fopen (name_file, "r");
    size_t size_file = 0;
    char* array = ReadFile (file, &size_file);
    table->str = array;

    table->num = (char**) calloc (600000, sizeof (char*));
    assert (table->num);

    int i = 0;
    while (array[0])
    {
        int n = 0;

        while (array[n] != '\n' && array[n] != ' ')
            n++;

        WordProcessing (&array, n);

        table->num[i++] = array;

        array += n + 1;
        SkipSpace (&array);
    }
}

void SkipSpace (char** str)
{
    int n = 0;
    while ((*str)[n] == '\r' || (*str)[n] == ' ' || (*str)[n] == '\n')
        n++;

    *str += n;
}

void WordProcessing (char** str, int n) 
{
    for (int i = 0; i < n; i++)
        (*str)[i] = tolower ((int) (*str)[i]);

    (*str)[n] = '\0';
    n--;

    while ((*str)[n] == '"' || (*str)[n] == '?'  || 
           (*str)[n] == '.' || (*str)[n] == ','  ||
           (*str)[n] == ':' || (*str)[n] == '\r' || 
           (*str)[n] == '!' || (*str)[n] == '\'' ||
           (*str)[n] == ';')
    {
        (*str)[n] = '\0';
        n--;
    }

    if (**str == '"' || **str == '\'')
    {
        (*str)++;
    }
}