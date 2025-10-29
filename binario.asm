INPUT a
jmpn is_neg
copy zero, neg 
jmpz is_zero
loop: load a 
    jmpz fim 
    div two 
    store next 
    mult two 
    store aux 
    load a 
    sub aux 
    store resto 
    output resto
    copy next, a 
    jmp loop
is_neg:
 copy one,neg 
load a 
mult minus_one 
store a 
jmp loop
is_zero:


output zero 
stop 
fim: 




load neg 
jmpz acaba
output one 
acaba: stop 
a: space 
zero: const 0
neg: space 
two: const 2 
next: 


space 
aux: space 

		resto: space 

one: 	const 		1 
		minus_one: 

			const -1