; Comprehensive single-argument instruction test case
; Testing all possible conditions and edge cases for INPUT, OUTPUT, etc.

; ========== VALID CASES ==========

; Simple valid cases
INPUT A
OUTPUT B
LOAD C
STORE D

; Valid with expressions
INPUT A + 5
OUTPUT B + 10
LOAD C + 1
STORE D + 2

; Valid with underscores and numbers
INPUT VAR_1
OUTPUT _TEST
LOAD ABC123
STORE _VAR_TEST

; ========== INVALID CASES - SYNTAX ERRORS ==========

; No arguments (should be syntax error)
INPUT
OUTPUT
LOAD
STORE
a: space

; Trailing commas (should be syntax error only)
INPUT A,
OUTPUT B,
LOAD C,
STORE D,

; Multiple trailing commas (should be syntax error only)
INPUT A,,
OUTPUT B,,,
LOAD C,,,,
STORE D,,,,,

; More than one argument (should be syntax error)
INPUT A, B
OUTPUT A, B, C
LOAD X, Y
STORE P, Q, R

; Mixed trailing commas and multiple arguments
INPUT A, B,
OUTPUT A,, B
LOAD 1A, B,,
STORE A,, B,,

; ========== INVALID CASES - LEXICAL ERRORS ==========

; Invalid identifiers (should be lexical error)
INPUT 123
OUTPUT 1ABC
LOAD A@B
STORE B#C

; Invalid characters in identifiers
INPUT A$
OUTPUT B%
LOAD C&
STORE D*

; ========== INVALID CASES - SEMANTIC ERRORS ==========

; Undefined variables (should be semantic error)
VAR1: CONST 10
INPUT UNDEFINED_VAR
OUTPUT ANOTHER_UNDEFINED

; Valid reference
INPUT VAR1

STOP

; ========== VARIABLE DECLARATIONS ==========
; Declare all variables used in the tests to avoid semantic errors

A: SPACE
B: SPACE
C: SPACE
D: SPACE
VAR_1: SPACE
_TEST: SPACE
ABC123: SPACE
_VAR_TEST: SPACE
X: SPACE
Y: SPACE
P: SPACE
Q: SPACE
R: SPACE
UNDEFINED_VAR: SPACE
ANOTHER_UNDEFINED: SPACE