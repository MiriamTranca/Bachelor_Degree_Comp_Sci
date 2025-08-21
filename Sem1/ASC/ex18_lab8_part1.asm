;Read a decimal number and a hexadecimal number from the keyboard. Display the number of 1's of the sum of the two numbers in decimal format. Example:
;a = 32 = 0010 0000b
;b = 1Ah = 0001 1010b
;32 + 1Ah = 0011 1010b
;The value printed on the screen will be 4

bits 32 
global start        
extern exit, printf, scanf              
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll



segment data use32 class=data
    a dd 0
    b dd 0 
    mes_1 db "give a: ", 0
    mes_2 db "give b: ", 0
    format1 db "%d", 0
    format2 db "%x", 0
    result dd 0
    
segment code use32 class=code
    start:
        ;print mes_1
        push dword mes_1
        call [printf]
        add esp, 4
        
        ;read a from keyboard 
        push dword a 
        push dword format1 
        call [scanf]
        add esp, 8 
        
        ;print mes_2
        push dword mes_2
        call [printf]
        add esp, 4
        
        ;read b from keyboard 
        push dword b 
        push dword format2
        call [scanf]
        add esp, 8 
        
        mov eax, [a] 
        add eax, [b] ; in eax we have a+b 
        
        ;count the number of 1's in ebx 
        mov ebx, 0 ; conuter 
        count_ones_loop: 
            test eax, 1 ; cheking the least significant bit 
            jz skip_increment ; if it is 0 
            inc ebx 
            skip_increment:
                shr eax, 1 ; shift right by 1
                jnz count_ones_loop ; repeat until eax is 0 
                
        mov [result], ebx 
        
        push dword [result]
        push format1 
        call [printf]
        add esp, 8
        
        
        
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
