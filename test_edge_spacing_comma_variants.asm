; test_edge_spacing_comma_variants.asm
; Call macro with various spacing around commas to verify comma-preservation logic
COPY_TWO: MACRO P, Q
    COPY #1, #2
ENDMACRO

MAIN: COPY_TWO A,B
MAIN2: COPY_TWO A ,B
MAIN3: COPY_TWO A, B
MAIN4: COPY_TWO A , B
STOP
A: CONST 5
B: CONST 6
