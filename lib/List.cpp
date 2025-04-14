#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include <mylist.h>

#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}

LIST* ListCtor (size_t size)
{
    if (!size) 
        return NULL;

    Elem_t* data_calloc = (Elem_t*) calloc (size, sizeof (Elem_t));
    if (data_calloc == NULL) 
        return NULL;
    
    int* next_calloc = (int*) calloc (size, sizeof (int));
    if (next_calloc == NULL) 
        return NULL;
    
    int* prev_calloc = (int*) calloc (size, sizeof (int));
    if (prev_calloc == NULL) 
        return NULL;
    
    LIST* list_calloc = (LIST*) calloc (1, sizeof (LIST));
    if (list_calloc == NULL) 
        return NULL;

    list_calloc->data = data_calloc;
    list_calloc->next = next_calloc;
    list_calloc->prev = prev_calloc;
    list_calloc->size = size;
    list_calloc->free = 1;

    for (int i = 0; i < (int) size; i++)
    {
        list_calloc->next[i] = i + 1;
        list_calloc->prev[i] = EMPTY_CELL;
        list_calloc->data[i].n_repeat = EMPTY_CELL;
        list_calloc->data[i].str = NULL;
    }

    list_calloc->next[0]        = 0;
    list_calloc->prev[0]        = 0;
    list_calloc->next[size - 1] = EMPTY_CELL;

    return list_calloc;
}

void ListDtor (LIST* list)
{
    assert (list);

    free (list->data);
    list->data = NULL;

    free (list->next);
    list->next = NULL;

    free (list->prev);
    list->prev = NULL;

    list->free = 0;

    list->size = 0;  

    free (list);
    list = 0;
}

int Insert (char* str, LIST* list)
{
    assert (list);

    int index = Find (str, list);
    if (index != -1)
    {
        list->data[index].n_repeat += 1;
    }
    
    else
    {
        if (list->free == EMPTY_CELL)
            ERROR (MyRealloc (list), OK);

        int next_free = list->next[list->free];

        list->data[list->free].str = str;
        list->data[list->free].n_repeat = 1;
        list->next[list->free] = list->next[0];
        list->prev[list->free] = 0;

        list->prev[list->next[0]] = list->free;
        list->next[0] = list->free;
        list->free = next_free; 

    }
    return OK;

}

// int InsertAfter (Elem_t value, int point, LIST* list)
// {
//     assert (list);

//     if (list->free == EMPTY_CELL)
//         ERROR (MyRealloc (list), OK);

//     int next_free = list->next[list->free];

//     list->data[list->free] = value;
//     list->next[list->free] = list->next[point];
//     list->prev[list->free] = point;

//     list->prev[list->next[point]] = list->free;
//     list->next[point] = list->free;
//     list->free = next_free; 
    
//     return OK;
// }

// int InsertBefore (Elem_t value, int point, LIST* list)
// {
//     assert (list);

//     if (list->free == EMPTY_CELL)
//         ERROR (MyRealloc (list), OK);

//     int next_free = list->next[list->free];
    
//     list->data[list->free] = value;
//     list->next[list->free] = point;
//     list->prev[list->free] = list->prev[point];

//     list->next[list->prev[point]] = list->free;
//     list->prev[point] = list->free;
//     list->free = next_free;   


//     return OK;
// }

// int InsertHead (Elem_t value, LIST* list)
// {
//     ERROR (InsertAfter (value, 0, list), OK);

//     return OK;
// }

// int InsertTail (Elem_t value, LIST* list)
// {
//     ERROR (InsertBefore (value, 0, list), OK);

//     return OK;
// }

// void DeletePoint (int point, LIST* list)
// {
//     assert (list);

//     list->data[point].str = NULL;
//     list->data[point].n_repeat = EMPTY_CELL;
//     list->prev[list->next[point]] = list->prev[point];
//     list->next[list->prev[point]] = list->next[point];
//     list->next[point] = list->free;
//     list->free = point;
//     list->prev[point] = EMPTY_CELL;

// }

// void DeleteHead  (LIST* list)
// {
//     DeletePoint (list->next[0], list);
// }

// void DeleteTail (LIST* list)
// {
//     DeletePoint (list->prev[0], list);
// }


int FindElement (char* value, LIST* list)
{
    assert (list);

    for (int i = 1; i < (int) list->size; i++)
        if (list->data[i].str && !strcmp (value, list->data[i].str))
            return list->data[i].n_repeat;

    return -1;
}

int Find (char* value, LIST* list)
{
    assert (list);

    for (int i = 1; i < (int) list->size; i++)
    {
        if (list->data[i].str && !strcmp (value, list->data[i].str))
            return i;
    }

    return -1;
}

int MyRealloc (LIST* list)
{
    assert (list);

    Elem_t* new_data = (Elem_t*) realloc (list->data, (size_t) (list->size) * 2 * sizeof (Elem_t));
    if (new_data == 0) 
        return ERROR_REALLOC;
    list->data = new_data;

    int* new_next = (int*) realloc (list->next, (size_t) (list->size) * 2 * sizeof (int));
    if (new_next == 0) 
        return ERROR_REALLOC;
    list->next = new_next;

    int* new_prev = (int*) realloc (list->prev, (size_t) (list->size) * 2 * sizeof (int));
    if (new_prev == 0) 
        return ERROR_REALLOC;
    list->prev = new_prev;

    list->size *= 2;

    for (int i = (int) list->size / 2; i < (int) list->size; i++) 
    {
        list->next[i] = i + 1;
        list->data[i].n_repeat = EMPTY_CELL;
        list->data[i].str = NULL;
        list->prev[i] = EMPTY_CELL;
    }

    list->next[list->size - 1] = EMPTY_CELL;
    list->free = (int) list->size / 2;
    return OK;
}