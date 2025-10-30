First: MACRO X,   Y
    LOAD X
    Second y, x 
ENDMACRO
Second: MACRO x,Y
    ADD x
    STORE Y
ENDMACRO
A: SPACE


First A,b
STOP

b: const 3