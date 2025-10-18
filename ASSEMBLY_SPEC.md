# Assembly language & assembler (summary)

This file documents the main functionalities and assumptions of the current assembler implementation in `assembler.cpp`. It is a concise reference for what the preprocessor and macro system do, which input cases are handled, and known limitations.

## Contract (what the tool does)

- Input: a plain-text assembly source file (vector of lines read from disk).
- Output: preprocessed assembly printed to stdout (currently). The preprocessor performs macro expansion and normalization (capitalize all letters and remove leading blank spaces/tabs)
## Key data structures and functions (in `assembler.cpp`)

- `mnt` (map<string,int>): macro name table — maps a macro name to its start index in `mdt`.
- `mdt` (vector<string>): macro definition table — stores macro body lines (with argument names normalized to positional markers like `#1`).
- `tabela_simbolos` (vector<Simbolo>): the symbol table structure used later in the assembler.

Important functions:
- `getTokens(string &linha)`: splits a line by spaces/tabs into tokens.
- `juntaTokens(vector<string>)`: joins tokens back into a single string with single spaces.
- `maisculas(string &linha)`: converts a line to uppercase (normalizes case-insensitive source).
- `tiraComentario(string &linha)`: removes content after `;` (inline comment support).
- `preProcessamento(vector<string> codigo)`: main preprocessing pipeline — normalizes lines, joins label-only lines to following instruction, and calls `expandeTodasMacros`.
- `expandeTodasMacros(vector<string> cod)`: single-pass macro definition collection + expansion of macro calls found in the code.
- `expandeMacro(string &nome, vector<string> &argumentos)`: reads macro body from `mdt` starting at `mnt[nome]` and substitutes positional markers `#1`, `#2`, ... with the invocation arguments.

## Macro model and rules (as implemented)

- Macro definitions use the pair `MACRO` / `ENDMACRO` (case-insensitive because the preprocessor uppercases lines).
- Macro definitions are expected to appear before their uses. In other words: "macros must be defined before they are called." The preprocessor collects definitions in a single left-to-right pass, so calls to macros defined later will not be recognized in the same pass.
- Definition form recognized:
  - `NAME: MACRO arg1 arg2`  (label-like macro name with a trailing `:` is accepted — the `:` is stripped when recording the macro name)
  - `NAME MACRO arg1 arg2` (depending on spacing; the code checks tokens after uppercasing)
- During macro definition, argument names in the macro body are replaced with positional markers `#1`, `#2`, ... and stored into `mdt`.
- Macro invocation performs positional substitution: invocation tokens after the macro name (or after a label prefix) are passed as `#1`, `#2`, etc. `expandeMacro` substitutes those back into the stored body and returns the expanded lines.
- Macros can be defined with zero arguments.

Additional macro-related notes:
- Parameter naming variants like `&A` are preserved; the preprocessor uppercases tokens and then compares them literally — so `&A` works if tokens are split correctly.
- The code treats commas and whitespace strictly: tokenization splits only on spaces/tabs

## Assumptions (project-level)

- The code assumes label collisions will not happen (macro expansions will not produce duplicate labels).
- The code assumes there will be no instruction vs macro name collisions (a token will not be both an instruction and a macro name).
- The code assumes macros will not call themselves (no self-recursive macro expansions).

## Directive rules enforced by tests / implementation assumptions

- `CONST` and `SPACE` directives (data declarations) are expected to appear at the end of the program or at least as final tokens for a label's declaration. Many tests and the assembler code assume data declarations are separate symbolic labels with `CONST`/`SPACE` following a label.
- The assembler preprocessor does not reorder data/instructions; it only normalizes and expands macros.

## Input cases the code currently deals with (handled cases)

- Case-insensitivity: keywords and symbols are uppercased by `maisculas` so source can be mixed-case.
- Comments: inline comments starting with `;` are removed (`tiraComentario`).
- Trailing whitespace and tabs: lines are tokenized (`getTokens`) and re-joined with single spaces (`juntaTokens`) — this strips extra spaces and tabs and normalizes spacing.
- Label on its own line: a label that appears alone on a line (ends with `:` and is the only token) is accumulated and attached to the following non-empty line. This allows code like:

  LabelOnly:
  LOAD A

  to become `LabelOnly: LOAD A` in the preprocessed output.
- Macro definitions before use: the code expects macros to be defined earlier in the file than their invocations (single-pass creation of `mdt`/`mnt`).
- Empty macros: macros with empty bodies are accepted and stored/expanded (they produce no output when expanded).
- Macro calls with extra spaces: tokens are normalized so calls like `   Inc    A   ` are handled; tokenization strips extra spaces.
- Macros without arguments: supported.
- Macro arguments containing arithmetic fragments when tokens are separated by spaces (e.g., `&A + 1`) — substitution operates on token-level, so separate tokens are required.

## Cases the code does NOT fully handle (known limitations)

- Nested macro calls are not expanded recursively in the same pass: if a macro's body (after positional substitution) contains a call to another macro, that nested call will remain unexpanded in the final output because expansion is only done for lines that the main pass sees. (Note: per the assumptions above, simple nested calls where macros are defined earlier may still work in practice, but the implementation performs a single pass.)
- Comma handling: `getTokens` splits only on spaces/tabs, so `COPY A, B` tokens may include commas (e.g., `A,`) and not be treated as two separate operand tokens. Many tests use commas in macro calls or directives; this implementation will not strip commas automatically.
- More sophisticated tokenization (strings, punctuation, parentheses, commas) is not implemented.

## Implementation notes / workflow summary

1. Preprocessing (in `preProcessamento`): uppercase, remove comments, normalize whitespace, attach label-only lines to next line.
2. Macro collection + expansion (single left-to-right pass in `expandeTodasMacros`): when a `MACRO` definition is encountered the preprocessor records the macro in `mnt` and pushes body lines (with param names replaced by `#n`) into `mdt`; when a line outside a macro is encountered the preprocessor checks whether the first token is an instruction (from a fixed list) — if so, it leaves it as-is; otherwise it checks `mnt` and expands macros by calling `expandeMacro` (positional param substitution) and appending the returned lines to the output.
3. Final output: the program prints expanded/preprocessed lines to stdout (a `.pre` file writer was present but commented out).


---

If you want, I can now implement any of the suggested improvements and run the test inputs to show the new preprocessor outputs. Otherwise this file documents the current behavior so you can keep it as a persistent summary.
