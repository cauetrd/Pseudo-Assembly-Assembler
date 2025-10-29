; Test comprehensive COPY scenarios
A: SPACE 10
B: SPACE 5
C: SPACE 
D: SPACE 

; === BASIC COPY OPERATIONS ===
; Variables defined before use
START: COPY A,      B          ; Basic copy
       COPY C,D          ; Another basic copy

; === COPY WITH EXPRESSIONS ===
; Both operands with expressions
       COPY A + 1, B + 2  ; Both with offsets
       COPY A + 5, B      ; First with offset
       COPY A, B + 3      ; Second with offset

; === VARIABLES DEFINED AFTER USE (FORWARD REFERENCES) ===
       COPY X, Y          ; Forward references
       COPY X + 1, Y + 1  ; Forward with expressions
       COPY Z, W + 10     ; Mixed forward

; === DIFFERENT COMMA STYLES ===
       COPY A,B           ; No spaces around comma
       COPY A , B         ; Space before comma
       COPY A, B          ; Space after comma
       COPY A , B         ; Spaces both sides

; === EXPRESSION COMMA STYLES ===
       COPY A + 1,B + 2   ; No spaces
       COPY A + 1 , B + 2 ; Space before comma
       COPY A + 1, B + 2  ; Space after comma
       COPY A + 1 , B + 2 ; Spaces both sides

       STOP

; === VARIABLE DEFINITIONS ===


; Forward referenced variables
X: space 5
Y: SPACE 5
Z: space 5
W: SPACE 5