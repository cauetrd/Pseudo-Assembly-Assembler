
mAcro2: MACRO &a, &bfsaf
    load &bfsaf 
    store &a 
    endmacro 
    
    
    MACRO1: MACRO &A, &B 
    output &a
    MACRO2 &A, &B 
    load &a 
    mult two 
    endmacro 
    

lbl: 
    macro1 a b 
  lbl2:  macro1 b b
    stop 
a: space
b: space 
two: const 32