
; Factorial program with comments and mixed case

Input    n      ; Read input value


 LoAd     n      ; Load n
fAt:     
sUb      oNe   
; Subtract 1 from n
Jmpz     Fim    ; If zero, jump to end
StoRE         aUx    ; Store result in aux




	mUlT     n      ; Multiply by n
  StoRe    n      ; Store result back in n
LoAd     aUx    ; Load aux
JmP          fAt    ; Loop
			FiM:   




	  OuTPuT   n   ; Output result
sToP


    aUx:     
sPaCe
n:       SpAcE
oNe:   
     cOnSt    1
