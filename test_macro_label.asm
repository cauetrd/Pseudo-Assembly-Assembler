; Teste com labels e macros aninhadas
; Macro simples
SAVE: MACRO VAR
    STORE VAR
ENDMACRO

; Macro com label que chama outra macro
LOAD_AND_SAVE: MACRO SOURCE TARGET
LOOP1: LOAD SOURCE
    SAVE TARGET
ENDMACRO

; Programa principal
    LOAD A
MAIN: LOAD_AND_SAVE B C
    STOP

A: CONST 5
B: CONST 10
C: SPACE
