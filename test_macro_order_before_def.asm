; A calls B but B is defined later
A: MACRO
    B
ENDMACRO

; Call A (B not defined yet)
A

; Now define B after A
B: MACRO
    LOAD X
ENDMACRO

X: SPACE
