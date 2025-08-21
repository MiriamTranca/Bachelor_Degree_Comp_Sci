bits 32 

global cerinta

extern printf 

import printf msvcrt.dll        

segment data use32 class=data
    format db "%d", 0
    number_correct dd 0
    number db 11
segment code use32 class=code
    
    cerinta:
        push ebp
        mov ebp, esp ; moving the stack frame 
        
        mov ecx, [ebp + 12] ; moving the length of the sir 
        mov esi, [ebp + 8] ; moving the adress of the sir 
        jz final 
        
        mov edi, 0
        
        loop_extern:
            cmp edi, ecx 
            jge final 
            
            mov ebx, edi 
            add ebx, 1
            loop_intern: 
                cmp ebx, ecx 
                jge next_extern ; doing the loop_extern for the next byte 
                
                ;constructing the word 
                movzx eax, byte[esi+edi] 
                movzx edx, byte[esi + ebx] 
                shl edx, 8 ; putting the byte into the higher part of the word 
                or eax, edx ; making the word 
                
                test eax, 1 ; checking if the last bit is 1 
                jz next_intern
                
                ;checking if divisible with 11 
                mov dx, 0 
                div byte[number] 
                cmp dx, 0 
                jne next_intern
                
                add dword[number_correct], 1 
                
                next_intern:
                    inc ebx 
                    jmp loop_intern
                
                next_extern:
                    inc edi 
                    jmp loop_extern
                    
    final:
        ;printf(format, number_correct)
        push dword[number_correct]
        push dword format
        call [printf]
        add esp, 8
        
        pop ebp
        ret
    
        