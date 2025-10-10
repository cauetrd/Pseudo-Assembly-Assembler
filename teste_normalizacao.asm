; Teste de normalização de expressões
ADD N+2          ; Deve virar: ADD N + 2
SUB A   -   3    ; Deve virar: SUB A - 3  
LOAD B+1         ; Deve virar: LOAD B + 1
STORE C  -  5    ; Deve virar: STORE C - 5
JMP LOOP+10      ; Deve virar: JMP LOOP + 10
COPY X,Y+2       ; Deve virar: COPY X, Y + 2
INPUT A  ,  B-1  ; Deve virar: INPUT A, B - 1
STOP

N: SPACE
A: CONST 10
B: CONST 20
C: SPACE 5
