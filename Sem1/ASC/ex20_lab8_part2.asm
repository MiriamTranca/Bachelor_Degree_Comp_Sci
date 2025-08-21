;A file name and a text (defined in the data segment) are given. The text contains lowercase letters and spaces. Replace all the letters on even positions with their position. Create a file with the given name and write the generated text to file.

;A file name and a text (defined in the data segment) are given. The text contains lowercase letters, digits and spaces. Replace all the digits on odd positions with the character ‘X’. Create the file with the given name and write the generated text to file.

bits 32
global start
extern exit,fclose,fprintf,fopen
import exit msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data

nume_fisier db "input_ex1.txt", 0
mod_acces db "w", 0
descriptor dd -1
text db "ana", 0
len equ $-text-1
text2 times len db 0

segment code use32 class=code

par:
    mov dl,bl
    clc
    shr dl,1
        jc dupa
    mov al,bl
    add al,'0'
    dupa:
ret

start:
        
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp,4*2
    mov [descriptor],eax
    
    cmp eax,0
    je final

    mov ecx,len
    mov edi,text2
    mov esi,text
    mov bx,0
    repeta:
        lodsb
        cmp al,' '
            je urm1
        call par
        urm1:
        inc bl
        stosb
    loop repeta
    
    push dword text2
    push dword [descriptor]
    call [fprintf]
    add esp,4*2
    
    push dword [descriptor]
    call [fclose]
    add esp,4*1
    
    final:
push dword 0
call [exit]