macro1: macro &a 
    lbl: 
        output &a 
        load &a 
    othr:
    
        mult &a 
        
            div &a
        store &a 
    endmacro 
macro2: macro &a, &b 
    input &a 
    lbl_dentro: 
    copy &a, &b 
    endmacro 

macro1 a 
macro2 a, B
a: space 
b: space