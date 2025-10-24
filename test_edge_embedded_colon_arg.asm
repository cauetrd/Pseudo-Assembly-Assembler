; test_edge_embedded_colon_arg.asm
; Argument contains a colon inside (LABEL:SUF) to see how tokenization and matching handle it
LOAD_ONE: MACRO X
    LOAD X
ENDMACRO

MAIN: LOAD_ONE LABEL:SUF
STOP
LABEL:SUF: CONST 9
