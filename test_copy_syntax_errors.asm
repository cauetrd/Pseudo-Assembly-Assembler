; Test cases for COPY syntax errors

; Test 1: Too many arguments (8 tokens)
COPY A + 1, B + 2 + 3

; Test 2: Wrong number of arguments (4 tokens)
COPY A, B C

; Test 3: Wrong number of arguments (6 tokens)  
COPY A + 1 B + 2

; Test 4: 5 tokens but '+' in wrong position (tokens: COPY A 1 + B - '+' in position 4, should be 3)
COPY A 1 + B

; Test 5: 7 tokens but '+' in wrong position (tokens: COPY A 1 + B 2 + C - second '+' in position 6, should be 5)  
COPY A + 1, B 2 + C

; Test 6: 7 tokens but first '+' in wrong position (tokens: COPY A 1 + B + 2 - first '+' in position 4, should be 3)
COPY A 1 +, B + 2

; Test 7: Missing comma between arguments (5 tokens without comma)
COPY A + 1 B

STOP

A: SPACE 1
B: SPACE 1
C: SPACE 1