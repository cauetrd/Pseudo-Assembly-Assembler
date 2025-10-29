test: macro &a, &B 
    load &a 
    mult &a 
    store &b 
    mult &b 
    lbl: 
    output &a
end:
endmacro
test AAAA, B 
stop
AAAA: const 10 
b: space