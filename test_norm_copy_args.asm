; test_norm_copy_args.asm
; test normalization with COPY instruction multiple arguments
COPY A,B
COPY   C  ,  D
COPY E,   F  
COPY   G   ,   H
A: CONST 1
B: SPACE 1
C: CONST 2
D: SPACE 1  
E: CONST 3
F: SPACE 1
G: CONST 4
H: SPACE 1