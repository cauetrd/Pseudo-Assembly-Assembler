; Test cases for COPY semantic errors (undefined symbols)

; Test 1: Undefined symbol in first argument
COPY UNDEFINED1, B

; Test 2: Undefined symbol in second argument
COPY A, UNDEFINED2

; Test 3: Undefined symbol in expression (first part)
COPY UNDEFINED3 + 1, B

; Test 4: Undefined symbol in expression (second part)  
COPY A + 1, UNDEFINED4 + 2

; Test 5: Multiple undefined symbols
COPY UNDEFINED5 + 1, UNDEFINED6 + 2

; Test 6: Mix of defined and undefined
COPY A + 1, UNDEFINED7

; Test 7: Valid case - all symbols defined
COPY A + 1, B + 2

STOP

A: SPACE 1
B: SPACE 1