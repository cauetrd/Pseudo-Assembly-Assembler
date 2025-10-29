; Teste de erros léxicos - Labels inválidos

; Erro: Label começando com número
2INVALID: CONST 10

; Erro: Label com caracteres especiais inválidos
LABEL@: SPACE
VAR$: CONST 5
TEST#: SPACE 2

; Erro: Label com hífen
INVALID-LABEL: CONST 1

; Labels válidos para comparação
VALID_LABEL: CONST 10
_VALID: SPACE
LABEL123: CONST 20

; Código principal
ADD VALID_LABEL
LOAD _VALID
STORE LABEL123
STOP