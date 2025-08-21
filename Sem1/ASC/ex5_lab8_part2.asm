;A text file is given. Read the content of the file, count the number of special characters and display the result on the screen. The name of text file is defined in the data segment.
;32–47 / 58–64 / 91–96 / 123–126
;less than 100 characters
bits 32 
global start        
extern exit , fopen, fclose, fread, printf              
import exit msvcrt.dll    
import fopen msvcrt.dll
import fclose msvcrt.dll 
import fread msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    file_name db "input_ex1.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1 ;where we put the descriptor of the file 
    
    nr_spec_char dd 0 
    
    format db "Number of special character is %d ", 0
    
    len equ 100
    buffer resb 100 
    
segment code use32 class=code
    start:
        ;open file 
        ;eax = fopen(file_name, access_mode)
        push dword access_mode 
        push dword file_name 
        call [fopen]
        add esp,8
        
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax 
        
        ;read from file 
        ;eax = fread(buffer, 1, len, file_descriptor)
        push dword [file_descriptor] 
        push dword len  
        push dword 1 
        push dword buffer 
        call [fread]
        add esp, 16
        
        ;move the start buffer in esi
        mov esi, buffer 
        mov ecx, eax 
        
        check_loop: 
            ;check if the ascii code is between 32 and 47
            cmp byte[esi], 32 
            jb not_special
            cmp byte[esi], 47
            jbe is_special
            
            ;check if the ascii code is between 58 and 64
            cmp byte[esi], 58 
            jb not_special 
            cmp byte[esi], 64
            jbe is_special
           
            ;check if the ascii code is between 91 and 96
            cmp byte[esi], 91
            jb not_special 
            cmp byte[esi], 96
            jbe is_special
            
            ;check if the ascii code is between 123 and 126
            cmp byte[esi], 123 
            jb not_special 
            cmp byte[esi], 126
            jbe is_special
            
            is_special:
                inc dword [nr_spec_char]
            
            not_special:
                inc esi
                loop check_loop
                
        display:
            ;printf(format, nr_spec_char)
            push dword [nr_spec_char]
            push dword format
            call [printf]
            add esp, 8
            
        close_file:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
            
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
