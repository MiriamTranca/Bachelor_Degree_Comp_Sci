;A text file is given. Read the content of the file, count the number of vowels and display the result on the screen. The name of text file is defined in the data segment.

;A text file is given. Read the content of the file, count the number of consonants and display the result on the screen. The name of text file is defined in the data segment.

bits 32 
global start        
extern exit, fread, fopen, fclose, printf              
import exit msvcrt.dll 
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
   
segment data use32 class=data
   file_name db "input_ex1.txt", 0 ;name of the file 
   access_mode db "r", 0 ;opens a file for reading, it must exist 
   file_descriptor dd -1 ; here we save the file descriptor
   nr_vowels dd 0 
   nr_consonants dd 0 
   vowels db "aeiouAEIOU" , 0 
   format db "The number of vowels is %d, of consonants is %d ,", 0 
   len equ 100 ; maximum number of characters read from the file in one step 
   buffer resb len ;where the part read from the file in one step will be put in 
   
segment code use32 class=code
    start:
        ;open the file 
        ;in eax we will have the file_descriptor
        ;eax = fopen(file_name, access_mode) 
        push dword access_mode ;the address
        push dword file_name 
        call [fopen] 
        add esp, 4*2 ; clean the stack 
        
        ;verify if the file was opened (if eax !=0)
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax ; saving the value of the file_descriptor 
        
        ;loop for reading the file 
        loop_read:
            ;reading the first 100 characters 
            ;eax = fread(buffer, 1(size of each ch in bytes), len, file_descriptor)
            push dword [file_descriptor] ; the contents 
            push dword len 
            push dword 1
            push dword buffer ; the address 
            call [fread] 
            add esp, 4*4 ; clean stack 
            
            ; eax = number of ch read 
            ; if it is 0 it means we went through the whole file 
            cmp eax, 0 
            je cleanup
            
            ;setup for checking the vowels 
            mov esi, buffer ;start of the buffer 
            mov ecx, eax ;number of ch for the loop
            
            count_vowels: 
                
                mov ebx, 0 
                mov bl, byte[esi] ; load a ch from the buffer in ebx 
                
                ;check if the loaded ch is a vowel 
                mov edi, vowels ;address of the vowels string 
                
                check_vowel_loop: 
                    ;check if we still have vowels to go through 
                    mov al, byte[edi] 
                    cmp al, 0
                    je not_vowel 
                    
                    ;check if the loaded ch is in the vowels string 
                    cmp bl, al
                    je is_vowel 
                    
                    ;contiune the loop 
                    inc edi ;to go to the next vowel 
                    jmp check_vowel_loop
                    
                is_vowel: 
                    inc dword [nr_vowels]
                    
                not_vowel:
                    inc dword [nr_consonants]
                    inc esi ;move to the next char in the buffer 
                    dec ecx
                    jnz count_vowels
            jmp loop_read
        
        cleanup: 
            ; call fclose to close the file 
            ;fclose(file_descriptor)
            push dword [file_descriptor]
            call [fclose]
            add esp, 4 
        
            ;display result 
            ;printf(format, nr_vowels, nr_consonants)
            push dword [nr_consonants]
            push dword [nr_vowels] ; the content 
            push dword format 
            call [printf]
            add esp, 4*2 ;clean stack
        
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
