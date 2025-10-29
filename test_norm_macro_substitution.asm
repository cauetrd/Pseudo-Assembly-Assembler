; test_norm_macro_substitution.asm
; macro substitutes an expression containing '+', ensure normalization after expansion
INCMACRO: MACRO X
LOAD X+1
ENDMACRO

INCMACRO A
A: CONST 3
