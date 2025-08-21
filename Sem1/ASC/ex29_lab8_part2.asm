;A text file is given. The text file contains numbers (in base 10) separated by spaces. Read the content of the file, determine the maximum number (from the numbers that have been read) and write the result at the end of file.

bits 32
global start
extern exit,fclose,fscanf,fopen,fprintf
import exit msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll


segment data use32 class=data

nume_fisier db "29.txt", 0
mod_acces db "a", 0
descriptor dd -1
format db "%d", 0
text dd 0
max dd -1

segment code use32 class=code

start:
        
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp,4*2
    mov [descriptor],eax
    
    cmp eax,0
        je final
   
    mov ecx,100
    repeta:
        push dword text
        push dword format
        push dword [descriptor]
        call [fscanf]
        add esp,4*3
        
        mov ebx, [text]
        cmp ebx,[max]
            jle maimic
        mov [max], ebx
        maimic:
    loop repeta
    
    push dword [max]
    push dword format
    push dword [descriptor]
    call [fprintf]
    add esp,4*3
    
    push dword [descriptor]
    call [fclose]
    add esp,4*1
    
    final:
push dword 0
call [exit]