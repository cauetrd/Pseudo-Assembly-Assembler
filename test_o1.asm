INPUT a 
load B
add A
jmpp label 
store c 
label:
    load c 
    jmpn fora 
    output b 
    load a 
    add b 
    store a 
    jmp LABEL
fora: stOp
a: space 
b: const 4
c: space