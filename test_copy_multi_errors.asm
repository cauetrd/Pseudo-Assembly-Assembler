; Test multiple operands - should show syntax error but compile all
COPY A, B, C
; Test empty operand - should show syntax error  
COPY A, , B
; Test normal case - should work fine
COPY X, Y
STOP
A: CONST 1
B: CONST 2
C: CONST 3
X: CONST 4
Y: CONST 5