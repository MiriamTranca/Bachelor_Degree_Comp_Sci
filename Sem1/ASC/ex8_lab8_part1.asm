;A natural number a (a: dword, defined in the data segment) is given. Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.

;Read two numbers a and b (base 10) from the keyboard and calculate: (a+b)/(a-b). The quotient will be stored in a variable called "result" (defined in the data segment). The values are considered in signed representation.

;Read two numbers a and b (base 10) from the keyboard and calculate: (a+b)*(a-b). The result of multiplication will be stored in a variable called "result" (defined in the data segment).


bits 32
global start        
extern exit, printf, scanf           
import exit msvcrt.dll   
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
    a dd 0 
    b dd 0 
    result dd 0 
    format db "%d", 0
    message1 db "Give a: ", 0 
    message2 db "Give b: ", 0
    message3 db "The result %+d", 0
    
    
segment code use32 class=code
    start:
        ;print message1 
        ;printf(message1)
        push dword message1 
        call [printf]
        add esp, 4 ; clear the stack 
        
        ;we read the number and store it in variable a
        ;scanf(format, a)
        push dword a 
        push dword format
        call [scanf] 
        add esp, 4*2
        
        ;print message2 
        ;printf(message2)
        push dword message2
        call [printf]
        add esp, 4 ; clear the stack 
        
        ;we read the number and store it in variable b
        ;scanf(format, b)
        push dword b
        push dword format
        call [scanf] 
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b] ; in eax = a+b
        
        mov ebx, [a]
        sub ebx, [b] ; in ebx = a-b 
        
        cdq
        idiv ebx ; in eax = (a+b)/(a-b)
        
        mov [result], eax 
        
        push dword [result]
        push message3
        call [printf]
        add esp, 8
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
