; test_norm_macro_arg_commas.asm
; macro defined with two params; call with "A,B" as separate args without spaces
MYMACRO: MACRO X,Y
COPY X,Y
ENDMACRO

MYMACRO A,B
A: CONST 10
B: CONST 20
