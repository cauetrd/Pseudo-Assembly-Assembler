; Teste mais complexo de macro aninhada
; Macro para operação básica
BASIC_OP: MACRO VAR
    LOAD VAR
    STORE TEMP
ENDMACRO

; Macro que usa BASIC_OP duas vezes
SWAP: MACRO X Y
    BASIC_OP X
    LOAD Y
    STORE X
    LOAD TEMP
    STORE Y
ENDMACRO

; Macro que usa SWAP
DOUBLE_SWAP: MACRO A B C D
    SWAP A B
    SWAP C D
ENDMACRO

; Programa principal
DOUBLE_SWAP NUM1 NUM2 NUM3 NUM4
STOP

NUM1: CONST 1
NUM2: CONST 2
NUM3: CONST 3
NUM4: CONST 4
TEMP: SPACE
