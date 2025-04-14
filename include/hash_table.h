#ifndef HASH_TABLE
#define HASH_TABLE

struct Table
{
    LIST** array;
    char* str;
    size_t size;
};

Table* TableCtor (size_t size);
void TableDtor (Table* table);
void LoadingData (const char* name_file, Table* table);
void SkipSpace (char** str);
unsigned int PolynomialHash (char* str);
void StrToLower (char *str);

#endif // HASH_TABLE