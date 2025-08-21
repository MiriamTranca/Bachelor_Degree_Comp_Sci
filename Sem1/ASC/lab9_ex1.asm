;LAB 11 SITE VANCEA
bits 32 

global start        

extern exit
import exit msvcrt.dll 
 
segment data use32 class=data
    a dd 20
    b dd 44
    s db 1,2,3,4,5
    ls equ $-s
    
segment code use32 class=code
    sumarray:
        ;int sumarray(s[] - array, ls - int)
        ; eax result
        ; free stack in procedure 
        ; ret add - esp
        ; s - esp+4
        ; ls - esp+8
        mov ecx, [esp+8]
        mov esi, [esp+4]
        mov bl, 0
        jecxz .end_loop
        .myrepeat:
            lodsb
            add bl, al
        loop .myrepeat
        .end_loop:
        mov eax, 0
        mov al, bl
        ret 2*4
        
    sum: 
            ; int sum(int a, int b)
            ; params in rev order on stack
            ; result in eax (sum of numbers)
            ; procedure will free the stack (if we use ret 4*2)
            ; ret address - esp
            ; a - esp + 4
            ; b - esp + 8
            mov eax, [esp+4]
            add eax, [esp+8]
            ret
            ; or ret 4*2 makes ret and esp, 4*2 in one command
    start:
        push dword [b]
        push dword [a]
        call sum
        add esp, 4*2
        
        ;eax contains the sum 
        
        
        ;int sumarray(s[] - array, ls - int)
        push dword ls
        push dword s
        call sumarray
        
        ; exit(0)
        push    dword 0      
        call    [exit]