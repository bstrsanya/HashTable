#ifndef MYLIST_H
#define MYLIST_H

#include <stdio.h>

struct NODE
{
    char* str;
    int n_repeat;
};

typedef NODE Elem_t;

struct LIST
{
    Elem_t* data;
    int* next;
    int* prev;
    size_t size;
    int free;
};    

LIST* ListCtor (size_t SIZE);
void ListDtor (LIST* list);
int MyRealloc (LIST* list);

// int InsertHead   (Elem_t value, LIST* list);
// int InsertAfter  (Elem_t value, int point, LIST* list);
// int InsertTail   (Elem_t value, LIST* list);
// int InsertBefore (Elem_t value, int point, LIST* list);

int Insert (char* str, LIST* list);
int Find (char* value, LIST* list);

int FindElement (char* value, LIST* list);

// void DeleteHead  (LIST* list);
// void DeleteTail  (LIST* list);
// void DeletePoint (int point, LIST* list);

enum ERRORS
{
    ERROR_REALLOC     = 1,
    OK                = 2,
    ER_CONNECT_ELEM   = 0b0000'0001,
    ER_POINT_ITSELF   = 0b0000'0010,
    ER_CONNECT_FREE   = 0b0000'0100
};

const int LEN_STR    = 100;
const int EMPTY_CELL = -1;
const size_t SIZE    = 5;

#endif // MYLIST_H