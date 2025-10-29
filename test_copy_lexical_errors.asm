; Test cases for COPY lexical errors

; Test 1: Invalid variable name in first argument
COPY 123ABC, B

; Test 2: Invalid variable name in second argument  
COPY A, 456DEF

; Test 3: Invalid variable name in expression (first part)
COPY _INVALID_, B

; Test 4: Invalid variable name in expression (second part)
COPY A, &INVALID

; Test 5: Invalid variable name in complex expression (first variable)
COPY 9VAR + 1, B

; Test 6: Invalid variable name in complex expression (second variable)
COPY A + 1, @VAR + 2

; Test 7: Multiple lexical errors
COPY 1ABC + 2, 3DEF + 4

; Test 8: Valid case for comparison - should have no lexical errors
COPY A + 1, B + 2

STOP

A: SPACE 1
B: SPACE 1