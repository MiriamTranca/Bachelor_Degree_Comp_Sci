;Read two numbers a and b (in base 16) from the keyboard and calculate a+b. Display the result in base 10

;Read two numbers a and b (in base 10) from the keyboard and calculate a+b. Display the result in base 16

;Read two numbers a and b (in base 10) from the keyboard. Calculate and print their arithmetic average in base 16

;Read a number in base 10 from the keyboard and display the value of that number in base 16

bits 32 
global start        
extern exit, printf, scanf             
import exit msvcrt.dll   
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dd 0 
    b dd 0 
    message1 db "a= ", 0
    message2 db "b= ", 0
    format db "%d", 0
    message3 db "arithmetic average %x", 0
    
    
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
        add eax, [b]
        
        cdq 
        mov ebx, 2
        idiv ebx
        
        push eax 
        push dword message3
        call [printf] 
        add esp , 8
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
