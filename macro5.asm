R: MACRO a24, FAS, FAA, MFA
LOAD A24 
STORE FAS
ADD MFA 
STORE MFA 
COPY MFA, FAA
EndMacro

input a 
r a b c d 
a: const 10 
b: space 
c: space 
d: space