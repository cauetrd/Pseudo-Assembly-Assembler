desvio: macro &a, &b, &label 
input &a 
input &b 
load &a 
add &b 
jmpp &label+ 12
jmp &label 
store result 
output result 
endmacro 
main: 

output tres 
chama: desvio x,   y,chama 
input again 
load again 
jmpp main 
stop
x: space 
y: space 
result: space
tres: const 3
again: space