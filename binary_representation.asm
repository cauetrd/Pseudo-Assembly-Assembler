INPUT N
loaD n
	jmpp 	  is_poS
					JMPZ IS_zero
  copy one, is_neg
		load N
MULt minus_one
sToRe n
jmp 	         	loop
is_pos: COPY ZERO, IS_NEG
LOOP: 	LOAD N
JMPZ      FIM
DIV TWO     			
store  NeXT
mult 	two
STORE	AUX
LOAD	N
sUb		AUX
Store resto
output resto
copy 		next, n
jMp loop
	IS_ZERO:
OUTPUT ZERO
stop
		      		      			FIM:   
	    	   	load is_neg
JMPZ FIM2
output one
FIM2:


		STOP
N: SPACE
one: 		const     1
	is_neg: SPACE
MINUS_ONE: CoNsT -1
zero: const 0
two: const 2
	next: space
	aux: space
		resto: 		space
