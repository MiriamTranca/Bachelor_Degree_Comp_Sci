;Read two numbers a and b (in base 10) from the keyboard and calculate a/b. This value will be stored in a variable called "result" (defined in the data segment). The values are considered in signed representation.
bits 32 
global start     
extern exit , printf, scanf              
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
  
segment data use32 class=data
    a dd 0 
    b dd 0 
    result dd 0
    message1 db "Give a: ", 0 
    message2 db "Give b: ", 0
    message3 db "The result is: %d", 10, 0
    format db "%d" ; a and b are in base 10    
    
    
segment code use32 class=code
    start:
        ;print message1 
        ;printf(message1)
        push dword message1 
        call [printf]
        add esp, 4 ; clear the stack 
        
        ;read from the keyboard and store in a the first number 
        ;scanf(format, a)
        push dword a ; the address of a 
        push dword format 
        call [scanf]
        add esp, 8
        
        ;print message2 
        ;printf(message2)
        push dword message2 
        call [printf]
        add esp, 4 ; clear the stack 
        
        ;read from the keyboard and store in b the second number 
        ;scanf(format, b)
        push dword b ; the address of b 
        push dword format 
        call [scanf]
        add esp, 8
        
        ;doing the division
        
        mov edx, 0 
        mov eax, [a] ; moving in edx:eax the contents of a 
        
        mov ebx, [b] ; moving in ebx the contents of b 

        div ebx ; in eax we have a/b  
        
        mov [result], eax ; moving in result a/b
            
        ;print the result 
        ;printf(message3, result) 
        push dword [result]
        push dword message3
        call [printf] 
        add esp, 8 
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
