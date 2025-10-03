; This is a comment at the beginning
    ; Another comment with leading spaces

swap: macro x y    ; Define swap macro
    load x         ; Load first parameter
    store temp     ; Store in temporary
    
    load y         ; Load second parameter
    store x        ; Store in first location
    load temp      ; Load temporary
    store y        ; Store in second location
endmacro           ; End of macro

; Main program starts here
    load a         ; Load variable a
    store b        ; Store in variable b
    
    swap a b       ; Call our swap macro
    
    stop           ; End program

; Variable definitions
a: const 10        ; First variable
b: const 20        ; Second variable  
temp: space        ; Temporary storage
