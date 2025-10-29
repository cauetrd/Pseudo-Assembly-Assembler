; test_norm_nested_macro.asm
; test normalization in nested macro calls
OUTER: MACRO X, Y
INNER X+1, Y
ENDMACRO

INNER: MACRO A, B
COPY A,B
LOAD A + 1
ENDMACRO

OUTER VAL1+2  ,  VAL2
VAL1: CONST 100
VAL2: CONST 200