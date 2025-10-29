; Test COPY with forward and backward references
SECTION TEXT

; === FORWARD REFERENCES (variables defined after use) ===
START: COPY FORWARD1, FORWARD2         ; Both forward
       COPY FORWARD3 + 1, FORWARD4     ; Forward with expression
       COPY FORWARD5, FORWARD6 + 2     ; Forward with expression
       COPY FORWARD7 + 3, FORWARD8 + 4 ; Both forward with expressions

; === BACKWARD REFERENCES (variables defined before use) ===
       COPY BACKWARD1, BACKWARD2        ; Both backward
       COPY BACKWARD1 + 1, BACKWARD2    ; Backward with expression
       COPY BACKWARD1, BACKWARD2 + 2    ; Backward with expression  
       COPY BACKWARD1 + 3, BACKWARD2 + 4 ; Both backward with expressions

; === MIXED REFERENCES ===
       COPY BACKWARD1, FORWARD9         ; Backward, forward
       COPY FORWARD10, BACKWARD2        ; Forward, backward
       COPY BACKWARD1 + 1, FORWARD11 + 2 ; Mixed with expressions
       COPY FORWARD12 + 3, BACKWARD2 + 4 ; Mixed with expressions

       STOP

; === BACKWARD DEFINITIONS (before use) ===
BACKWARD1: CONST 100
BACKWARD2: SPACE 1

; === FORWARD DEFINITIONS (after use) ===  
FORWARD1: CONST 200
FORWARD2: SPACE 1
FORWARD3: CONST 300
FORWARD4: SPACE 1
FORWARD5: CONST 400
FORWARD6: SPACE 1
FORWARD7: CONST 500
FORWARD8: SPACE 1
FORWARD9: CONST 600
FORWARD10: CONST 700
FORWARD11: SPACE 1
FORWARD12: CONST 800