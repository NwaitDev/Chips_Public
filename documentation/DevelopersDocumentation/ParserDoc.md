# The Chips parser

It is available in the FullCompileChain/Chips2XmiParser folder.

chipsparser parses a `.chips` file with the ANTLR grammar, builds a typed AST while type-checking it, then serialises the AST as XMI for `chips1.1.ecore`. Usage: `chipsparser <input.chips> <output.chips.xmi>`.

| File | Role |
| --- | --- |
| `Chips.g4` | Grammar; ANTLR generates `ChipsParser`, `ChipsLexer`, `ChipsBaseVisitor` into `generated/` |
| `chips_ast_builder.hpp/.cpp` | `ChipsBaseVisitor` that builds the AST (`program_node`); one `visit*` per grammar rule; nodes are owned by `visitor_env` via `make_node` |
| `type_checker_visitor.hpp` | Checks each statement before it is built (`checker.visit(ctx)`); types are `dataflow_type` INT, FLOAT, BOOL |
| `input_inference_visitor.hpp` | Infers the type of collective (`c_*`) expressions |
| `visitor_env.hpp/.cpp` | Scopes and symbol tables: `lookup_logical`, `lookup_physical`, `lookup_object`, `lookup_block` |
| `ast_node_definitions.hpp/.tpp/.cpp` | AST node classes, templated on `dataflow_type` and on the context (`statement_env`: DEFINITION, COLLECTIVE, SYSTEM) |
| `meta_type_conversions.hpp`, `type_utils.hpp`, `metamodel_enums.hpp` | Compile-time mappings from (context, type) to node classes; enums mirroring the metamodel |
| `ChipsToXmiWriter.hpp/.cpp/.tpp` | Walks the AST and writes the XMI |

Semantic errors go through `semantic_fail(ctx, message)`, which reports the line and column; `chipsc` remaps them to the original file when `--include` was used.


For historical reasons (ie. no real technical reasons), the parser is currently developped in C++, based on ANTLR4. 
Maybe it should have been developed with Java for compatibility with the Eclipse Modeling Framework (EMF) later used, but it was a little late to realize that.