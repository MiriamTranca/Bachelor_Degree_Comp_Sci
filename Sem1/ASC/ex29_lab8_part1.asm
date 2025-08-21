;Read three numbers a, m and n (a: word, 0 <= m, n <= 15, m > n) from the keyboard. Isolate the bits m-n of a and display the integer represented by those bits in base 16
bits 32
global start        
extern exit, printf, scanf               

segment data use32 class=data
    prompt_a db "Enter a (hex, e.g., 0x12345678): ", 0
    prompt_mn db "Enter m and n (decimal, space-separated): ", 0
    input_a db "%x", 0
    input_mn db "%d %d", 0
    result_msg db "Extracted bits (hex): 0x%x", 10, 0
    a dd 0
    m dd 0
    n dd 0 
    result dd 0
   
segment code use32 class=code
    start:
        ; Prompt for 'a'
        push dword prompt_a
        call printf
        add esp, 4

        ; Read 'a'
        push dword a
        push dword input_a
        call scanf
        add esp, 8

        ; Prompt for 'm' and 'n'
        push dword prompt_mn
        call printf
        add esp, 4

        ; Read 'm' and 'n'
        push dword n
        push dword m
        push dword input_mn
        call scanf
        add esp, 12

        ; Load inputs
        mov eax, [a]        ; eax = a
        mov ecx, [m]        ; ecx = m
        mov ebx, [n]        ; ebx = n

        ; Validate m > n (optional, but recommended)
        cmp ecx, ebx
        jle exit_program

        ; Extract bits m to n
        sub ecx, ebx        ; ecx = m - n
        inc ecx             ; ecx = m - n + 1 (bit count)
        mov edx, 1          ; edx = 1
        shl edx, cl         ; edx = (1 << (m - n + 1))
        dec edx             ; edx = mask for m-n bits
        shl edx, ebx        ; align mask to position n
        and eax, edx        ; isolate m-n bits
        shr eax, ebx        ; shift bits down to LSB
        mov [result], eax   ; store result

        ; Display result
        push dword [result]
        push dword result_msg
        call printf
        add esp, 8

    exit_program:
        ; Exit program
        push dword 0
        call exit
