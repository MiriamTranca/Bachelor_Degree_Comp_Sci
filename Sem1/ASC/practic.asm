bits 32
global start        
extern exit, fopen, fread, printf, fclose, fscanf               
import exit msvcrt.dll    
import fopen msvcrt.dll 
import fread msvcrt.dll 
import printf msvcrt.dll 
import fclose msvcrt.dll 
import fscanf msvcrt.dll 
                         
                         
                         
segment data use32 class=data
    file_name db "input.txt", 0 
    access_mode db "r", 0 ;we read from the file 
    
    file_descriptor dd -1 ; here we will have the file descriptor

    format db "%x", 0
    number dd 0
    
    copy_number dd 0 
    
    output_format db "Number: %d ", 0 
    
    number_bits_0 dd 0
    output_format_2 dd "Bits: %d ", 0
    
    
segment code use32 class=code
    start:
        ;open the file 
        ;eax = fopen(file_name, access_mode) 
        push dword access_mode 
        push dword file_name 
        call [fopen]
        add esp, 8 
        
        ;check if file was opened correct 
        cmp eax, 0 
        je final 
        
        mov [file_descriptor], eax 
        
        read_loop:
            ;eax = fscanf(file_descriptor, format, number) 
            push dword number 
            push dword format 
            push dword [file_descriptor]
            call [fscanf]
            add esp, 12
            
            cmp eax, -1 ;if done with the reading by comparing eof
            je out_read_loop
            
            mov eax, [number] 
            
            and eax, 1 ; masking the last bit 
            cmp eax, 0 ;checking if it is an even number
            jne not_printing
            
            ;print numbers to see if it works 
            ;printf(format, number) 
            push dword [number] 
            push dword output_format 
            call [printf]
            add esp, 8
            
            
            mov eax, [number]
            mov ecx, 0 ;the number of shifts
            number_of_0:
                cmp eax, 0 ; if we went through the whole number 
                je out_of_number
                
                shr eax, 1
                
                mov edx, eax 
                and edx, 1; masking the last bit
                cmp edx, 0; checking if the bit is zero
                jne not_adding
                
                mov ebx, [number_bits_0] ;incrementing the number of bits
                inc ebx 
                
                not_adding:
                
                jmp number_of_0
                
            out_of_number:
            ;print number of bits 0 
            ;printf(format, number_bits_0)
            
            push dword [number_bits_0]
            push dword output_format_2
            call [printf]
            add esp, 8
            
            
            not_printing:
                jmp read_loop
            
        out_read_loop:
        
        ;close file 
        ;fclose(file_descriptor)
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
    final:    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
