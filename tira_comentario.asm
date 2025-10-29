; Comentario
Negate: MACRO X
    LOAD X ; carrega argumento
    MULT MINUS_ONE ; multiplica por -1 
    STORE X ; guarda resultado
ENDMACRO

Negate A ; chama macro
STOP
A: SPACE
MINUS_ONE: CONST -1 ; define constante