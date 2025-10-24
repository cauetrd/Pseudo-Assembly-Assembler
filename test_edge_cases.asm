; Teste de casos extremos e edge cases

; Teste 1: Labels em linhas separadas
LABEL1:
ADD N1

LABEL2:
    SUB N2

; Teste 2: Múltiplos espaços e tabs
    	   LOAD   	  A   	  
STORE     B    	

; Teste 3: Labels com underscore (válidos)
VAR_1: CONST 10
_LABEL: SPACE 2
VAR_WITH_NUMBERS_123: SPACE

; Teste 4: Expressões complexas com espaços irregulares
JMP   LABEL1  +  5
LOAD  VAR_1   -   2
COPY  A  +  1  ,  B  -  3

; Teste 5: Comentários em diferentes posições
ADD A ; comentário no fim
; comentário linha inteira
    ; comentário com espaços
LOAD B ; outro comentário

; Teste 6: Mistura de maiúsculas e minúsculas
jmp Label1
LoAd VaR_1
sToRe b

; Teste 7: SPACE com argumentos
ARRAY: SPACE 10
MATRIX: SPACE 100

; Teste 8: CONST com valores
PI: CONST 314
ZERO: CONST 0
NEGATIVE: CONST -50

; Teste 9: Instruções de salto
LOOP:
    INPUT VAR_1
    JMPZ END
    JMPP POSITIVE
    JMPN NEGATIVE_NUM
    JMP LOOP

POSITIVE:
    OUTPUT VAR_1
    JMP END

NEGATIVE_NUM:
    SUB ZERO
    OUTPUT ZERO
    
END:
    STOP

N1: CONST 5



N2: 


CONST 6
A: SPACE
B: SPACE