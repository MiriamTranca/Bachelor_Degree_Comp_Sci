bits 32 

global start        

extern exit, printf, fscanf, fread, fopen, fclose              
import exit msvcrt.dll    
import printf msvcrt.dll
import fscanf msvcrt.dll
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    fin_descriptor resd 1
    input_file db "a.txt", 0
    accr db "r", 0
    cuv resd 10
    
    print_format db "Nr caractere = %d, Nr cuvinte = %d ", 0
    read_format db "%s", 0
    nr_cuv dd 0
    nr_car dd 0
    
segment code use32 class=code
    start:
        
        push dword accr
        push dword input_file
        call [fopen]
        add ESP, 4*2
        
        cmp EAX, 0
        jz final
        
        mov dword[fin_descriptor], EAX
        
        read:
            push dword[fin_descriptor]
            push 1
            push 1
            push dword cuv
            call [fread]
            add ESP, 4*4
            
            cmp EAX, 0
            jz end_read
            
            inc dword[nr_car]
        jmp read
        end_read:
        
        push dword[fin_descriptor]
        call [fclose]
        add ESP, 4
        
        push dword accr
        push dword input_file
        call [fopen]
        add ESP, 4*2
        
        cmp EAX, 0
        jz final
        
        mov dword[fin_descriptor], EAX
                
        read_words:
            push dword cuv
            push dword read_format 
            push dword[fin_descriptor]
            call [fscanf]
            add ESP, 4*3
            
            cmp EAX, -1
            jz end_read_words
            
            inc dword[nr_cuv]
        jmp read_words
        end_read_words:
        
        push dword[nr_cuv]
        push dword[nr_car]
        push dword print_format
        call [printf]
        add ESP, 3*4
        
        push dword[fin_descriptor]
        call [fclose]
        add ESP, 4
        
        final:
        push    dword 0     
        call    [exit]    
