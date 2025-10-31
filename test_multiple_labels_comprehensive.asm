; Teste com múltiplas labels na mesma linha e em linhas diferentes
; Cenário 1: 2 labels na mesma linha
L1: L2: ADD X

; Cenário 2: 3 labels na mesma linha
M1: M2: M3: SUB Y

; Cenário 3: 4 labels na mesma linha
P1: P2: P3: P4: MULT Z

; Cenário 4: 5 labels na mesma linha
Q1: Q2: Q3: Q4: Q5: DIV W

; Cenário 5: 6 labels na mesma linha
R1: R2: R3: R4: R5: R6: LOAD V

; Cenário 6: Label única (normal, sem erro)
A_NORMAL: STORE U

; Cenário 7: Label em linha separada seguida de instrução
B_LABEL:
INPUT T

; Cenário 8: Duas labels em linhas separadas
C_LABEL:
D_LABEL:
OUTPUT S

; Cenário 9: Label repetida (deve dar erro semântico)
L1: JMPZ FINAL

; Cenário 10: Definição de variáveis com labels normais
X: CONST 10
Y: CONST 20
Z: CONST 30
W: CONST 5
V: CONST 15
U: SPACE
T: SPACE
S: SPACE

; Cenário 11: Label final
FINAL: STOP
