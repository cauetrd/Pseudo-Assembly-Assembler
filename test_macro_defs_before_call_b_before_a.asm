B: MACRO
    LOAD X
ENDMACRO

A: MACRO
    B
ENDMACRO

; Call A after both defs (B defined before A)
A

X: SPACE
