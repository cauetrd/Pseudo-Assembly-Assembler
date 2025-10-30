
; === UNDEFINED VARIABLES ===
START: COPY UNDEFINED1, B    ; First operand undefined
       COPY A, UNDEFINED2    ; Second operand undefined
       COPY UNDEFINED3, UNDEFINED4 ; Both operands undefined

; === UNDEFINED WITH EXPRESSIONS ===
       COPY UNDEFINED5 + 1, B       ; Undefined with expression
       COPY A + 2, UNDEFINED6       ; Undefined with expression  
       COPY UNDEFINED7 + 3, UNDEFINED8 + 4 ; Both undefined with expressions

; === MIX OF DEFINED AND UNDEFINED ===
       COPY A, UNDEFINED9           ; Defined, undefined
       COPY UNDEFINED10, A          ; Undefined, defined
       COPY A + 1, UNDEFINED11 + 2  ; Defined expr, undefined expr

       STOP

A: CONST 10
B: SPACE 1
