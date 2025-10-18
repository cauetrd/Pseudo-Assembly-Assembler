MACRO_SIMPLES: MACRO &a
        LOAD &A 
        ADD ONE 
        STORE &A 
    output &a 
            endmacro

chama:
        macro_simples b 
    stop 
b: space 
    one: const 1