sum: macro &a, &b 
    load &a 
    add &b 
    store x 
    endmacro 
a: space
b: space 
x: space
input a 
input b 
load a 
jmpp chama 
stop





    
        
        sum a, b 
stop 
