INPUT A
INPUT B
INPUT C

; ---- compare A and B ----
LOAD A
SUB B
JMPP AB_OK        ; if A >= B, skip swap
COPY A, AUX
COPY B, A
COPY AUX, B
AB_OK:

; ---- compare A and C ----
LOAD A
SUB C
JMPP AC_OK        ; if A >= C, skip swap
COPY A, AUX
COPY C, A
COPY AUX, C
AC_OK:

; ---- compare B and C ----
LOAD B
SUB C
JMPP BC_OK        ; if B >= C, skip swap
COPY B, AUX
COPY C, B
COPY AUX, C
BC_OK:

; ---- print all numbers ----
OUTPUT A
OUTPUT B
OUTPUT C

STOP

A: SPACE
B: SPACE
C: SPACE
AUX: SPACE
