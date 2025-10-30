; Comprehensive test for two-argument instructions (COPY)
; Testing all valid and invalid cases

; ========== VALID CASES ==========

; Basic valid cases
COPY A, B
COPY VAR1, VAR2
COPY X, Y

; Valid with expressions
COPY A + 1, B
COPY A, B + 2
COPY A + 3, B + 4

; Valid with spacing variations
COPY A,B
COPY A ,B
COPY A, B
COPY A , B
COPY  A  ,  B  

; ========== INVALID CASES - SYNTAX ERRORS ==========

; Zero arguments
COPY

; One argument
COPY A
COPY VAR1

; One argument with trailing comma
COPY A,
COPY VAR1,

; More than two arguments
COPY A, B, C
COPY A, B, C, D
COPY X, Y, Z

; Consecutive commas (missing operands)
COPY A,, B
COPY A,,, B
COPY A,,,, B
COPY , A, B
COPY A, , B

; Multiple trailing commas
COPY A, B,
COPY A, B,,
COPY A, B,,,

; Complex consecutive comma cases
COPY A,, B,
COPY A,,, B,,
COPY , A,, B,

; ========== INVALID CASES - LEXICAL ERRORS ==========

; Invalid identifiers (should be lexical errors, not syntax)
COPY 123A, B
COPY A, 456B
COPY A@, B
COPY A$, B%
COPY A-B, C
COPY A.B, C

; ========== INVALID CASES - EXPRESSION ERRORS ==========

; Invalid + usage (should be syntax errors)
COPY A+, B
COPY A, B+
COPY A +, B
COPY A, B +
COPY +A, B
COPY A, +B

; ========== EDGE CASES ==========

; Valid edge cases
COPY _VAR, _VAR2
COPY VAR_1, VAR_2
COPY A1, B2

; Mixed errors (lexical + syntax)
COPY A,, 123B
COPY 456A,, B,

STOP