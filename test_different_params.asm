macro1: macro &x 
    output &x 
    endmacro 
macro2: macro &y, &z 
    copy &y, &z 
    endmacro 

macro1 a 
macro2 a, b
stop 
a:
 space   2
b: space