repeat_label: MacrO &A, &B 
    Loop: load &a
            jmpz fim 
            sub &B 
            store &a  
    jmp Loop
    fim: outpuT A 
    endmacro 

    input a 
    input b 
    repeat_label a b 
    second_label: input b
    repeat_label b a
    stop 
a: space 
b: space
b: const 5