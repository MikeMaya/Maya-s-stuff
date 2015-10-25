segment .data
	handleConsola			dd	1				;Primer argumento para la llamada al sistema _WriteConsoleA()	
	longitudCadena 			dd 	1				;tercer argumento 
	caractEscritos			dd 	1				;Cuarto argumento 
	caractLeidos			dd 	1				;Cuarto argumento 
	ultimoArgumento			dd 	1				;Quinto argumento
	cad1 db 	'Ingrese la primer cadena:', 0xA 		
	cad2 db 	'Ingrese la siguiente cadena:', 0xA 	
	cad3 db 	'Cadena concatenada:', 0xA 	
	cad4 db 	0xA,'Cadena invertida:', 0xA 	
	cad5 db 	0xA,'La longitud es: ', 0xA 	
	tama 	db	 0d
	cont 	db   0d

segment	.bss
	cadena  resb   4			; usada para lectura
	aux 	resb   4			; usada para impresion	
	cadf 	resb 500
	cadIn	resb 500
	cadl 	resb 50	

segment .text	
	global _main	
	extern _GetStdHandle@4							;Acceso externo a la llamada al sistema _GetStdHandle()
	extern _WriteConsoleA@20						;Acceso externo a la llamada al sistema _WriteConsoleA()
	extern	_ReadConsoleA@20
	extern _ExitProcess@4	

