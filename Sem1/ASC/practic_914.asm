bits 32 
global start        

extern exit, printf, fopen,fread,fclose, scanf                
import exit msvcrt.dll    
import printf msvcrt.dll 
import fopen msvcrt.dll 
import fread msvcrt.dll 
import fclose msvcrt.dll 
import scanf msvcrt.dll

segment data use32 class=data
    mes_1 db "Give file name: ", 0
    file_name resb 100 
    format_input db "%s", 0
    access_mode db "r", 0 
    file_descriptor dd -1
    
    mes_2 db "Give n: ", 0
    n dd 0 
    format_n db "%d", 0 
    
    format_txt db "%h", 0
    text resb 100
    len equ 100
    
    number_bits dd 0 
    
    length_txt dd 0
    
    
segment code use32 class=code
    start:
        ;print mes_1 
        ;printf(mes_1) 
        push dword mes_1
        call [printf] 
        add esp, 4
        
        ;read file name 
        ;scanf(format_input,file_name)
        push dword file_name 
        push dword format_input
        call [scanf]
        add esp, 8 
        
        ;print mes_2
        ;printf(mes_2) 
        push dword mes_2
        call [printf] 
        add esp, 4
        
        ;read number
        ;scanf(format_n,n)
        push dword n
        push dword format_n
        call [scanf]
        add esp, 8 
        
        ;eax = fopen(file_name, access_mode) 
        push dword access_mode 
        push dword file_name 
        call [fopen] 
        add esp, 8 
        
        ;see if file opened 
        cmp eax, 0 
        je final
        
        mov [file_descriptor], eax 
        
        ;read from file into text 
        ;eax = fread(text,1, len, file_descriptor) 
        push dword [file_descriptor] 
        push dword len 
        push dword 1
        push dword text 
        call [fread] 
        add esp, 16 
        
        mov ebx, eax ; the length of the char
        
        mov esi, text 
        
        loop_check_bit: 
            cmp ebx, 0 
            je out_loop 
            
            lodsb ; esi inc, al the char from text 
            
            mov cl, [n] ; moving into ecx the number of the bit we need to check
            
            shr al, cl
            and al, 1
            
            cmp al, 1 ;check if the last bit is 1
            jne not_one
            
            inc dword[number_bits]
            
            
            not_one:
            dec ebx  
            
            jmp loop_check_bit 
            
        out_loop:
        
        ;print number_bits 
        push dword [number_bits]
        push dword format_n
        call [printf] 
        add esp, 8 
        
        ;fclose(file_descriptor) 
        push dword [file_descriptor] 
        call [fclose]
        add esp, 4
        
        final:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
