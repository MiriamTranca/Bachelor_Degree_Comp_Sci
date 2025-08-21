bits 32 
global start        

extern cerinta
extern exit              

import exit msvcrt.dll    

segment data use32 class=data
   sir db 11, 34, 66, 33
   len equ $- sir ; number of bytes in sir
   
segment code use32 class=code
    start:
        ; apelam functia cerinta din file_b 
        ; cerinta [lungime, sir]
        push dword sir 
        push dword len 
        call cerinta 
        add esp, 8 ;clear stack
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
