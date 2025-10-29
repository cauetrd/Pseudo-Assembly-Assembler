; Teste de erros sintáticos e semânticos

; Erro: Instrução inexistente
INVALID_INSTRUCTION A
UNKNOWN_OP B

; Erro: Número incorreto de parâmetros
ADD ; sem parâmetros
SUB A B C ; muitos parâmetros
COPY A ; poucos parâmetros para COPY
JMP ; sem parâmetro para JMP

; Erro: Rótulo não declarado
JMP UNDEFINED_LABEL
LOAD NONEXISTENT_VAR
STORE MISSING_LABEL

; Erro: Dois rótulos na mesma linha
LABEL1: LABEL2: ADD A

; Erro: Rótulo declarado duas vezes
DUPLICATE: CONST 10
ADD A
DUPLICATE: SPACE 5

; Código válido para teste
VALID_LABEL: CONST 15
ADD VALID_LABEL
STOP

A: SPACE
B: CONST 20