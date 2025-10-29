; Teste de macro que chama outra macro
; Macro simples para carregar um valor
LOAD_VALUE: MACRO VAR, var2 
    LOAD VAR
    store var2 
ENDMACRO

; Macro que usa a macro LOAD_VALUE
DOUBLE_LOAD: MACRO X, Y
    LOAD_VALUE X,        y 
    LOAD_VALUE Y,     x
ENDMACRO
A: CONST 10
B: CONST 20
; Programa principal
DOUBLE_LOAD A B
STOP


