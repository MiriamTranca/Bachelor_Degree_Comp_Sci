bits 32 
global start        
extern exit, fopen, fclose, fscanf, printf              ; Tell NASM that these functions exist
import exit msvcrt.dll    
import fopen msvcrt.dll 
import fscanf msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 

segment data use32 class=data
    file_name db "input.txt", 0              ; File name to open
    access_mode db "r", 0                    ; Mode to open the file (read mode)
    file_descriptor dd -1                    ; File descriptor initialized to -1
    format db "%d", 0                        ; Format specifier for fscanf
    number dd 0                              ; Variable to store the number read from file

segment code use32 class=code
    start:
        ; Open file
        push dword access_mode            ; Push access mode for fopen
        push dword file_name             ; Push file name for fopen
        call [fopen]                         ; Call fopen
        add esp, 8                           ; Clean up the stack after the call
        
        cmp eax, 0                            ; Check if fopen returned NULL (error)
        je final                             ; Jump to final if fopen failed
        mov [file_descriptor], eax          ; Store file descriptor
        
        mov ecx, 0                           ; Initialize loop counter (not really used here)
    read_loop: 
        ; Read integer from file (fscanf)
        push dword number                    ; Push pointer to the number variable
        push dword format                    ; Push format string for fscanf
        push dword [file_descriptor]         ; Push file descriptor
        call [fscanf]                        ; Call fscanf
        add esp, 12                          ; Clean up the stack after the call
        
        cmp eax, 1                           ; Check if fscanf returned EOF (end of file)
        jne out_loop                          ; Jump out of loop if EOF
        
        ; Print the number read (printf)
        push dword [number]                  ; Push number to print
        push dword format                    ; Push format string
        call [printf]                        ; Call printf
        add esp, 8                           ; Clean up the stack after the call
        jmp read_loop                        ; Repeat the loop
    
    out_loop:
        ; Close the file (fclose)
        push dword [file_descriptor]         ; Push file descriptor to fclose
        call [fclose]                        ; Call fclose
        add esp, 4                           ; Clean up the stack
        
    final:
        ; Exit the program
        push dword 0                         ; Push exit status (0)
        call [exit]                          ; Call exit to terminate the program
