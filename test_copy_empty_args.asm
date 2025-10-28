; test_copy_empty_args.asm
; test COPY with empty arguments
COPY ,B
COPY A,
COPY ,
A: CONST 1
B: CONST 2