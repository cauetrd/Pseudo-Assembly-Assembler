sum_array:
 
macro &array, &sum, &label
    input &array 
    input &array+1
    input &array+ 2 
    load &array 
    add &array + 1
    add &array +2
    jmpn &label
    store &sum 
    endmacro
avg: macro &A, &B  
    load &a 
    div tres 
    store &b 
    endmacro 


lbl: 

sum_array n, soma, lbl 
avg soma, result 
output result 
stop 
n: 



space 3
soma: space 
result: 
space 
tres: const 3