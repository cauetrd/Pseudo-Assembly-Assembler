sum_array: macro &array, &sum 
    load &array 
    add &array+1
    add &array+2
    store &sum 
    endmacro
avg: macro &A, &B  
    load &a 
    div tres 
    store &b 
    endmacro

sum_array n, soma
avg soma, result 
output result 
stop 
n: 



space 3
soma: space 
result: space 
tres: const 3