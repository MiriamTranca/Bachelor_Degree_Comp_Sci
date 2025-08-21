bits 32 
global start        
extern exit         
import exit msvcrt.dll  
  
segment data use32 class=data
    s dd 12344321h, 23455432h, 34567890h
    a1 resd 10 
    a2 resd 10 
    a3 resd 10
    word_a1 dw 0
    len equ ($-s)/4
    
segment code use32 class=code
    start:
        ;for a1
        mov ecx, len; for the loop 
        mov esi, 0
        mov ebx, 0
        loop_a1:
            cld
            
            ;out of the loop jump
            cmp ecx, 0 
            je final_a1
            
            mov eax, [s+esi*4] ; moving the curent dword in eax 
            
            std
            lodsw 
            
            shr eax, 16 ; putting the high part in ax 
            
            cmp di, ax 
            jne not_palindrom
                
                
            
            palindrom: 
                mov edx, dword[s+esi*4] 
                mov dword[a1 + ebx*4], edx
                inc ebx
            
            not_palindrom:
            dec ecx
            inc esi 
            jmp loop_a1
           
        final_a1:   
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
