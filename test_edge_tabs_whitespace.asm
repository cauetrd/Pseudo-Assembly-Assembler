; test_edge_tabs_whitespace.asm
; Contains literal tabs and mixed spaces to confirm normalization
TAB_MACRO: MACRO        X
	OUTPUT          X
ENDMACRO

START:    TAB_MACRO	A
	TAB_MACRO	B
STOP
A: CONST 10
B: CONST 20
