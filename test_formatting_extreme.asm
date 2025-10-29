; Teste de formatação extrema e casos limites

; Linhas vazias no meio do código


; Labels isolados seguidos de instruções
ISOLATED_LABEL:

    ADD VAR1

ANOTHER_LABEL:


    SUB VAR2

; Teste com apenas espaços e tabs em linhas
    	    
		
    	  	

; Labels com case mixing extremo
lOwErCaSe_LaBel: CONST 42
UPPERCASE_LABEL: space 1

; Expressões com espaçamento extremo
ADD    VAR1    +    10
SUB    VAR2    -    5
COPY    VAR1   ,   VAR2   +   1
MULT    VAR1    +    2

; Comentários com caracteres especiais
; Comentário com símbolos: @#$%^&*()
; Comentário com números: 123456789
; Comentário vazio:
;

; Instruções com argumentos complexos
JMP ISOLATED_LABEL + 5
JMPZ ANOTHER_LABEL - 2
JMPP lOwErCaSe_LaBel + 1
JMPN UPPERCASE_LABEL

; Input/Output tests
INPUT VAR1
OUTPUT VAR2
INPUT VAR1 + 0
OUTPUT VAR2 - 0

STOP

VAR1: SPACE 3
VAR2: CONST 100