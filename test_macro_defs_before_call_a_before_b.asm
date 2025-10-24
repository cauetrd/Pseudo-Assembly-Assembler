A: MACRO
    B
ENDMACRO

B: MACRO
    LOAD X
ENDMACRO

; Call A after both defs (A defined before B)
A

X: SPACE
