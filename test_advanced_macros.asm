; Teste de macros avançadas - casos extremos

; Macro com comentários internos
MACRO_WITH_COMMENTS: MACRO X, Y
    LOAD X      ; carrega primeiro parâmetro
    ADD Y       ; soma segundo parâmetro
    ; comentário no meio da macro
    STORE RESULT ; armazena resultado
ENDMACRO

; Macro aninhada - uma macro chama outra
SAVE_VAR: MACRO VAR
    LOAD VAR
    STORE BACKUP
ENDMACRO

RESTORE_AND_ADD: MACRO VAR, VALUE
    SAVE_VAR VAR
    ADD VALUE
    STORE VAR
ENDMACRO

; Macro com espaços irregulares na definição
  SPACED_MACRO  :   MACRO   A  ,  B  
	LOAD   A
	    SUB    B
	STORE   TEMP
  ENDMACRO

; Teste de expansão com labels
LOOP_MACRO: MACRO COUNT
    LOAD COUNT
    JMPZ END_LOOP
    SUB ONE
    STORE COUNT
    JMP LOOP_START
END_LOOP:
ENDMACRO

; Código principal
LOOP_START:
    MACRO_WITH_COMMENTS NUM1, NUM2
    RESTORE_AND_ADD NUM1, INCREMENT
    SPACED_MACRO NUM2, NUM1
    LOOP_MACRO COUNTER
    STOP

; Variáveis
NUM1: CONST 10
NUM2: CONST 5
INCREMENT: CONST 1
COUNTER: CONST 3
RESULT: SPACE
BACKUP: SPACE
TEMP: SPACE
ONE: CONST 1