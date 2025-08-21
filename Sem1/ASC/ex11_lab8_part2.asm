;A file name is given (defined in the data segment). Create a file with the given name, then read words from the keyboard and write those words in the file, until character '$' is read from the keyboard.

;A file name is given (defined in the data segment). Create a file with the given name, then read numbers from the keyboard and write those numbers in the file, until the value '0' is read from the keyboard.

bits 32 
global start   
     
extern exit,fclose,fprintf,fopen,printf,scanf    
           
import exit msvcrt.dll 
import fclose msvcrt.dll 
import fprintf msvcrt.dll 
import fopen msvcrt.dll 
import printf msvcrt.dll 
import scanf msvcrt.dll  


segment data use32 class=data
    file_name db "input_ex1.txt", 0
    access_mode db "w", 0 
    len equ 101 
    number dd 0
    file_descriptor dd -1
    prompt db "Enter a number: ", 0
    format db "%d", 0
    
segment code use32 class=code
    start:
        ;open the file 
        ;eax = fopen(file_name, access_mode) 
        push dword access_mode 
        push dword file_name
        call [fopen]
        add esp, 8
        
        ;check if file opened 
        cmp eax, 0 
        je final 
        
        mov [file_descriptor], eax
        
        read_loop: 
            ; print prompt 
            push dword prompt
            call [printf]
            add esp, 4
        
            ;read number from keaboard
            push dword number
            push dword format  
            call [scanf]
            add esp, 8
        
            ;check if number is 0 
            mov eax, [number]
            cmp eax, 0 
            je close_file
            
            ;write to the file
            push dword [number]
            push dword format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 12
            
            jmp read_loop
            
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