_main:
	;mostramos el primer mensaje
	push dword -11							
	call _GetStdHandle@4					
	mov [handleConsola],eax					
	xor eax,eax								
	mov eax,26d								
	mov [longitudCadena],eax				
	xor eax,eax								
	mov eax,0d								
	mov [ultimoArgumento],eax				
	push dword [ultimoArgumento]
	push dword caractEscritos
	push dword [longitudCadena]
	push dword cad1
	push dword [handleConsola]
	call _WriteConsoleA@20

	;leemos la primer cadena
	xor	eax,eax
	push dword -10							
	call _GetStdHandle@4					
	mov [handleConsola],eax	
	xor		eax,eax
	mov		eax,50d
	mov		[longitudCadena],eax
	xor		eax,eax
	mov		eax,0d
	mov		[ultimoArgumento],eax
	push	dword [ultimoArgumento]
	push	dword caractLeidos
	push	dword [longitudCadena]
	push	dword cadf
	push	dword [handleConsola]
	call	_ReadConsoleA@20

	mov edi,cadf	
	mov ecx,0
	mov eax,1

	tam:
		mov dl,byte[edi]
		cmp dl,0xD	
		je pre
		inc ecx
		inc edi
		jmp tam
	pre:
		add [tama],ecx

	proc:					;Se piden las siguientes cadenas
		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,29d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cad2
		push dword [handleConsola]
		call _WriteConsoleA@20

		xor	eax,eax
		push dword -10							
		call _GetStdHandle@4					
		mov [handleConsola],eax	
		xor		eax,eax
		mov		eax,50d
		mov		[longitudCadena],eax
		xor		eax,eax
		mov		eax,0d
		mov		[ultimoArgumento],eax
		push	dword [ultimoArgumento]
		push	dword caractLeidos
		push	dword [longitudCadena]
		push	dword cadl
		push	dword [handleConsola]
		call	_ReadConsoleA@20

		mov esi,cadl

	ciclo:			
		mov dl,byte[esi]	
		cmp dl,0xD	
		je verificar										
		mov byte[edi],dl
		inc edi	
		inc esi
		mov ecx,1
		add [tama],ecx
		jmp ciclo

	verificar:
		mov eax,[cont]
		inc eax
		cmp eax,9
		je sig
		mov eax,1
		add [cont],eax
		jmp proc
	
	sig:
		mov esi,cadIn
		xor eax,eax
		mov eax, [tama]
		dec edi
		dec eax
		mov [aux],eax

	invertir:
		mov dl,byte[edi]	
		cmp byte [aux],0d
		je faltante
		mov byte[esi],dl
		inc esi
		dec edi
		mov eax,-1
		add [aux],eax
		jmp invertir

	faltante:
		mov dl,byte[edi]	
		mov byte[esi],dl
		jmp imprimir

	imprimir:
		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,20d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cad3
		push dword [handleConsola]
		call _WriteConsoleA@20

		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,150d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cadf
		push dword [handleConsola]
		call _WriteConsoleA@20

		;mostramos el primer mensaje
		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,19d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cad4
		push dword [handleConsola]
		call _WriteConsoleA@20

		
		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,150d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cadIn
		push dword [handleConsola]
		call _WriteConsoleA@20

	sig2:
		push dword -11							
		call _GetStdHandle@4					
		mov [handleConsola],eax					
		xor eax,eax								
		mov eax,17d								
		mov [longitudCadena],eax				
		xor eax,eax								
		mov eax,0d								
		mov [ultimoArgumento],eax				
		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cad5
		push dword [handleConsola]
		call _WriteConsoleA@20

		cmp byte [tama],100d
	    jge caso3
	    cmp byte [tama],10d
	    jge caso2
	    jmp salir

	    caso2:						;numero de 2 digitos
	    	xor eax,eax
	    	mov eax,[tama]
	    	mov bl,10	
	    	mov dx,0
	    	mov ah,0
	    	div bl
	    	mov [tama],ax
	    	mov [aux],ah

		    mov  ecx, [tama]		;El resultado se guarda en eax, se manda a ecx
		    add  ecx, 48d          	;Se convierte a ASCII
		    mov  [cadena], ecx	    ;Se guarda en la cade
		    xor ecx, ecx
		    mov  ecx, [aux]			;El residuo se guarda en edx, se pasa a ecx
		    add  ecx, 48d           ;Se convierte a ASCII
		    mov  [cadena+1], ecx		;Se guarda el segundo valor
		    
		    xor  edx, edx			;limpio edx
		    xor  eax, eax			;limpio eax	

		    push dword -11							
			call _GetStdHandle@4					
			mov [handleConsola],eax					
			xor eax,eax								
			mov eax,2d								
			mov [longitudCadena],eax				
			xor eax,eax								
			mov eax,0d								
			mov [ultimoArgumento],eax				
			push dword [ultimoArgumento]
			push dword caractEscritos
			push dword [longitudCadena]
			push dword cadena
			push dword [handleConsola]
			call _WriteConsoleA@20
		    jmp salir

	    caso3:						;numero de 3 digitos
	    	xor edx, edx
	    	xor eax,eax

			mov eax,[tama]
	    	mov bl,100	
	    	mov dx,0
	    	mov ah,0
	    	div bl
	    	mov [tama],ax
	    	mov [aux],ah

	    	mov  ecx, [tama]		;El resultado se guarda en eax, se manda a ecx
		    add  ecx, 48d          	;Se convierte a ASCII
		    mov  [cadena], ecx	    ;Se guarda en la cade
		    xor ecx, ecx

		    mov eax,[aux]
	    	mov bl,10	
	    	mov dx,0
	    	mov ah,0
	    	div bl
	    	mov [tama],ax
	    	mov [aux],ah
	    	
	    	mov  ecx, [tama]		;El resultado se guarda en eax, se manda a ecx
		    add  ecx, 48d          	;Se convierte a ASCII
		    mov  [cadena+1], ecx	    ;Se guarda en la cade
		    xor ecx, ecx
		    mov  ecx, [aux]			;El residuo se guarda en edx, se pasa a ecx
		    add  ecx, 48d           ;Se convierte a ASCII
		    mov  [cadena+2], ecx		;Se guarda el segundo valor

		    push dword -11							
			call _GetStdHandle@4					
			mov [handleConsola],eax					
			xor eax,eax								
			mov eax,1d								
			mov [longitudCadena],eax				
			xor eax,eax								
			mov eax,0d								
			mov [ultimoArgumento],eax				
			push dword [ultimoArgumento]
			push dword caractEscritos
			push dword [longitudCadena]
			push dword cadena
			push dword [handleConsola]
			call _WriteConsoleA@20

salir:		
	push dword 0
	call _ExitProcess@4
