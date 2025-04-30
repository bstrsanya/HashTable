#include "mylist.h"
#include "fileproces.h"
#include "hash_table.h"
#include <xmmintrin.h>
#include <immintrin.h>

void LoadingData (Table* table)
{
    int i = 0;
    
    while (table->num[i])
    {
        int n = (int) strlen (table->num[i]);
        unsigned int index = crc32HashFunc (table->num[i], n);
        Insert (table->num[i], n, table->array[index % table->size]);
        i++;
    }
}

int Test (Table* table)
{
    FILE* file = fopen (FIND_WORDS_FILE, "r");
    size_t size_file = 0;
    char* find_words_array = ReadFile (file, &size_file);
    char* pointer_array = find_words_array;

    LIST** table_array = table->array;
    size_t table_size = table->size;

    int sum = 0;
    while (find_words_array[0])
    {
        int n = 0;
        while (find_words_array[n] != '\n')
            n++;

            find_words_array[n] = '\0';

        unsigned int index = crc32HashFunc (find_words_array, n);
        sum += FindElement (find_words_array, n, table_array[index % table_size]);

        find_words_array += n + 1;
    }

    free (pointer_array);

    return sum;
}

unsigned int crc32HashFunc (char *buf, int len)
{
    unsigned int crc = 0;

    asm 
    (
        ".intel_syntax noprefix                \n\t"
        "       mov eax, -1                    \n\t"    
        "       mov rsi, %[buf]                \n\t"        
        "       mov ecx, %[len]                \n\t"
        
        "1:     cmp ecx, 4                     \n\t"
        "       jb 3f                          \n\t"
        
        "       crc32 eax, dword ptr [rsi]     \n\t"
        "       add rsi, 4                     \n\t"
        "       sub ecx, 4                     \n\t"
        "       jmp 1b                         \n\t"
        
        "3:     test ecx, ecx                  \n\t"           
        "       jz 2f                          \n\t"                   
        
        "4:     crc32 eax, byte ptr [rsi]      \n\t" 
        "       inc rsi                        \n\t"                 
        "       dec rcx                        \n\t"                  
        "       jnz 4b                         \n\t"                   
        
        "2:     xor eax, -1                    \n\t"     
        "       mov %[crc], eax                \n\t"  

        ".att_syntax prefix                    \n\t"
        : [crc] "=r" (crc)
        : [buf] "r" (buf), [len] "r" (len)
        : "rax", "rcx", "rsi", "cc", "memory"
    );

    return crc;
}

int PolynomialHash (char* str)
{
    long long hash = 0;
    long long k = 1;
    int n = 0;

    while (str[n])
    {
        hash += (long long) (str[n]) * k;
        k *= 1013ll;
        hash %= 1844674407370955;
        k %= 1844674407370955;

        n++;
    }

    return (int) (hash % 2147483648);
}

int MurmurHash2 (char* key)
{
    unsigned int len = strlen (key);
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *)key;
    unsigned int k = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= (unsigned) data[1] << 8;
        k |= (unsigned) data[2] << 16;
        k |= (unsigned) data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
      case 3:
        h ^= (unsigned) data[2] << 16;
      case 2:
        h ^= (unsigned) data[1] << 8;
      case 1:
        h ^= data[0];
        h *= m;
    };
  
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
  
    return (int) (h % 2147483648);
}

int LenStrHashFunc (char* str)
{
    return (int) strlen (str);
}

int SumLetterHashFunc (char* str)
{
    int sum = 0;
    int n = 0;

    while (str[n])
    {
        sum += str[n];
        n++;
    }

    return sum;
}
