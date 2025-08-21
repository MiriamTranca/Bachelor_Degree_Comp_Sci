;A text file is given. Read the content of the file, determine the digit with the highest frequency and display the digit along with its frequency on the screen. The name of text file is defined in the data segment.

;A text file is given. Read the content of the file, determine the lowercase letter with the highest frequency and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.

;A text file is given. Read the content of the file, determine the uppercase letter with the highest frequency and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.

;A text file is given. Read the content of the file, determine the special character with the highest frequency and display the character along with its frequency on the screen. The name of text file is defined in the data segment.
bits 32 
global start        
extern exit, printf, fopen, fclose, fread               
import exit msvcrt.dll    
import printf msvcrt.dll 
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 

segment data use32 class=data
    file_name db "input_ex1.txt", 0
    access_mode db "r", 0 
    file_descriptor dd -1 
    
    result_letter dd 0 
    result_freq dd 0 
    
    current_letter dd 0 
    current_freq dd 0
    
    format db "letter %c , frequency %d", 0 
    
    len equ 100 
    buffer resb 100
    length_buffer dd 0 
    
    mes db "out", 0
    
segment code use32 class=code
    start:
        ;open file 
        ;eax = fopen(file_name, access_mode)
        push dword access_mode 
        push dword file_name
        call [fopen]
        add esp, 8 
        
        cmp eax, 0 ; check if the file is opened 
        je final
        
        mov [file_descriptor], eax 
        
        ;read file 
        ;eax = fread(buffer, 1, len, file_descriptor)
        push dword [file_descriptor] 
        push dword len 
        push dword 1 
        push dword buffer 
        call [fread] 
        add esp, 16 
        
        mov [length_buffer], eax
        
        mov ecx, 'z' 
        
        check_freq:
            mov [current_letter], ecx 
            push ecx 
            mov esi, buffer 
            mov ecx, [length_buffer]; for the next loop
            
            check_for_letter:
                mov eax, 0
                lodsb ; in al the char from the buffer 
                cmp eax, [current_letter] 
                jne next
                inc dword [current_freq]
                
                next:
            loop check_for_letter 
            pop ecx ; restoring ecx for the next loop 
            
            ;check if the frequency is bigger than the biggest frequency
            mov ebx, [current_freq] 
            mov edx, [result_freq]
            cmp ebx, edx 
            jle not_good
                mov dword [result_freq], ebx 
                mov ebx, [current_letter] 
                mov dword [result_letter], ebx 
            not_good:
            mov dword [current_freq], 0
            
            mov ebx, 'a' 
            cmp ebx, ecx 
            je out_loop 
        loop check_freq
        
        out_loop:
            
        ;print 
        ;printf(format, current_letter, current_freq)
        push dword [result_freq]
        push dword [result_letter]
        push dword format
        call [printf]
        add esp, 12
        
        ;close file 
        ;fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final: 
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
