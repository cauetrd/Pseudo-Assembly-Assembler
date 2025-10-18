; Teste de macro que chama outra macro
; Macro simples para carregar um valor
LOAD_VALUE: MACRO VAR
    LOAD VAR
ENDMACRO

; Macro que usa a macro LOAD_VALUE
DOUBLE_LOAD: MACRO X Y
    LOAD_VALUE X
    LOAD_VALUE Y
ENDMACRO

; Programa principal
DOUBLE_LOAD A B
STOP

A: CONST 10
B: CONST 20
