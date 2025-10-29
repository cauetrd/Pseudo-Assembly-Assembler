; Test COPY lexical errors (invalid variable names)

; === INVALID VARIABLE NAMES ===
START: COPY 1A, B        ; Variable starts with digit
       COPY A, 2B        ; Variable starts with digit
       COPY 123, B       ; All digits first operand
       COPY A, 456       ; All digits second operand
       
; === SPECIAL CHARACTERS ===
       COPY A-B, C       ; Invalid character (hyphen)
       COPY A, B@C       ; Invalid character (@)
       COPY A.B, C       ; Invalid character (.)
       COPY A, B#C       ; Invalid character (#)
       COPY A$, B        ; Invalid character ($)
       COPY A, B%        ; Invalid character (%)

; === WITH EXPRESSIONS ===
       COPY 1A + 2, B    ; Invalid var with expression
       COPY A + 1, 2B    ; Invalid var with expression
       COPY A-B + 1, C   ; Invalid var with expression
       COPY A, B@C + 5   ; Invalid var with expression

; === BOTH OPERANDS INVALID ===
       COPY 1A, 2B       ; Both invalid
       COPY A-B, C@D     ; Both invalid with special chars

       STOP
1A: SPACE
A: CONST 1
B: CONST 2
C: CONST 3