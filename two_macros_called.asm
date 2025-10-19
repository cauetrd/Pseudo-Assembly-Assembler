macro1: macro &a, &b 
    load &a 
    output &a 
    mult &a 
    store &b 
    endmacro

macro2: macro &a, &b 
    load &a 
    sub &b 
    div &b 
    store &a 
    endmacro 

    input a 
    input b 
    load one 
    add b 
    store A
    lbl:       macro1 a B
    lbl1:
    
    
            
            macro2 a b 
        stop
    a: space 
    b: space 
    one: const 1