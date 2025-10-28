; test_norm_multiple_spaces.asm
; test multiple spaces around commas and plus signs
COPY A  ,   B
LOAD X   +    1
STORE Y+2
COPY   C,D
A: CONST 10
B: CONST 20
X: space 3
Y: space 3
C: CONST 30
D: CONST 40
