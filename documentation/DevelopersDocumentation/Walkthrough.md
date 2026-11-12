# Walkthrough: adding a new language construct

To give an overview of how to make the language evolve, this document presents all the steps to go through to add a new statement part of the chips language.

A new statement touches up to six places, in the following order. Skip a step only when the construct has no effect there.

1. **Grammar** — add the rule (with a `# Label` alternative) to `Chips.g4` and regenerate the ANTLR sources for both chipsparser and Chips2Cpp.
2. **Type checking** — add `visit<Label>` to `type_checker_visitor.hpp` (and to `input_inference_visitor.hpp` for a collective form) using `expect` / `resolve_variable`.
3. **AST** — add the node class in `ast_node_definitions.*`, its alias in `meta_type_conversions.hpp` if it is typed, and `visit<Label>` in `chips_ast_builder` (call `checker.visit(ctx)` first, build with `make_node`).
4. **Metamodel + XMI** — add the EClass to `chips1.1.ecore` if the concept is new, and its serialisation to `ChipsToXmiWriter`.
5. **ATL** — add or extend the rule in `chips2bip.atl` that maps it to BIP.
6. **C++ generation** — add a `translate<Label>` branch in `CodeGenListener::translateStatementBody`; until then the statement is copied verbatim and reported as `unhandled:`.

Check it end to end with `chipsc test.chips --chips-xmi`, then `--bip`, then a full run. Little reminder, you can use the ```probe``` statement inside function definitions of a Chips model to print the value of expressions in a CSV file.