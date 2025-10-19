square: macro &a, &B 
LOAD &A 
    MULT &A 
    STORE &B 
    ENDMACRO 
    INPUT N 
    COPY ZERO, RESULT 
    LOOP:   LOAD N 
JMPZ FIM
SQUARE N, TEMP 
LOAD RESULT
ADD TEMP 
STORE RESULT 
LOAD N 
SUB ONE 
STORE N 
JMP LOOP 
FIM: OUTPUT result 
    stop 
    n: space 
    temp: space 
    one: const 1 
    zero: const 0
    result: space
