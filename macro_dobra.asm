DOBRA: MACRO OP
    LOAD OP
    ADD OP
    STORE OP
ENDMACRO

ABS_DOBRA: MACRO OP, &a
    LOAD OP
    JMPP &a + 12
    JMPZ &a + 12
    LOAD ZERO
    SUB OP
    STORE OP
    DOBRA OP
ENDMACRO

INPUT A
INPUT B

; --- calcula o módulo dos dois números ---
dobra_a: ABS_DOBRA A, dobra_a 
dobra_b: ABS_DOBRA B, dobra_b

; --- agora verifica qual é o maior ---
LOAD A
SUB B
JMPP A_MAIOR
JMPZ IGUAIS
OUTPUT b 
jmp fim 
A_MAIOR: OUTPUT A
JMP FIM

IGUAIS: 
OUTPUT zero 

FIM: STOP

; ======= VARIÁVEIS =======
A: SPACE
B: SPACE
ZERO: CONST 0

; ======= MACROS =======
