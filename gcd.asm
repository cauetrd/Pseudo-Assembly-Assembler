invERT: MacrO &a
	Load  &A
   mult        minus_one
			store     	&A
							endmacro
	input a
input b
	load 	A
jmpn INVERTE_A
JMPZ is_zero
comp_b: load    b
	jmpp GCD
jmpz IS_zERO
invert b
inverte_a: 			
INVERT a
jmp    comp_b
gcd:   
     
	load a 
sub b
jmpn troca_a_B
			jmpz fim
store a
jmp gcd
troca_A_B: LOAD				B
    sub     a
store 		b
jmp	gcd
FIM: OUTPUT A
stop
is_zero: load b
jmpn 		INVERTE_b
jmpp show_b
output a
stop 
	inverte_b: 


invert b
	show_b: 


output b
	stop
a: space
b: space
minus_one: const -1
