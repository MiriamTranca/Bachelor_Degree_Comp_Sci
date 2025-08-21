; Two natural numbers a and b (a, b: dword, defined in the data segment) are given. Calculate a/b and display the quotient and the remainder in the following format: "Quotient = <quotient>, remainder = <remainder>". Example: for a = 23, b = 10 it will display: "Quotient = 2, remainder = 3". The values will be displayed in decimal format (base 10) with sign.

; Two natural numbers a and b (a: dword, b: dword, defined in the data segment) are given. Calculate a/b and display the quotient in the following format: "<a>/<b> = <quotient>". Example: for a = 200, b = 5 it will display: "200/5 = 40". The values will be displayed in decimal format (base 10) with sign.

; Two natural numbers a and b (a: dword, b: dword, defined in the data segment) are given. Calculate a/b and display the remainder in the following format: "<a> mod <b> = <remainder>". Example: for a = 23, b = 5 it will display: "23 mod 5 = 3". The values will be displayed in decimal format (base 10) with sign.


bits 32
global start        

extern exit , printf             
import exit msvcrt.dll
import printf msvcrt.dll  

  
segment data use32 class=data
    a dd 37
    b dd 5
    format db "Quotient = %+d , remainder = %+d", 0
    
segment code use32 class=code
    start:
        mov eax, [a] 
        cdq ; in edx:eax = a
        
        mov ebx, [b]
        
        idiv ebx ; in eax we have a/b, in edx we have a%b
        
        ;print(format, eax, edx)
        push edx
        push eax
        push dword format 
        call [printf]
        add esp, 12
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
