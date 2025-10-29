; Teste de três níveis de aninhamento
; Nível 1: Macro básica
BASE: MACRO X
    LOAD X
ENDMACRO

; Nível 2: Macro que chama BASE
MIDDLE: MACRO Y Z
    BASE Y
    STORE Z
ENDMACRO

; Nível 3: Macro que chama MIDDLE
TOP: MACRO A B C D
    MIDDLE A B
    MIDDLE C D
ENDMACRO

; Programa principal
TOP VAR1 VAR2 VAR3 VAR4
STOP

VAR1: CONST 100
VAR2: SPACE
VAR3: CONST 200
VAR4: SPACE
