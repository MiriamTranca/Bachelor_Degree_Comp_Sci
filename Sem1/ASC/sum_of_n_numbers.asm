bits 32                         
segment code use32 public code
global _sum_of_first_n_numbers

_sum_of_first_n_numbers:
	; int sum_of_the_first_n_numbers(int n)
	; INPUT:
	;	n - the number of numbers to compute the sum of
	;
	; OUTPUT:
	;	- an integer, DWORD, representing the sum of the first n numbers, starting from 1

	; create the stack frame
	push ebp
	mov ebp, esp

	; the sum will be in eax 
	mov eax, 0
	mov ecx, [ebp + 8] ;the first argument
	
	.sum_loop: 
		add eax, ecx ;eax = eax+ecx
        dec ecx
        jnz .sum_loop ; will repeat the loop until ecx is 0

	; free the stack frame
	mov esp, ebp
	pop ebp

	ret
