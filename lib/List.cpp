#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <mylist.h>
#include <ctype.h>
#include <cstdint>

#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}

LIST* ListCtor (size_t size)
{
    if (!size) 
        return NULL;

    Elem_t* data_calloc = (Elem_t*) aligned_alloc (32, size * sizeof (Elem_t));
    if (data_calloc == NULL) 
        return NULL;
    
    int* next_calloc = (int*) calloc (size, sizeof (int));
    if (next_calloc == NULL) 
        return NULL;
    
    int* prev_calloc = (int*) calloc (size, sizeof (int));
    if (prev_calloc == NULL) 
        return NULL;
    
    LIST* list_calloc = (LIST*) aligned_alloc (32, sizeof (LIST));
    if (list_calloc == NULL) 
        return NULL;

    list_calloc->data = data_calloc;
    list_calloc->next = next_calloc;
    list_calloc->prev = prev_calloc;
    list_calloc->capacity = size;
    list_calloc->size = 0;
    list_calloc->free = 1;

    for (int i = 0; i < (int) size; i++)
    {
        list_calloc->next[i] = i + 1;
        list_calloc->prev[i] = EMPTY_CELL;
        list_calloc->data[i].n_repeat = EMPTY_CELL;
        list_calloc->data[i].str = NULL;
        list_calloc->data[i].len = 0;
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
    list->capacity = 0;

    free (list);
    list = 0;
}

int Insert (char* str, int len, LIST* list)
{
    assert (list);

    int index = Find (str, len, list);
    if (index != -1)
    {
        list->data[index].n_repeat += 1;
    }
    
    else
    {
        if (list->free == EMPTY_CELL)
            ERROR (MyRealloc (list), OK);

        int next_free = list->next[list->free];

        uint8_t buf[32] = {0};
        memcpy (buf, str, len);
        __m256i vec = _mm256_loadu_si256 ((__m256i*) buf);
        list->data[list->free].avx = vec;        

        list->data[list->free].str = str;
        list->data[list->free].len = len;
        list->data[list->free].n_repeat = 1;
        list->next[list->free] = list->next[0];
        list->prev[list->free] = 0;
        list->size += 1;

        list->prev[list->next[0]] = list->free;
        list->next[0] = list->free;
        list->free = next_free; 

    }
    return OK;

}

int FindElement (char* value, int len, LIST* list)
{
    // assert (list);

    for (int i = 1; i < (int) list->size; i++)
    {
        // if (len != list->data[i].len)
        //     continue;
        
        // if (list->data[i].str && !strncmp (value, list->data[i].str, list->data[i].len))
        //     return list->data[i].n_repeat;

        // if (!strcmp (list->data[i].str, value))
        //     return list->data[i].n_repeat;

        alignas(32) uint8_t buf[32] = {0};
        memcpy (buf, value, len % 32);
        __m256i vec = _mm256_load_si256 ((__m256i*) buf);

        __m256i cmp = _mm256_xor_si256 (vec, list->data[i].avx);
        int result = _mm256_testz_si256(cmp, cmp);

        if (result == 1)
            return list->data[i].n_repeat;
    }

    return -1;
}

int Find (char* value, int len, LIST* list)
{
    assert (list);

    for (int i = 1; i < (int) list->capacity; i++)
    {
        if (list->data[i].len != len)
            continue;
        else
            if (list->data[i].str && !strncmp (value, list->data[i].str, (size_t) len))
                return i;
    }

    return -1;
}

int MyRealloc (LIST* list)
{
    assert (list);

    Elem_t* new_data = (Elem_t*) realloc (list->data, (size_t) (list->capacity) * 2 * sizeof (Elem_t));
    if (new_data == 0) 
        return ERROR_REALLOC;
    list->data = new_data;

    int* new_next = (int*) realloc (list->next, (size_t) (list->capacity) * 2 * sizeof (int));
    if (new_next == 0) 
        return ERROR_REALLOC;
    list->next = new_next;

    int* new_prev = (int*) realloc (list->prev, (size_t) (list->capacity) * 2 * sizeof (int));
    if (new_prev == 0) 
        return ERROR_REALLOC;
    list->prev = new_prev;

    list->capacity *= 2;

    for (int i = (int) list->capacity / 2; i < (int) list->capacity; i++) 
    {
        list->next[i] = i + 1;
        list->data[i].n_repeat = EMPTY_CELL;
        list->data[i].str = NULL;
        list->prev[i] = EMPTY_CELL;
    }

    list->next[list->capacity - 1] = EMPTY_CELL;
    list->free = (int) list->capacity / 2;
    return OK;
}