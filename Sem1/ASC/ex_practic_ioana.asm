;Read a 100 characters string from the keyboard. The string contains a hidden message.
;The message was hidden by turning each letter in its ASCII code (in base 16).
;Write in a file the original message in a file. The original message does not contain spaces or digits.

bits 32 
global start        
extern exit, scanf, fprintf, fopen, fclose              
import exit msvcrt.dll    
import scanf msvcrt.dll 
import fprintf msvcrt.dll 
import fopen msvcrt.dll 
import fclose msvcrt.dll 

segment data use32 class=data
    text resb 101 ; where we put the text read from the keyboard
    decoded_mes resb 101
    
    file_name db "output.txt", 0 ; name of the output file 
    mode_access db "w", 0 ; the access mode is write 
    file_descriptor dd -1 ; here will store the descriptor of the file 
    
    format db "%s", 0 ; in string 
    
segment code use32 class=code
    start:
        ;read from the keyboard 
        ;scanf(format, text) 
        push dword text 
        push dword format 
        call [scanf]
        add esp, 8
        
        mov esi, text ;source pointer 
        mov edi, decoded_mes ; destination pointer 
        mov ecx, 0 ;index counter 
        mov ebx, 0
        
        decode_loop: 
            mov al, byte [esi+ecx] ;load char from source 
            cmp al, 0 ;check for null terminator 
            je get_out
           
            ;convert hex char to a number 
            sub al, '0' ; for ascii values '0'-'9' 
            cmp al, 9 
            jle hex_valid_digit
            sub al, 7 ;ascii values between 'A'-'F' 
            hex_valid_digit: 
                shl al, 4 ; make space for the next hex char 
                
            ;read 2nd hex char 
            inc ecx 
            mov ah, byte [esi + ecx] 
            sub ah, '0' 
            cmp ah, 9 
            jle hex_2_valid_digit 
            sub ah, 7 
            
            hex_2_valid_digit: 
            or al, ah 

            mov byte [edi+ebx], al 
            inc ebx
            
            inc ecx 
            jmp decode_loop
            
        
        get_out:
        mov byte[edi +ecx], 0 ;null-terminnate the decoded string 
        
        ;open or create the file 
        ;eax = fopen(file_name, mode_access) 
        push dword mode_access 
        push dword file_name 
        call [fopen]
        add esp, 8 
        
        ;if the file cannot be opened go to the final
        cmp eax, 0 ; in eax the file descriptor 
        je final
        
        mov [file_descriptor], eax
        
        ;write in the file 
        ;fprintf(file_descriptor, format_output, text)
        push dword decoded_mes 
        push dword format 
        push dword [file_descriptor]
        call [fprintf]
        add esp, 12
        
        ;close the file 
        ;fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
