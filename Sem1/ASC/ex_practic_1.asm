;Se citeste din fisier un sir de numere.
;a)	Sa se calculeze suma, produsul numerelor, pozitiile maximului. 
;b)	Sa se sorteze sirul de numere.
;c)	Sa se scrie sirul de numere in baza doi intr-un alt fisier.

bits 32

extern exit, fscanf, fopen, printf, fclose, fprintf
import exit msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

global start

segment data use32 class=data

    a db 1
    b db 2

    file_descriptor dd -1
    file_name db "input.txt", 0
    access_mode db "r", 0
    
    integer_format db "%d", 0
    number dd 0
    
    number_array resd 100
    array_length dd 0
    
    sum dd 0
    product dd 1
    
    curr_max dd 0
    max_apps dd 0
    max_positions resd 255
    
    print_sum_and_product_message db "The sum is: %d and the product is: %d", 10, 13, 0
    print_max_and_positions db "The maximum is %d and the positions are: ", 0
    
    output_file db "output.txt", 0
    write_format db "w", 0
    string_format db "%s ", 0
    
    binary_buffer resb 255

segment code use32 class=code

    base2:
        push ebp
        mov ebp, esp
        
        mov ebx, dword [ebp + 8] ; buf
        mov eax, dword [ebp + 12] ; no
        
        sub esp, 4
        mov dword [ebp - 4], 2 ; two constant
        
        mov ecx, 0
        .division_loop:
            mov edx, 0
            div dword [ebp - 4]
            
            push edx
            inc ecx
            cmp eax, 0
            jnz .division_loop
        
        mov edi, ebx
        cld
        jecxz .end_create_number
        .create_number:
            pop eax
            add eax, '0'
            
            stosb
            
            loop .create_number
        .end_create_number:
        
        mov byte [edi], 0
        
        mov esp, ebp
        pop ebp
        
        ret

    sort_array:
    
        ; create the stack frame
        push ebp
        mov ebp, esp
        
        sub esp, 4 ; reserve some space
        
        mov ebx, [ebp + 8] ; arr
        mov edx, [ebp + 12] ; len
        
        mov dword [ebp - 4], edx
        
        ; for int i = 0; i < len; i++
        mov ecx, 0
        .outer_loop:
            push ecx
            
            ; for int j = 0; j < len; j++
            mov ecx, 1
            .inner_loop:
                
                ; if ebx[ecx - 1] > ebx[ecx], swap
                mov edx, dword [ebx + (ecx - 1) * 4]
                cmp edx, dword [ebx + ecx * 4]
                jl .end_branch
                
                mov eax, dword [ebx + (ecx - 1) * 4]
                xchg eax, dword [ebx + ecx * 4]
                mov dword [ebx + (ecx - 1) * 4], eax
                
                .end_branch:
                
                inc ecx
                cmp ecx, dword [ebp - 4]
                jnb .end_inner_loop
                jmp .inner_loop
            .end_inner_loop:
            
            pop ecx
            
            inc ecx
            cmp ecx, dword [ebp - 4]
            jnb .end_outer_loop
            jmp .outer_loop
            
        .end_outer_loop:
        
        
        mov esp, ebp
        pop ebp
        
        ret


    start:
        ; eax = fopen(file, access_mode)
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        jne file_is_valid
        
        ; if file is not valid
        push dword -1
        call [exit]
        
        file_is_valid:
        mov dword [file_descriptor], eax
        
        mov ecx, 0
        mov edi, number_array
        reading_loop:
            pusha
        
            ; eax = fscanf(file_descriptor, format, number)
            push dword number
            push dword integer_format
            push dword [file_descriptor]
            call [fscanf]
            add esp, 4 * 3
            
            
            ; if eax == -1, break
            cmp eax, -1
            jz end_reading_loop
            
            popa
            mov eax, dword [number]
            cld
            stosd ; [edi++] = eax; creating the array
            
            inc ecx
            jmp reading_loop
            
        end_reading_loop:
        ; pop the values
        popa
        
        mov dword [array_length], ecx
        
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        
        ; a)
        mov ecx, dword [array_length]
        jecxz end_computation_loop
        computation_loop:
            mov eax, dword [number_array + (ecx - 1 ) * 4]
            mov ebx, eax
        
            ; add to the sum
            add dword [sum], eax
            
            mov eax, dword [product]
            imul ebx ; in this case we'll only take into consideration the lower part of the quad word
            mov dword [product], eax
            
            ; compare the max
            cmp ebx, dword [curr_max]
            jl maximum_check_end
            je equal_case
            
            ; new maximum
            mov dword [curr_max], ebx
            mov dword [max_apps], 1
            
            mov edi, max_positions
            mov eax, ecx
            stosd
            
            jmp maximum_check_end
            
            equal_case:
            inc dword [max_apps]
            mov eax, ecx
            stosd
            
            
            maximum_check_end:
            loop computation_loop
        
        end_computation_loop:
        
        ; printf(print_sum_and_product_message, su, product)
        push dword [product]
        push dword [sum]
        push dword print_sum_and_product_message
        call [printf]
        add esp, 4 * 3
        
        
        ; printf(print_max_and_positions, max)
        push dword [curr_max]
        push dword print_max_and_positions
        call [printf]
        add esp, 4 * 2
        
        ; print the positions
        mov ecx, dword [max_apps]
        mov esi, max_positions
        jecxz end_print_loop
        print_max_positions_loop:
            lodsd ; eax = [esi ++]
            
            pusha
            
            ; printf(integer_format, eax)
            push eax
            push dword integer_format
            call [printf]
            add esp, 4 * 2
            
            popa
            loop print_max_positions_loop
        
        end_print_loop:
        
        
        ; b)
        ; sort_array(number_array, len)
        push dword [array_length]
        push dword number_array
        call sort_array
        add esp, 4 * 2
        
        ; c)
        ; eax = fopen(output_file, write_format)
        push dword write_format
        push dword output_file
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        jnz valid_output_file
        
        push dword -1
        call [exit]
        
        valid_output_file:
        mov dword [file_descriptor], eax
        
        mov esi, number_array
        mov ecx, dword [array_length]
        cld
        jecxz end_binary_print_loop
        binary_print_loop:
            lodsd ; eax = [esi++]
            
            pusha
            ; base2(buffer, eax)
            push eax
            push dword binary_buffer
            call base2
            add esp, 4 * 2
            
            ; fprintf(file_descriptor, string_format, binary_buffer)
            push dword binary_buffer
            push dword string_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            popa
        
            loop binary_print_loop
        end_binary_print_loop:
        
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        push dword 0
        call [exit]
