; B defined first, then A calls B
B: MACRO
    LOAD X
ENDMACRO

A: MACRO
    B
ENDMACRO

; Call A (B already defined)
A

X: SPACE
