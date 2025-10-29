; test_norm_tabs_spaces_mix.asm
; test tabs mixed with spaces around commas and plus
COPY	A ,	B
LOAD	X +	1
STORE Y	+	2
INPUT	 Z
A: CONST 11
B: CONST 22
X: CONST 6
Y: CONST 9
Z: CONST 0