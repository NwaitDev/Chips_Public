.PHONY: all test clean quicktest

all: chipsc

SRCS := sources/ast_base.hpp sources/ast_definitions.hpp sources/ast_inoutputs.hpp sources/ast_lrxvalues.hpp sources/ast_program.hpp sources/ast_statements.hpp sources/ast_system_specific.hpp sources/ast_variables.hpp sources/ASTBuilder.hpp sources/chips_node_print.cpp sources/ChipsToXmiVisitor.cpp sources/ChipsToXmiVisitor.hpp sources/ChipsToXmiWriter.cpp sources/ChipsToXmiWriter.hpp sources/meta_type_conversions.hpp sources/metamodel_enums.hpp sources/chips_headers.hpp

chipsc: generate.sh $(SRCS)
	./generate.sh
	cd build ; make 2> debug.log
quicktest: quick.chips
	./build/chipsc quick.chips

clean:
	rm -f ChipsParser.hpp ChipsParser.cpp ChipsLexer.cpp chipsc \
	      position.hh stack.hh location.hh output_*.xmi *.output
