MACRO1: MACRO &A, &B 
    output &a
    MACRO2 &A, &B 
    load &a 
    mult two 
    endmacro 
    
macro2: MACRO &a, &B 
    load &b 
    store &a 
    endmacro 
lbl: 
    macro1 a b 
    macro1 b a
    stop 
a: space
b: space 
two: const 34