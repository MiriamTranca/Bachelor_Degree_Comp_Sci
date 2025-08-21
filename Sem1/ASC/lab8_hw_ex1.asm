;Problem: Read a number in base 10 from the keyboard and display the value of that number in base 16 Example: Read: 28; display: 1C
bits 32 
global start       
extern exit, scanf , printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    n dd 0 ; defining the variable n, in which we will place the number in base 10
    format db "%d", 0 ; defining the format  
    format2 db "%x", 0 ; defining the format for base 16
    
segment code use32 class=code
    start:
        push dword n ; pushing the parameters on the stack in reverse order ; pushing the offset of n
        push dword format
        
        call [scanf] ; calling the function scanf to read the number n in base 10
        
        add esp, 4*2 ; cleaning from the stack 4 bytes for each dword
        
        
        push dword [n] ; pushing the parameters on the stack in reverse order ; pushing the value stored in n 
        push dword format2
        
        call [printf]   ; calling the function printf to print the number n in base 16
        
        add esp, 4*2    ; cleaning from the stack 4 bytes for each dword
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
