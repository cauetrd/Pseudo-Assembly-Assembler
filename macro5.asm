R: MACRO a24, FAS, FAA, MFA
LOAD A24 
STORE FAS
ADD MFA 
STORE MFA 
COPY MFA, FAA
output faa
EndMacro

input b
r a b c d 
stop
a: const 10 
b: space 
c: space 
d: const 20