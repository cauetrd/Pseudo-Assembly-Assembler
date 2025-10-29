; test_norm_plus_expressions.asm
; test plus normalization in various contexts
LOAD A+B
STORE C  +  D
ADD E+F
SUB G   +   H
JMP X+1
JMPN Y  +  2
A: CONST 10
B: CONST 1
C: CONST 20
D: CONST 2
E: CONST 30
F: CONST 3
G: CONST 40
H: CONST 4
X: CONST 50
Y: CONST 60