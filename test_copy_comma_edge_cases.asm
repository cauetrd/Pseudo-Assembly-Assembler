; Test edge cases and special comma handling
SECTION TEXT

; === EDGE CASE COMMA POSITIONS ===
START: COPY A,B           ; No spaces
       COPY A ,B          ; Space before comma only
       COPY A, B          ; Space after comma only
       COPY A , B         ; Spaces both sides

; === COMMA WITH EXPRESSIONS ===
       COPY A+1,B+2       ; No spaces in expressions
       COPY A + 1,B + 2   ; Spaces in expressions, no space around comma
       COPY A + 1 ,B + 2  ; Space before comma
       COPY A + 1, B + 2  ; Space after comma
       COPY A + 1 , B + 2 ; Spaces around comma

; === TRAILING COMMAS (should be errors) ===
       COPY A, B,         ; Trailing comma
       COPY A + 1, B + 2, ; Trailing comma with expressions

; === LEADING COMMAS (should be errors) ===
       COPY , A, B        ; Leading comma
       COPY , A + 1, B    ; Leading comma with expression

; === MISSING OPERANDS ===
       COPY , B           ; Missing first operand
       COPY A,            ; Missing second operand
       COPY ,             ; Missing both operands

; === MULTIPLE COMMAS ===
       COPY A,, B         ; Double comma
       COPY A, , B        ; Comma space comma
       COPY A,,, B        ; Triple comma

       STOP

SECTION DATA
A: CONST 10
B: SPACE 1