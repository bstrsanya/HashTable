section .text

global my_crc32

my_crc32:
                push rsi 
                push rdi                      

                mov eax, -1

            .1: cmp edi, 4
                jb .3

                crc32 eax, dword [rsi]
                add rsi, 4
                sub edi, 4
                jmp .1

            .3: test edi, edi
                jz .2

            .4: crc32 eax, byte [rsi]
                inc rsi
                dec edi
                jnz .4

            .2: xor eax, -1
                
                pop rdi                        
                pop rsi
                           
                ret