; Comprehensive COPY instruction test case
; Testing all possible conditions and edge cases

; ========== BASIC ARGUMENT COUNT TESTS ==========

; Zero arguments (should be syntax error)
COPY

; One argument (should be syntax error)
COPY A
COPY A,

; Two arguments (valid cases)
COPY A,   B
COPY A,B
COPY A   ,B
COPY  A  ,  B  

; More than two arguments (should be syntax error)
COPY A, B, C
COPY A,B,C,D
COPY A, B, C, D, E

; ========== EXPRESSION TESTS ==========

; Valid expressions
COPY A + 1, B
COPY A, B + 2
COPY A + 3, B + 4
COPY A+1, B+2
COPY A + 5 , B + 6

; Invalid expressions (should be syntax error)
COPY A+, B
COPY A, B+
COPY A + , B
COPY A , B + 

; ========== COMMA POSITIONING TESTS ==========

; Consecutive commas (should be syntax error with empty operand)
COPY A,,B
COPY A,,,B
COPY A,,,,B

; Leading/trailing commas
COPY ,A,B
COPY A,B,
COPY ,A,B,

; Multiple spaces around commas
COPY A  ,  ,  B
COPY A   ,   B
COPY A,   B
COPY A   , B

; ========== LEXICAL ERROR TESTS ==========

; Invalid variable names (should be lexical error)
COPY 123, B
COPY A, 456
COPY 1A, B2
COPY A-B, C
COPY A@, B#
COPY A$, B%

; Valid variable names with underscores
COPY A_1, B_2
COPY _VAR1, _VAR2

; ========== SEMANTIC ERROR TESTS ==========

; Undefined variables (should create pendencies, resolved later)
COPY UNDEFINED1, UNDEFINED2

; ========== MACRO TESTS ==========

; Define a macro with COPY
MACRO_WITH_COPY: MACRO ARG1, ARG2
    COPY #1, #2
    COPY #1 + 1, #2 + 2
ENDMACRO

; Use the macro
MACRO_WITH_COPY A, B
MACRO_WITH_COPY C, D

; Macro with problematic COPY calls
PROBLEM_MACRO: MACRO ARG1
    COPY #1
    COPY #1,
    COPY #1, , B
ENDMACRO

PROBLEM_MACRO TEST_VAR

; ========== COMPLEX CASES ==========

; Mixed valid and invalid on same line concepts
LABEL1: COPY A, B
LABEL2: COPY C + 1, D + 2

; Copy with labels as operands
COPY LABEL1, LABEL2

; ========== EDGE CASES ==========

; Empty tokens and whitespace
COPY   A   ,   B   
COPY	A	,	B	

; Very long expressions
COPY VERY_LONG_VARIABLE_NAME_1, VERY_LONG_VARIABLE_NAME_2
COPY VERY_LONG_VARIABLE_NAME_1 + 999, VERY_LONG_VARIABLE_NAME_2 + 888

; Case sensitivity (should all be uppercase after preprocessing)
copy a, b
Copy A, B
COPY a, B

; ========== PROGRAM CONTROL ==========
STOP

; ========== VARIABLE DEFINITIONS ==========
A: CONST 10
B: CONST 20
C: CONST 30
D: CONST 40
VERY_LONG_VARIABLE_NAME_1: CONST 100
VERY_LONG_VARIABLE_NAME_2: CONST 200
A_1: CONST 11
B_2: CONST 22
_VAR1: CONST 33
_VAR2: CONST 44
TEST_VAR: CONST 55
UNDEFINED1: CONST 99
UNDEFINED2: CONST 88