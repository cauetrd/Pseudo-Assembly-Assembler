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


sim: output one 
jmp repeat 
nao: output zero 

repeat:  input again 
load again
jmpp Main
stop 
a: space 
b: space 
one: const 1 
zero: const 0
again: space