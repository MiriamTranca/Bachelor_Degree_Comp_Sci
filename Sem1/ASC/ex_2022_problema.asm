bits 32 
global start        
extern exit, printf              
import exit msvcrt.dll
import printf msvcrt.dll 
   
segment data use32 class=data
    s1 dw 12abh, 34cdh, 56efh ; first string
    s2 dw 3500h, 0011h, 7ffbh ; second string 
    len equ ($-s2)/2 ; length of the strings
    sd resd len ; array for doublewords
    format_print db "%c", 0 ; format to print characters
    format_end_print db " | ", 0 ; separator between printed doublewords
    number_bits_first db 0 ; bit count for first word
    number_bits_second db 0 ; bit count for second word
    copy_1 dw 0
    copy_2 dw 0
    bin_buffer times 33 db 0 ; buffer to store binary string

segment code use32 class=code
    start:
        mov ecx, len ; loop counter
        mov edi, sd ; address of destination array
        mov esi, s1 ; first string pointer
        mov edx, s2 ; second string pointer
        cld ; clear direction flag
        jecxz final ; if length is 0, exit

    make_numbers:
        lodsw ; load a word from s1 into AX
        mov word[copy_1], ax ; copy for bit counting
        call count_bits
        mov [number_bits_first], al ; store count
        
        mov ax, [edx] ; load a word from s2
        mov word[copy_2], ax
        call count_bits
        mov [number_bits_second], al
        
        ; Compare bit counts to order bytes
        mov al, [number_bits_first]
        cmp al, [number_bits_second]
        jbe order_correct ; if s1 has <= bits, keep order

        ; Swap bytes if s1 has more 1s
        xchg ah, al
        
    order_correct:
        stosd ; store the ordered doubleword in sd
        add edx, 2 ; move to the next word in s2
        loop make_numbers
    
    print_results:
        mov ecx, len
        mov esi, sd
        jecxz final
    
    print_loop:
        lodsd ; load a doubleword
        push eax
        call print_binary
        push format_end_print
        call [printf]
        add esp, 4
        loop print_loop
    
    final:
        push dword 0
        call [exit]
    
count_bits:
    xor al, al ; clear count
bit_loop:
    test word[copy_1], 1
    jz skip_inc
    inc al
skip_inc:
    shr word[copy_1], 1
    jnz bit_loop
    ret

print_binary:
    mov eax, dword[esi] 
    div byte[1] ; in ah the rest
    
binary_loop:
    shl eax, 1
    mov dl, '0'
    jc set_one
    jmp store_bit
set_one:
    mov dl, '1'
store_bit:
    mov [edi], dl
    dec edi
    loop binary_loop
    push bin_buffer
    call [printf]
    add esp, 4
    ret
