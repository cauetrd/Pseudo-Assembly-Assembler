divisivel: macro &a, &B
load &a
div &b 
mult &b 
sub &a 



                jmpz sim  
                jmp nao 



                endmacro
main: input a 
input b 
divisivel a, B

one: const 1 
nao: output zero 
jmp repeat
FIM: stop 
repeat:  input again 
load again
jmpp Main
JMP FIM 
sim: output one 
jmp repeat 
a: space 
b: space 
zero: const 0
again: space