
// Generated from /home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/FullCompileChain/ChipsXmiGenerator/../Chips.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  ChipsLexer : public antlr4::Lexer {
public:
  enum {
    SYSTEM_KW = 1, INT_KW = 2, FLOAT_KW = 3, BOOL_KW = 4, LOGICAL_KW = 5, 
    PHYSICAL_KW = 6, AS_KW = 7, INIT_KW = 8, THEN_KW = 9, FOREACH_KW = 10, 
    IN_KW = 11, IF_KW = 12, ELSE_KW = 13, TO_KW = 14, LINK_KW = 15, IMPLEMENTS_KW = 16, 
    HAVING_KW = 17, INPUT_KW = 18, STOP_KW = 19, AMONG_KW = 20, SPREAD_KW = 21, 
    COLLECT_KW = 22, CTX_KW = 23, OBJECT_KW = 24, WITH_KW = 25, IMPLEMENTATION_KW = 26, 
    BY_KW = 27, TARGET_KW = 28, DEFAULT_KW = 29, USING_KW = 30, ACTUATOR_KW = 31, 
    SENSOR_KW = 32, PROBE_KW = 33, ARROW = 34, PLUS = 35, MINUS = 36, TIMES = 37, 
    DIV = 38, MOD = 39, LT = 40, GT = 41, EQ = 42, LEQ = 43, GEQ = 44, NEQ = 45, 
    AND = 46, OR = 47, NOT = 48, ASSIGN = 49, COMMA = 50, SEMICOL = 51, 
    L_PARENTH = 52, R_PARENTH = 53, L_CURL = 54, R_CURL = 55, L_SQUA = 56, 
    R_SQUA = 57, COLUMN = 58, PERIOD = 59, BOOL = 60, FLOAT = 61, INT = 62, 
    IDENTIFIER = 63, NEWLINE = 64, WS = 65, COMMENT = 66
  };

  explicit ChipsLexer(antlr4::CharStream *input);

  ~ChipsLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

