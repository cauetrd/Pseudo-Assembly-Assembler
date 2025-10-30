; Test COPY syntax errors
SECTION TEXT

; === TOKEN COUNT ERRORS ===
START: COPY              ; Too few tokens (1)
       COPY A            ; Too few tokens (2)  
       COPY A B          ; Missing comma (2 args but no comma)
       COPY A, B, C      ; Too many basic args (5 tokens but wrong pattern)
       COPY A + B + C, D ; Too many operators (6 tokens)
       COPY A, B + C + D ; Too many operators (6 tokens)

; === PLUS SIGN POSITION ERRORS ===
       COPY +, B         ; Plus in wrong position
       COPY A, +         ; Plus in wrong position  
       COPY A B +, C     ; Plus in wrong position (5 tokens)
       COPY A, B C +     ; Plus in wrong position (5 tokens)
       COPY + A, B + C   ; Plus at start (5 tokens)
       COPY A + B +, C   ; Two plus signs (5 tokens)
       COPY A B + C +, D ; Wrong plus positions (7 tokens)
       COPY A +, B + C + ; Multiple plus errors (7 tokens)

; === COMMA ERRORS ===
       COPY A B          ; Missing comma
       COPY , B          ; Missing first operand
       COPY A ,          ; Missing second operand
       COPY A,, B        ; Double comma
       COPY A, , B       ; Space comma space

       STOP

SECTION DATA
A: CONST 1
B: CONST 2  
C: CONST 3
D: CONST 4