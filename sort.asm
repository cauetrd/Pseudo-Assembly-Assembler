swap: macro &a, &b 
copy &a, temp 
copy &b, &a 
copy temp, &a 
endmacro 
temp: space 
input a 
input b 
input c 
load A
sub b 
jmpn troca_a_b 
comp_a_c: load a 
sub c 
jmpn troca_a_c 
comp_b_c:
load b 
sub c 
jmpn troca_b_c 
fim: 

output c 
output b 
output a 
stop 
troca_a_b: 

swap a, b 
jmp comp_a_c

troca_a_c:
 swap      a,       c 
jmp comp_b_c 
troca_b_c: 


    swap       b,       c 


            jmp fim 

a: SPACE
b: space 
c: space 
