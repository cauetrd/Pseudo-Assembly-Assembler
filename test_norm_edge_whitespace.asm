; test_norm_edge_whitespace.asm
; test edge cases with whitespace normalization
COPY A,
COPY ,B
LOAD X+
LOAD +Y
STORE   ,  
ADD  +  
A: CONST 1
B: CONST 2
X: CONST 3
Y: CONST 4