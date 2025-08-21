;2.	Se citeste un text din fisier si un character de la tastatura.
;c)	Codificati textul folosind corespondenta ABCD… WXYZ -> CDEF…  YZAB si afisati condificarea intr-un nou fisier.

bits 32 

global start        

extern exit, fopen, fclose, fread, fwrite, printf            
 
import exit msvcrt.dll  
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fwrite msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    fin_descriptor resd 1
    fout_descriptor resd 1
    input_file db "a.txt", 0
    output_file db "b.txt", 0
    accr db "r", 0
    accw db "w", 0
    
    array resb 100
    print_format db "%c", 0
    
segment code use32 class=code
    start:
        
        push dword accr
        push dword input_file
        call [fopen]
        add ESP, 2*4
        
        mov dword[fin_descriptor], EAX
        
        push dword accw
        push dword output_file
        call [fopen]
        add ESP, 2*4
        
        mov dword[fout_descriptor], EAX
        mov EDI, array
        mov ECX, 0
        
        repeat:
            
            push ECX
            push dword[fin_descriptor]
            push 1
            push 1
            push EDI
            call [fread]
            add ESP, 4*4
            pop ECX
            
            cmp EAX, 0
            jz end_repeat
            
            add dword[EDI], 2
            cmp dword[EDI], 'z'
            
            jle Dont_decrease
                sub dword[EDI], 26
            Dont_decrease:
            
            push ECX
            push dword[EDI]
            push dword print_format
            call [printf]
            add ESP, 2*4
            pop ECX
            
            inc ECX
            add EDI, 1
        jmp repeat
        end_repeat:
        
        push dword[fout_descriptor]
        push ECX
        push dword 1
        push dword array
        call [fwrite]
        add ESP, 4*4
        
        push    dword 0     
        call    [exit]    
