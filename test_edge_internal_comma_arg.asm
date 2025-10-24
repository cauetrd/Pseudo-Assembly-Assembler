; test_edge_internal_comma_arg.asm
; Pass an argument that itself contains a comma (A,B) to a macro parameter
PRINT_TWO: MACRO X, Y
    OUTPUT X
    OUTPUT Y
ENDMACRO

MAIN: PRINT_TWO A,B, c
STOP
A,B: CONST 1
c: CONST 2
