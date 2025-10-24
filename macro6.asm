Sum: MACRO &A, &B, &C
    LOAD &A
    ADD &B
    ADD &C
    copy &a, &b 
    STORE &A
ENDMACRO

chama: 
macro &a, &b, &c 
output &a
sum &a, &b, &c 
endmacro
    
chama X, Y, Z
STOP

X: CONST 1
Y: CONST 2
Z: CONST 3
RESULT: SPACE