is_prime:
macro &a, &lbl 
copy two, aux2 
load &a 
sub aux2 

OUTPUT auX2 
jmpz &lbl + 34 
load &a
div aux2
mult aux2 
sub &a
jmpz &lbl + 29
load aux2 
add one 
store aux2 
jmp &lbl + 11
copy zero, result 
jmp &lbl+ 37
copy one, result
endmacro
input n 
lbl_macro: 

is_prime n,lbl_macro
output result 
stop
n: space 
two: const 2 
one: 

const 1 
aux2: space 
result:
 space 

 zero: const 0