;Problem: A file name is given (defined in the data segment). Create a file with the given name, then read numbers from the keyboard and write only the numbers divisible by 7 to file, until the value '0' is read from the keyboard.
bits 32
global start        
extern exit, fopen, fclose, scanf, fprintf
import exit msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll 
import fprintf msvcrt.dll  

segment data use32 class=data
    file_name db "file_hw8.txt", 0   
    access_mode db "w", 0        ; w - creates an empty file for writing
    file_descriptor dd -1       ; variable to hold the file descriptor
    n dd  0       ; in this variable we'll store the value read from the keyboard
    format  db "%d", 0  ; base 10

segment code use32 class=code
start:
    ; eax = fopen(file_name, access_mode)
    push dword access_mode     
    push dword file_name
    call [fopen]
    add esp, 4*2                

    mov [file_descriptor], eax  ; store the file descriptor returned by fopen
    
    ; if file cannot be opened jump to final 
    cmp eax, 0
    je final
    
    ;read the numbers from the keyboard
    read_numbers:
        push dword n                ; push the address of n 
        push dword format           ; push the format string for scanf
        call [scanf]                ; call scanf to read an integer
        add esp, 4*2                
    
        ; check if the number is 0 to exit the loop
        cmp dword [n], 0
        je final          
    
        ;see if number is divisible by 7
        mov eax, [n]                
        mov edx, 0                 
        mov ecx, 7              
        div ecx                      ; eax = eax / ecx, edx = eax % ecx
        cmp edx, 0                  ; the number is divisible by 7
        je write_to_file            ; jump to write_to_file 
    
        ; skip writing the number and continue reading if not divisible by 7
        jmp read_numbers            
    
        write_to_file:
            push dword [n]                
            push dword format           
            push dword [file_descriptor]
            call [fprintf]              
            add esp, 4*3                
    
            ; continue reading numbers
            jmp read_numbers            
    
    final:
    ; close the file
    push dword [file_descriptor]
    call [fclose]
    add esp, 4

    ; Exit the program
    push dword 0                ; Exit code 0
    call [exit]                 ; Exit the program

