adding: macro &a, &b 
load &a
add &b
store &b  
mul &b, &a 
output &a  
endmacro 
mul: macro &a, &b 
load &a 
mult &b 
store &b 
endmacro 

input a 
input b 
lbl: 

adding a, b 
stop 
a: space 
b: space