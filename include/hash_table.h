#ifndef HASH_TABLE
#define HASH_TABLE

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <cstdint>

struct Table
{
    LIST** array;
    char* str;
    char** num;
    size_t size;
};

Table* TableCtor (size_t size);
void TableDtor (Table* table);
void ParsingText (const char* name_file, Table* table);
void LoadingData (Table* table);
void SkipSpace (char** str);
int PolynomialHash (char* str);
void WordProcessing (char** str, int n); 
int Test (Table* table);
int MurmurHash2 (char* key);
int crc32HashFunc (char *buf);

int LenStrHashFunc (char* str);
int SumLetterHashFunc (char* str);


const size_t INITIAL_LIST_SIZE = 10;

#endif // HASH_TABLE