copy_vec: macro &a, &b 
input_vec &a 
copy &a,&b
copy &a+1,&b + 1 
copy &a+ 2, &b +2 
copy &a+3, &b+3
output_vec &b 
endmacro 

input_vec: 
macro &a 
input &a 
input &a+1 
input &a+2
endmacro 
output_vec: macro x  
output x  
output x+1
output x+2 
endmacro
copy_vec a,b
stop
a: space 3 
b: space 3