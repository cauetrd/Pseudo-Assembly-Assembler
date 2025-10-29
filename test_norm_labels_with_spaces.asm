; test_norm_labels_with_spaces.asm
; test normalization with labels and spacing
LABEL1:   COPY A  ,  B
LABEL2:		LOAD X + 1
LABEL3: STORE Y,Z
   LABEL4: ADD P+Q
A: CONST 5
B: CONST 6  
X: CONST 7
Y: CONST 8
Z: CONST 9
P: CONST 10
Q: CONST 11