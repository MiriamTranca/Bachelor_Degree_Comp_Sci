;Read two numbers a and b (in base 10) from the keyboard and calculate their product. This value will be stored in a variable called "result" (defined in the data segment).
bits 32 
global start        

extern exit, printf, scanf               
import exit msvcrt.dll   
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
    a dd 0 
    b dd 0
    message1 db "Please give a: ", 0
    message2 db "Please give b: ", 0
    result dd 0
    result_msg db "The result is: %d", 10, 0 ; Message with format specifier (%d) and newline
    format db "%d", 0 ;numbers are decimals 
    
    
segment code use32 class=code
    start:
        ;we printf message1
        push dword message1
        call [printf]
        add esp, 4 ; taking the parameter out of the stack
        
        ;we read the number and store it in variable a
        ;scanf(format, a)
        push dword a 
        push dword format
        call [scanf] 
        add esp, 4*2
        
        ;we printf message2
        push dword message2
        call [printf]
        add esp, 4 ; taking the parameter out of the stack
        
        ;we read the number and store it in variable b
        ;scanf(format, b)
        push dword b 
        push dword format
        call [scanf] 
        add esp, 4*2
        
        mov eax, [a] ;  put a in eax, to do the multiplication
        mov ebx, [b]
        mul ebx ; in edx:eax we have a*b 
        
        mov [result], eax ; in result a*b 
        
        ; Print the result
        push dword [result]     ; Push the value of result
        push dword result_msg   ; Push the format string
        call [printf]           ; Call printf
        add esp, 8              ; Clear parameters from the stack
        
        
        
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
