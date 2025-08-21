;Read two numbers a and b (in base 10) from the keyboard and determine the order relation between them (either a < b, or a = b, or a > b). Display the result in the following format: "<a> < <b>, <a> = <b> or <a> > <b>".

bits 32
global start        
extern exit, printf, scanf                
import exit msvcrt.dll   
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0 
    b dd 0 
    format db "%d", 0 
    prompt1 db "a= ", 0
    prompt2 db "b= " , 0
    mes1 db "%d < %d", 0
    mes2 db "%d > %d", 0 
    mes3 db "%d = %d", 0    
    
segment code use32 class=code
    start:
        ;print prompt a 
        push dword prompt1 
        call [printf]
        add esp, 4 
        
        ;read a 
        push dword a 
        push dword format 
        call [scanf]
        add esp, 8 
        
        ;print prompt b 
        push dword prompt2
        call [printf]
        add esp, 4 
        
        ;read b 
        push dword b  
        push dword format 
        call [scanf]
        add esp, 8 
        
        mov eax, [a] 
        mov ebx, [b] 
        
        cmp eax, ebx 
        je print_mes3 
        ja print_mes1 
        jb print_mes2 
        
        print_mes1:
            push dword [a] 
            push dword [b] 
            push dword mes1
            call [printf]
            add esp, 12
            jmp exit_program
            
        print_mes2:
            push dword [a] 
            push dword [b] 
            push dword mes2
            call [printf]
            add esp, 12
            jmp exit_program
            
        print_mes3:
            push dword [b] 
            push dword [a] 
            push dword mes3
            call [printf]
            add esp, 12
            jmp exit_program
        
        exit_program:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
