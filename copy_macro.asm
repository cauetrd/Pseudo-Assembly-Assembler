test: macro &a, &b, &c 
copy &a 
copy 
copy &a, &b, &c 
right: copy &a, &b 
endmacro 

lbl:
test  x,y,z,a 
a: space 
x: const 5 
y: space 
z: space 