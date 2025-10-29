; Test COPY with all valid expression patterns
SECTION TEXT

; === 3 TOKEN PATTERNS (basic) ===
START: COPY A, B          ; Simple copy
       COPY X, Y          ; Another simple copy

; === 5 TOKEN PATTERNS (one expression) ===
       COPY A + 1, B      ; First operand with expression
       COPY A + 10, B     ; First operand with larger number
       COPY A + 255, B    ; First operand with max reasonable offset
       
       COPY A, B + 1      ; Second operand with expression  
       COPY A, B + 10     ; Second operand with larger number
       COPY A, B + 255    ; Second operand with max reasonable offset

; === 7 TOKEN PATTERNS (both expressions) ===
       COPY A + 1, B + 1  ; Both with same offset
       COPY A + 1, B + 2  ; Both with different offsets
       COPY A + 10, B + 20 ; Both with larger offsets
       COPY A + 0, B + 0  ; Both with zero offset
       COPY A + 255, B + 255 ; Both with max offsets

; === EXPRESSION COMBINATIONS ===
       COPY A + 1, Y      ; Expression + simple
       COPY X, B + 1      ; Simple + expression
       COPY X + 5, Y + 10 ; Both expressions, different variables

; === ZERO OFFSETS ===
       COPY A + 0, B      ; Zero offset (should work)
       COPY A, B + 0      ; Zero offset second operand
       COPY A + 0, B + 0  ; Both zero offsets

       STOP

SECTION DATA
A: CONST 100
B: SPACE 1
X: CONST 200  
Y: SPACE 1