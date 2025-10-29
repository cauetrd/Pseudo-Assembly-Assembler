; Test cases for mixed COPY errors

; Test 1: Both syntax and lexical errors
COPY A + B C + 123DEF

; Test 2: Syntax error - wrong token count with lexical error
COPY 456ABC + 1, B + 2 + 3

; Test 3: Syntax error - missing '+' with lexical error  
COPY _INVALID 1, B

; Test 4: Edge case - '+' as variable name (lexical error)
COPY +, B

; Test 5: Edge case - numeric constant as variable (lexical error)
COPY 123, 456

; Test 6: Edge case - empty tokens (syntax error)
COPY , B

; Test 7: Valid expressions that should work
COPY A + 5, B + 10

STOP

A: SPACE 1  
B: SPACE 1