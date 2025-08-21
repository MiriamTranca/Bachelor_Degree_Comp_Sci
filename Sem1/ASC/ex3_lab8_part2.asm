;A text file is given. Read the content of the file, count the number of even digits and display the result on the screen. The name of text file is defined in the data segment.

;A text file is given. Read the content of the file, count the number of odd digits and display the result on the screen. The name of text file is defined in the data segment.

bits 32
global start   
extern exit, fopen, fclose, fread, printf               
import exit msvcrt.dll   
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 
import printf msvcrt.dll

segment data use32 class=data
    file_name db "input_ex1.txt", 0
    access_mode db "r", 0 ;opens a file for reading 
    file_descriptor dd -1 ; here we will put the descriptor of the opened file 
    
    nr_even dd 0 ; here we will store the number of even digits from the file 
    nr_odd dd 0 ; here we will store the number of odd digits from the file 
    
    even_digits db "24680", 0 
    odd_digits db "13579", 0
    
    format db "The number of even digits is %d and of odd digits is %d ", 0 ;the format for priting to the screen 
    
    len equ 100 ; for reading from the file 
    buffer resb 100 ; reserving 100 bytes for the buffer 
    
segment code use32 class=code
    start:
        ;open the file 
        ;eax = fopen(file_name, access_mode)
        push dword access_mode ; the address 
        push dword file_name 
        call [fopen]
        add esp, 8 ; clear stack 
        
        cmp eax, 0 ;check if the file was opened correctly 
        je final
        
        mov [file_descriptor], eax 
        
        ;read from file in parts 
        read_file: 
            ;read parts of 100 char 
            ;eax = fread(buffer, 1, len, file_descriptor)
            push dword [file_descriptor] 
            push dword len
            push dword 1 
            push dword buffer
            call [fread]
            add esp, 16 
            
            cmp eax, 0 ;compare if the number of read char was 0 
            je cleanup
            
            mov ecx, eax ; for the loop, the number of char read 
            mov esi, buffer ;the start of the buffer in esi 
            
            count_even: 
            
                mov bl, byte[esi] ; in bl the current char to be checked 
                
                mov edi, even_digits
                
                ;check if the byte in bl is in even_digits
                check_even: 
                    mov al, byte[edi]
                    
                    ;check if we have char to go through 
                    cmp al, 0 
                    je check_next 
                    
                    cmp al, bl ;check if the char is in the string of even digits 
                    je is_even
                    
                    ;continue
                    inc edi
                    jmp check_even
                    
                is_even:
                    inc dword [nr_even] ; increment the number of even digits found  
                    jmp next_char
                    
                check_next:    
                    ;check for odd digits 
                    mov edi, odd_digits
                
                    check_odd: 
                        mov al, byte[edi]
                    
                        cmp al, 0
                        je next_char 
                    
                        cmp al, bl 
                        je is_odd 
                    
                        ;continue 
                        inc edi 
                        jmp check_odd
                    
                    is_odd: 
                        inc dword [nr_odd] 
                        jmp next_char
                    
                    next_char:
                        inc esi 
                        loop count_even
                    
            jmp read_file
            
        cleanup:
            ;close file 
            ;fclose(file_descriptor)
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
            ;display the result 
            ;printf(format, nr_even, nr_odd)
            push dword [nr_odd] ; the contents 
            push dword [nr_even] 
            push dword format
            call [printf] 
            add esp, 12 
            
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
