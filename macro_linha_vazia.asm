; macro_linha_vazia.asm
; Test: macro calling another macro, empty lines and whitespace-only lines,
; and labels defined inside macros. Updated to match assembler syntax.

INNER: MACRO
    ; inner macro body
    AUX: CONST 1

ENDMACRO

OUTER: MACRO
    ; call inner
    INNER

    
    	
    ; line with spaces above (4 spaces) and a tab above
    OUTER_LABEL:
    INNER
ENDMACRO

START: LOAD A
    OUTER
    STOP
A: CONST 10