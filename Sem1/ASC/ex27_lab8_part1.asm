;A character string is given (defined in the data segment). Read one character from the keyboard, then count the number of occurences of that character in the given string and display the character along with its number of occurences.
bits 32
global start  
extern exit, scanf, printf              
import exit msvcrt.dll   
import scanf msvcrt.dll 
import printf msvcrt.dll 
 
segment data use32 class=data
    string db "ana are 4 mere si o para.", 0
    number_of_char equ $-string
    char db 0                      ; Character input by the user
    format_scan db "%c", 0         ; Format for reading a character
    format_print db "The character '%c' appears %d times.", 0
    result dd 0                    ; Store the count (32-bit)

segment code use32 class=code
    start:
        ; Read one character from the keyboard
        push dword char
        push dword format_scan
        call [scanf]
        add esp, 8

        ; Initialize counters
        mov ecx, number_of_char    ; Length of the string
        xor ebx, ebx               ; Counter for occurrences
        mov esi, string            ; Pointer to the start of the string
        
    find_char:
        mov al, [esi]              ; Load the current character
        cmp al, 0                  ; Check if null terminator
        je end_loop                ; Exit if end of string
        cmp al, [char]             ; Compare with input character
        jne continue_loop
        inc ebx                    ; Increment the counter if match
    continue_loop:
        inc esi                    ; Move to the next character
        loop find_char             ; Decrement ecx and repeat if not zero
        
    end_loop:
        mov [result], ebx          ; Store the result

        ; Display the result
        push dword [result]        ; Push count
        push dword [char]          ; Push character
        push dword format_print    ; Push format string
        call [printf]
        add esp, 12                ; Clean up the stack

        ; Exit the program
        push dword 0               ; Return code 0
        call [exit]
