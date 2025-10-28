; test_edge_macro_punct.asm
; macro argument that looks like it contains a comma but should be treated as single arg
PRINTMACRO: MACRO MSG
OUTPUT MSG
ENDMACRO

PRINTMACRO HELLO,WORLD
HELLO,WORLD: CONST 42