
// Generated from /home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/FullCompileChain/ChipsXmiGenerator/../Chips.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  ChipsParser : public antlr4::Parser {
public:
  enum {
    SYSTEM_KW = 1, INT_KW = 2, FLOAT_KW = 3, BOOL_KW = 4, LOGICAL_KW = 5, 
    PHYSICAL_KW = 6, AS_KW = 7, INIT_KW = 8, THEN_KW = 9, FOREACH_KW = 10, 
    IN_KW = 11, IF_KW = 12, ELSE_KW = 13, TO_KW = 14, LINK_KW = 15, IMPLEMENTS_KW = 16, 
    HAVING_KW = 17, INPUT_KW = 18, STOP_KW = 19, AMONG_KW = 20, SPREAD_KW = 21, 
    COLLECT_KW = 22, CTX_KW = 23, OBJECT_KW = 24, WITH_KW = 25, IMPLEMENTATION_KW = 26, 
    BY_KW = 27, TARGET_KW = 28, DEFAULT_KW = 29, USING_KW = 30, ACTUATOR_KW = 31, 
    SENSOR_KW = 32, ARROW = 33, PLUS = 34, MINUS = 35, TIMES = 36, DIV = 37, 
    MOD = 38, LT = 39, GT = 40, EQ = 41, LEQ = 42, GEQ = 43, NEQ = 44, AND = 45, 
    OR = 46, NOT = 47, ASSIGN = 48, COMMA = 49, SEMICOL = 50, L_PARENTH = 51, 
    R_PARENTH = 52, L_CURL = 53, R_CURL = 54, L_SQUA = 55, R_SQUA = 56, 
    COLUMN = 57, PERIOD = 58, BOOL = 59, FLOAT = 60, INT = 61, IDENTIFIER = 62, 
    NEWLINE = 63, WS = 64, COMMENT = 65
  };

  enum {
    RuleProgram = 0, RuleSystem = 1, RulePreamble = 2, RuleObject_def = 3, 
    RuleImplementation_def = 4, RuleNode_mapping = 5, RuleFunction_def = 6, 
    RuleCollective_op_def = 7, RuleC_output = 8, RuleL_function_def = 9, 
    RuleP_function_def = 10, RuleC_signature = 11, RuleC_keywords = 12, 
    RuleWith_section = 13, RuleWith_statement = 14, RuleInit_section = 15, 
    RuleThen_section = 16, RuleExpr = 17, RuleExpr0 = 18, RuleExpr01 = 19, 
    RuleExpr1 = 20, RuleExpr2 = 21, RuleCast = 22, RuleC_expr = 23, RuleC_stopless_expr = 24, 
    RuleC_stopless_expr0 = 25, RuleC_stopless_expr01 = 26, RuleC_stopless_expr1 = 27, 
    RuleC_stopless_expr2 = 28, RuleC_cast = 29, RuleSuffixes = 30, RuleC_suffixes = 31, 
    RuleS_suffixable_expr = 32, RuleBlock = 33, RuleLoop_in = 34, RuleLoop_statement = 35, 
    RuleC_loop_statement = 36, RuleS_loop_statement = 37, RuleIf_else_statement = 38, 
    RuleS_if_else_statement = 39, RuleC_if_else_statement = 40, RuleIf_statement = 41, 
    RuleS_if_statement = 42, RuleC_if_statement = 43, RuleStatement = 44, 
    RuleS_statement = 45, RuleS_expr = 46, RuleCollective_operation = 47, 
    RuleC_statement = 48, RuleNamed_output = 49, RuleP_named_output = 50, 
    RuleDf_parameter_decl = 51, RuleDf_type = 52, RulePdf_parameter_type = 53, 
    RulePdf_parameter_decl = 54, RuleCdf_defaulted_decl = 55, RuleCdf_full_declaration = 56
  };

  explicit ChipsParser(antlr4::TokenStream *input);

  ChipsParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ChipsParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class SystemContext;
  class PreambleContext;
  class Object_defContext;
  class Implementation_defContext;
  class Node_mappingContext;
  class Function_defContext;
  class Collective_op_defContext;
  class C_outputContext;
  class L_function_defContext;
  class P_function_defContext;
  class C_signatureContext;
  class C_keywordsContext;
  class With_sectionContext;
  class With_statementContext;
  class Init_sectionContext;
  class Then_sectionContext;
  class ExprContext;
  class Expr0Context;
  class Expr01Context;
  class Expr1Context;
  class Expr2Context;
  class CastContext;
  class C_exprContext;
  class C_stopless_exprContext;
  class C_stopless_expr0Context;
  class C_stopless_expr01Context;
  class C_stopless_expr1Context;
  class C_stopless_expr2Context;
  class C_castContext;
  class SuffixesContext;
  class C_suffixesContext;
  class S_suffixable_exprContext;
  class BlockContext;
  class Loop_inContext;
  class Loop_statementContext;
  class C_loop_statementContext;
  class S_loop_statementContext;
  class If_else_statementContext;
  class S_if_else_statementContext;
  class C_if_else_statementContext;
  class If_statementContext;
  class S_if_statementContext;
  class C_if_statementContext;
  class StatementContext;
  class S_statementContext;
  class S_exprContext;
  class Collective_operationContext;
  class C_statementContext;
  class Named_outputContext;
  class P_named_outputContext;
  class Df_parameter_declContext;
  class Df_typeContext;
  class Pdf_parameter_typeContext;
  class Pdf_parameter_declContext;
  class Cdf_defaulted_declContext;
  class Cdf_full_declarationContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<PreambleContext *> preamble();
    PreambleContext* preamble(size_t i);
    SystemContext *system();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  SystemContext : public antlr4::ParserRuleContext {
  public:
    SystemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYSTEM_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<S_statementContext *> s_statement();
    S_statementContext* s_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SystemContext* system();

  class  PreambleContext : public antlr4::ParserRuleContext {
  public:
    PreambleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PreambleContext() = default;
    void copyFrom(PreambleContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CollectiveOperationDefinitionContext : public PreambleContext {
  public:
    CollectiveOperationDefinitionContext(PreambleContext *ctx);

    Collective_op_defContext *collective_op_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ObjectDefinitionContext : public PreambleContext {
  public:
    ObjectDefinitionContext(PreambleContext *ctx);

    Object_defContext *object_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionDefinitionContext : public PreambleContext {
  public:
    FunctionDefinitionContext(PreambleContext *ctx);

    Function_defContext *function_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImplementationDefinitionContext : public PreambleContext {
  public:
    ImplementationDefinitionContext(PreambleContext *ctx);

    Implementation_defContext *implementation_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PreambleContext* preamble();

  class  Object_defContext : public antlr4::ParserRuleContext {
  public:
    Object_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OBJECT_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    With_sectionContext *with_section();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Object_defContext* object_def();

  class  Implementation_defContext : public antlr4::ParserRuleContext {
  public:
    Implementation_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPLEMENTATION_KW();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *COLUMN();
    antlr4::tree::TerminalNode *BY_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<Node_mappingContext *> node_mapping();
    Node_mappingContext* node_mapping(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Implementation_defContext* implementation_def();

  class  Node_mappingContext : public antlr4::ParserRuleContext {
  public:
    Node_mappingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HAVING_KW();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AS_KW();
    antlr4::tree::TerminalNode *SEMICOL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Node_mappingContext* node_mapping();

  class  Function_defContext : public antlr4::ParserRuleContext {
  public:
    Function_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Function_defContext() = default;
    void copyFrom(Function_defContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LogicalDefintionContext : public Function_defContext {
  public:
    LogicalDefintionContext(Function_defContext *ctx);

    L_function_defContext *l_function_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PhysicalDefinitionContext : public Function_defContext {
  public:
    PhysicalDefinitionContext(Function_defContext *ctx);

    P_function_defContext *p_function_def();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Function_defContext* function_def();

  class  Collective_op_defContext : public antlr4::ParserRuleContext {
  public:
    Collective_op_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    C_signatureContext *c_signature();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *TARGET_KW();
    antlr4::tree::TerminalNode *L_PARENTH();
    std::vector<C_exprContext *> c_expr();
    C_exprContext* c_expr(size_t i);
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<C_statementContext *> c_statement();
    C_statementContext* c_statement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<C_outputContext *> c_output();
    C_outputContext* c_output(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Collective_op_defContext* collective_op_def();

  class  C_outputContext : public antlr4::ParserRuleContext {
  public:
    C_outputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_outputContext() = default;
    void copyFrom(C_outputContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DefaultOutputContext : public C_outputContext {
  public:
    DefaultOutputContext(C_outputContext *ctx);

    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *DEFAULT_KW();
    antlr4::tree::TerminalNode *L_PARENTH();
    std::vector<C_exprContext *> c_expr();
    C_exprContext* c_expr(size_t i);
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ChanneledOutputContext : public C_outputContext {
  public:
    ChanneledOutputContext(C_outputContext *ctx);

    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    std::vector<C_exprContext *> c_expr();
    C_exprContext* c_expr(size_t i);
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_outputContext* c_output();

  class  L_function_defContext : public antlr4::ParserRuleContext {
  public:
    L_function_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOGICAL_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    Init_sectionContext *init_section();
    Then_sectionContext *then_section();
    std::vector<Df_parameter_declContext *> df_parameter_decl();
    Df_parameter_declContext* df_parameter_decl(size_t i);
    std::vector<Named_outputContext *> named_output();
    Named_outputContext* named_output(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  L_function_defContext* l_function_def();

  class  P_function_defContext : public antlr4::ParserRuleContext {
  public:
    P_function_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PHYSICAL_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    With_sectionContext *with_section();
    Init_sectionContext *init_section();
    Then_sectionContext *then_section();
    std::vector<Pdf_parameter_declContext *> pdf_parameter_decl();
    Pdf_parameter_declContext* pdf_parameter_decl(size_t i);
    std::vector<P_named_outputContext *> p_named_output();
    P_named_outputContext* p_named_output(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  P_function_defContext* p_function_def();

  class  C_signatureContext : public antlr4::ParserRuleContext {
  public:
    C_signatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    C_keywordsContext *c_keywords();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AMONG_KW();
    std::vector<Cdf_defaulted_declContext *> cdf_defaulted_decl();
    Cdf_defaulted_declContext* cdf_defaulted_decl(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_signatureContext* c_signature();

  class  C_keywordsContext : public antlr4::ParserRuleContext {
  public:
    C_keywordsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPREAD_KW();
    antlr4::tree::TerminalNode *COLLECT_KW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_keywordsContext* c_keywords();

  class  With_sectionContext : public antlr4::ParserRuleContext {
  public:
    With_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WITH_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<With_statementContext *> with_statement();
    With_statementContext* with_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  With_sectionContext* with_section();

  class  With_statementContext : public antlr4::ParserRuleContext {
  public:
    With_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    With_statementContext() = default;
    void copyFrom(With_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ContextualDeclarationContext : public With_statementContext {
  public:
    ContextualDeclarationContext(With_statementContext *ctx);

    antlr4::tree::TerminalNode *CTX_KW();
    Df_typeContext *df_type();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOL();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WithRegularStatementContext : public With_statementContext {
  public:
    WithRegularStatementContext(With_statementContext *ctx);

    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ChannelDeclarationContext : public With_statementContext {
  public:
    ChannelDeclarationContext(With_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  With_statementContext* with_statement();

  class  Init_sectionContext : public antlr4::ParserRuleContext {
  public:
    Init_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INIT_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Init_sectionContext* init_section();

  class  Then_sectionContext : public antlr4::ParserRuleContext {
  public:
    Then_sectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *THEN_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Then_sectionContext* then_section();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  GEQContext : public ExprContext {
  public:
    GEQContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *GEQ();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ORContext : public ExprContext {
  public:
    ORContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *OR();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ANDContext : public ExprContext {
  public:
    ANDContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *AND();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LTContext : public ExprContext {
  public:
    LTContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *LT();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LEQContext : public ExprContext {
  public:
    LEQContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *LEQ();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassExpr0Context : public ExprContext {
  public:
    PassExpr0Context(ExprContext *ctx);

    Expr0Context *expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NEQContext : public ExprContext {
  public:
    NEQContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *NEQ();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EQContext : public ExprContext {
  public:
    EQContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *EQ();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GTContext : public ExprContext {
  public:
    GTContext(ExprContext *ctx);

    Expr0Context *expr0();
    antlr4::tree::TerminalNode *GT();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();

  class  Expr0Context : public antlr4::ParserRuleContext {
  public:
    Expr0Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Expr0Context() = default;
    void copyFrom(Expr0Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SUBContext : public Expr0Context {
  public:
    SUBContext(Expr0Context *ctx);

    Expr01Context *expr01();
    antlr4::tree::TerminalNode *MINUS();
    Expr0Context *expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassExpr01Context : public Expr0Context {
  public:
    PassExpr01Context(Expr0Context *ctx);

    Expr01Context *expr01();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PLUSContext : public Expr0Context {
  public:
    PLUSContext(Expr0Context *ctx);

    Expr01Context *expr01();
    antlr4::tree::TerminalNode *PLUS();
    Expr0Context *expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Expr0Context* expr0();

  class  Expr01Context : public antlr4::ParserRuleContext {
  public:
    Expr01Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Expr01Context() = default;
    void copyFrom(Expr01Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PassExpr1Context : public Expr01Context {
  public:
    PassExpr1Context(Expr01Context *ctx);

    Expr1Context *expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegateContext : public Expr01Context {
  public:
    NegateContext(Expr01Context *ctx);

    antlr4::tree::TerminalNode *MINUS();
    Expr1Context *expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Expr01Context* expr01();

  class  Expr1Context : public antlr4::ParserRuleContext {
  public:
    Expr1Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Expr1Context() = default;
    void copyFrom(Expr1Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DIVContext : public Expr1Context {
  public:
    DIVContext(Expr1Context *ctx);

    Expr2Context *expr2();
    antlr4::tree::TerminalNode *DIV();
    Expr1Context *expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NOTContext : public Expr1Context {
  public:
    NOTContext(Expr1Context *ctx);

    antlr4::tree::TerminalNode *NOT();
    Expr2Context *expr2();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MODContext : public Expr1Context {
  public:
    MODContext(Expr1Context *ctx);

    Expr2Context *expr2();
    antlr4::tree::TerminalNode *MOD();
    Expr1Context *expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MULTContext : public Expr1Context {
  public:
    MULTContext(Expr1Context *ctx);

    Expr2Context *expr2();
    antlr4::tree::TerminalNode *TIMES();
    Expr1Context *expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassExpr2Context : public Expr1Context {
  public:
    PassExpr2Context(Expr1Context *ctx);

    Expr2Context *expr2();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Expr1Context* expr1();

  class  Expr2Context : public antlr4::ParserRuleContext {
  public:
    Expr2Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Expr2Context() = default;
    void copyFrom(Expr2Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CastAsContext : public Expr2Context {
  public:
    CastAsContext(Expr2Context *ctx);

    CastContext *cast();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionContext : public Expr2Context {
  public:
    FunctionContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolLiteralContext : public Expr2Context {
  public:
    BoolLiteralContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *BOOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FloatLiteralContext : public Expr2Context {
  public:
    FloatLiteralContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *FLOAT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarContext : public Expr2Context {
  public:
    VarContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParensContext : public Expr2Context {
  public:
    ParensContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *L_PARENTH();
    ExprContext *expr();
    antlr4::tree::TerminalNode *R_PARENTH();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarContextContext : public Expr2Context {
  public:
    VarContextContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *CTX_KW();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntLiteralContext : public Expr2Context {
  public:
    IntLiteralContext(Expr2Context *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Expr2Context* expr2();

  class  CastContext : public antlr4::ParserRuleContext {
  public:
    CastContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PARENTH();
    Df_typeContext *df_type();
    antlr4::tree::TerminalNode *R_PARENTH();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CastContext* cast();

  class  C_exprContext : public antlr4::ParserRuleContext {
  public:
    C_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_exprContext() = default;
    void copyFrom(C_exprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CStoplessExpressionContext : public C_exprContext {
  public:
    CStoplessExpressionContext(C_exprContext *ctx);

    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StopContext : public C_exprContext {
  public:
    StopContext(C_exprContext *ctx);

    antlr4::tree::TerminalNode *STOP_KW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_exprContext* c_expr();

  class  C_stopless_exprContext : public antlr4::ParserRuleContext {
  public:
    C_stopless_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_stopless_exprContext() = default;
    void copyFrom(C_stopless_exprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CGTContext : public C_stopless_exprContext {
  public:
    CGTContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *GT();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CORContext : public C_stopless_exprContext {
  public:
    CORContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *OR();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassCExpr0Context : public C_stopless_exprContext {
  public:
    PassCExpr0Context(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CNEQContext : public C_stopless_exprContext {
  public:
    CNEQContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *NEQ();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CLTContext : public C_stopless_exprContext {
  public:
    CLTContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *LT();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CLEQContext : public C_stopless_exprContext {
  public:
    CLEQContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *LEQ();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CANDContext : public C_stopless_exprContext {
  public:
    CANDContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *AND();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CEQContext : public C_stopless_exprContext {
  public:
    CEQContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *EQ();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CGEQContext : public C_stopless_exprContext {
  public:
    CGEQContext(C_stopless_exprContext *ctx);

    C_stopless_expr0Context *c_stopless_expr0();
    antlr4::tree::TerminalNode *GEQ();
    C_stopless_exprContext *c_stopless_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_stopless_exprContext* c_stopless_expr();

  class  C_stopless_expr0Context : public antlr4::ParserRuleContext {
  public:
    C_stopless_expr0Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_stopless_expr0Context() = default;
    void copyFrom(C_stopless_expr0Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CSUBContext : public C_stopless_expr0Context {
  public:
    CSUBContext(C_stopless_expr0Context *ctx);

    C_stopless_expr01Context *c_stopless_expr01();
    antlr4::tree::TerminalNode *MINUS();
    C_stopless_expr0Context *c_stopless_expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CPLUSContext : public C_stopless_expr0Context {
  public:
    CPLUSContext(C_stopless_expr0Context *ctx);

    C_stopless_expr01Context *c_stopless_expr01();
    antlr4::tree::TerminalNode *PLUS();
    C_stopless_expr0Context *c_stopless_expr0();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassCExpr01Context : public C_stopless_expr0Context {
  public:
    PassCExpr01Context(C_stopless_expr0Context *ctx);

    C_stopless_expr01Context *c_stopless_expr01();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_stopless_expr0Context* c_stopless_expr0();

  class  C_stopless_expr01Context : public antlr4::ParserRuleContext {
  public:
    C_stopless_expr01Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_stopless_expr01Context() = default;
    void copyFrom(C_stopless_expr01Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PassCExpr1Context : public C_stopless_expr01Context {
  public:
    PassCExpr1Context(C_stopless_expr01Context *ctx);

    C_stopless_expr1Context *c_stopless_expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CNegateContext : public C_stopless_expr01Context {
  public:
    CNegateContext(C_stopless_expr01Context *ctx);

    antlr4::tree::TerminalNode *MINUS();
    C_stopless_expr1Context *c_stopless_expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_stopless_expr01Context* c_stopless_expr01();

  class  C_stopless_expr1Context : public antlr4::ParserRuleContext {
  public:
    C_stopless_expr1Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_stopless_expr1Context() = default;
    void copyFrom(C_stopless_expr1Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CMODContext : public C_stopless_expr1Context {
  public:
    CMODContext(C_stopless_expr1Context *ctx);

    C_stopless_expr2Context *c_stopless_expr2();
    antlr4::tree::TerminalNode *MOD();
    C_stopless_expr1Context *c_stopless_expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CDIVContext : public C_stopless_expr1Context {
  public:
    CDIVContext(C_stopless_expr1Context *ctx);

    C_stopless_expr2Context *c_stopless_expr2();
    antlr4::tree::TerminalNode *DIV();
    C_stopless_expr1Context *c_stopless_expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PassCExpr2Context : public C_stopless_expr1Context {
  public:
    PassCExpr2Context(C_stopless_expr1Context *ctx);

    C_stopless_expr2Context *c_stopless_expr2();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CMULTContext : public C_stopless_expr1Context {
  public:
    CMULTContext(C_stopless_expr1Context *ctx);

    C_stopless_expr2Context *c_stopless_expr2();
    antlr4::tree::TerminalNode *TIMES();
    C_stopless_expr1Context *c_stopless_expr1();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CNOTContext : public C_stopless_expr1Context {
  public:
    CNOTContext(C_stopless_expr1Context *ctx);

    antlr4::tree::TerminalNode *NOT();
    C_stopless_expr2Context *c_stopless_expr2();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_stopless_expr1Context* c_stopless_expr1();

  class  C_stopless_expr2Context : public antlr4::ParserRuleContext {
  public:
    C_stopless_expr2Context(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_stopless_expr2Context() = default;
    void copyFrom(C_stopless_expr2Context *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ChanneledAccuExpressionContext : public C_stopless_expr2Context {
  public:
    ChanneledAccuExpressionContext(C_stopless_expr2Context *ctx);

    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *PERIOD();
    C_suffixesContext *c_suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CParenthesisContext : public C_stopless_expr2Context {
  public:
    CParenthesisContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *L_PARENTH();
    C_stopless_exprContext *c_stopless_expr();
    antlr4::tree::TerminalNode *R_PARENTH();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CVariableExpressionContext : public C_stopless_expr2Context {
  public:
    CVariableExpressionContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    C_suffixesContext *c_suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CBOOLContext : public C_stopless_expr2Context {
  public:
    CBOOLContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *BOOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CtxVariableExpressionContext : public C_stopless_expr2Context {
  public:
    CtxVariableExpressionContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *CTX_KW();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();
    C_suffixesContext *c_suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CINTContext : public C_stopless_expr2Context {
  public:
    CINTContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  INPUTContext : public C_stopless_expr2Context {
  public:
    INPUTContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *INPUT_KW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CCastAsContext : public C_stopless_expr2Context {
  public:
    CCastAsContext(C_stopless_expr2Context *ctx);

    C_castContext *c_cast();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CFLOATContext : public C_stopless_expr2Context {
  public:
    CFLOATContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *FLOAT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionCallContext : public C_stopless_expr2Context {
  public:
    FunctionCallContext(C_stopless_expr2Context *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<C_exprContext *> c_expr();
    C_exprContext* c_expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_stopless_expr2Context* c_stopless_expr2();

  class  C_castContext : public antlr4::ParserRuleContext {
  public:
    C_castContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PARENTH();
    Df_typeContext *df_type();
    antlr4::tree::TerminalNode *R_PARENTH();
    C_stopless_exprContext *c_stopless_expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_castContext* c_cast();

  class  SuffixesContext : public antlr4::ParserRuleContext {
  public:
    SuffixesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> L_SQUA();
    antlr4::tree::TerminalNode* L_SQUA(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_SQUA();
    antlr4::tree::TerminalNode* R_SQUA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SuffixesContext* suffixes();

  class  C_suffixesContext : public antlr4::ParserRuleContext {
  public:
    C_suffixesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> L_SQUA();
    antlr4::tree::TerminalNode* L_SQUA(size_t i);
    std::vector<C_stopless_exprContext *> c_stopless_expr();
    C_stopless_exprContext* c_stopless_expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_SQUA();
    antlr4::tree::TerminalNode* R_SQUA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_suffixesContext* c_suffixes();

  class  S_suffixable_exprContext : public antlr4::ParserRuleContext {
  public:
    S_suffixable_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    S_suffixable_exprContext() = default;
    void copyFrom(S_suffixable_exprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SSuffixableVariableExpressionContext : public S_suffixable_exprContext {
  public:
    SSuffixableVariableExpressionContext(S_suffixable_exprContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SSuffixableFunctionCallExpressionContext : public S_suffixable_exprContext {
  public:
    SSuffixableFunctionCallExpressionContext(S_suffixable_exprContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SSuffixableBlockOutputExpressionContext : public S_suffixable_exprContext {
  public:
    SSuffixableBlockOutputExpressionContext(S_suffixable_exprContext *ctx);

    BlockContext *block();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  S_suffixable_exprContext* s_suffixable_expr();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  Loop_inContext : public antlr4::ParserRuleContext {
  public:
    Loop_inContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loop_inContext* loop_in();

  class  Loop_statementContext : public antlr4::ParserRuleContext {
  public:
    Loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOREACH_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN_KW();
    Loop_inContext *loop_in();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loop_statementContext* loop_statement();

  class  C_loop_statementContext : public antlr4::ParserRuleContext {
  public:
    C_loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOREACH_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN_KW();
    Loop_inContext *loop_in();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<C_statementContext *> c_statement();
    C_statementContext* c_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_loop_statementContext* c_loop_statement();

  class  S_loop_statementContext : public antlr4::ParserRuleContext {
  public:
    S_loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOREACH_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN_KW();
    S_suffixable_exprContext *s_suffixable_expr();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<S_statementContext *> s_statement();
    S_statementContext* s_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  S_loop_statementContext* s_loop_statement();

  class  If_else_statementContext : public antlr4::ParserRuleContext {
  public:
    If_else_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    If_statementContext *if_statement();
    antlr4::tree::TerminalNode *ELSE_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_else_statementContext* if_else_statement();

  class  S_if_else_statementContext : public antlr4::ParserRuleContext {
  public:
    S_if_else_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    S_if_statementContext *s_if_statement();
    antlr4::tree::TerminalNode *ELSE_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<S_statementContext *> s_statement();
    S_statementContext* s_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  S_if_else_statementContext* s_if_else_statement();

  class  C_if_else_statementContext : public antlr4::ParserRuleContext {
  public:
    C_if_else_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    C_if_statementContext *c_if_statement();
    antlr4::tree::TerminalNode *ELSE_KW();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<C_statementContext *> c_statement();
    C_statementContext* c_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_if_else_statementContext* c_if_else_statement();

  class  If_statementContext : public antlr4::ParserRuleContext {
  public:
    If_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF_KW();
    antlr4::tree::TerminalNode *L_PARENTH();
    ExprContext *expr();
    antlr4::tree::TerminalNode *R_PARENTH();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_statementContext* if_statement();

  class  S_if_statementContext : public antlr4::ParserRuleContext {
  public:
    S_if_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF_KW();
    antlr4::tree::TerminalNode *L_PARENTH();
    ExprContext *expr();
    antlr4::tree::TerminalNode *R_PARENTH();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<S_statementContext *> s_statement();
    S_statementContext* s_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  S_if_statementContext* s_if_statement();

  class  C_if_statementContext : public antlr4::ParserRuleContext {
  public:
    C_if_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF_KW();
    antlr4::tree::TerminalNode *L_PARENTH();
    C_exprContext *c_expr();
    antlr4::tree::TerminalNode *R_PARENTH();
    antlr4::tree::TerminalNode *L_CURL();
    antlr4::tree::TerminalNode *R_CURL();
    std::vector<C_statementContext *> c_statement();
    C_statementContext* c_statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  C_if_statementContext* c_if_statement();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StatementIfContext : public StatementContext {
  public:
    StatementIfContext(StatementContext *ctx);

    If_statementContext *if_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StatementDeclarationContext : public StatementContext {
  public:
    StatementDeclarationContext(StatementContext *ctx);

    Df_typeContext *df_type();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOL();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StatementLoopContext : public StatementContext {
  public:
    StatementLoopContext(StatementContext *ctx);

    Loop_statementContext *loop_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StatementContextualAssignmentContext : public StatementContext {
  public:
    StatementContextualAssignmentContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *CTX_KW();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StatementAssignmentContext : public StatementContext {
  public:
    StatementAssignmentContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StatementIfElseContext : public StatementContext {
  public:
    StatementIfElseContext(StatementContext *ctx);

    If_else_statementContext *if_else_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  S_statementContext : public antlr4::ParserRuleContext {
  public:
    S_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    S_statementContext() = default;
    void copyFrom(S_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FeedingStatementContext : public S_statementContext {
  public:
    FeedingStatementContext(S_statementContext *ctx);

    BlockContext *block();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    S_exprContext *s_expr();
    antlr4::tree::TerminalNode *R_PARENTH();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SLoopStatementContext : public S_statementContext {
  public:
    SLoopStatementContext(S_statementContext *ctx);

    S_loop_statementContext *s_loop_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ObjectDeclarationContext : public S_statementContext {
  public:
    ObjectDeclarationContext(S_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LinkingStatementContext : public S_statementContext {
  public:
    LinkingStatementContext(S_statementContext *ctx);

    antlr4::tree::TerminalNode *LINK_KW();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<SuffixesContext *> suffixes();
    SuffixesContext* suffixes(size_t i);
    antlr4::tree::TerminalNode *TO_KW();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SIfStatementContext : public S_statementContext {
  public:
    SIfStatementContext(S_statementContext *ctx);

    S_if_statementContext *s_if_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SIfElseStatementContext : public S_statementContext {
  public:
    SIfElseStatementContext(S_statementContext *ctx);

    S_if_else_statementContext *s_if_else_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImplementationStatementContext : public S_statementContext {
  public:
    ImplementationStatementContext(S_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<SuffixesContext *> suffixes();
    SuffixesContext* suffixes(size_t i);
    antlr4::tree::TerminalNode *IMPLEMENTATION_KW();
    antlr4::tree::TerminalNode *USING_KW();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RegularStatementContext : public S_statementContext {
  public:
    RegularStatementContext(S_statementContext *ctx);

    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  S_statementContext* s_statement();

  class  S_exprContext : public antlr4::ParserRuleContext {
  public:
    S_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    S_exprContext() = default;
    void copyFrom(S_exprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SRegularExpressionContext : public S_exprContext {
  public:
    SRegularExpressionContext(S_exprContext *ctx);

    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SBlockOutputExpressionContext : public S_exprContext {
  public:
    SBlockOutputExpressionContext(S_exprContext *ctx);

    BlockContext *block();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SCollectiveCastExpressionContext : public S_exprContext {
  public:
    SCollectiveCastExpressionContext(S_exprContext *ctx);

    Collective_operationContext *collective_operation();
    BlockContext *block();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  S_exprContext* s_expr();

  class  Collective_operationContext : public antlr4::ParserRuleContext {
  public:
    Collective_operationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PARENTH();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *R_PARENTH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Collective_operationContext* collective_operation();

  class  C_statementContext : public antlr4::ParserRuleContext {
  public:
    C_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    C_statementContext() = default;
    void copyFrom(C_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CollectiveIfElseStatementContext : public C_statementContext {
  public:
    CollectiveIfElseStatementContext(C_statementContext *ctx);

    C_if_else_statementContext *c_if_else_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollectiveLoopStatementContext : public C_statementContext {
  public:
    CollectiveLoopStatementContext(C_statementContext *ctx);

    C_loop_statementContext *c_loop_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollectiveIfStatementContext : public C_statementContext {
  public:
    CollectiveIfStatementContext(C_statementContext *ctx);

    C_if_statementContext *c_if_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollectiveAssignmentContext : public C_statementContext {
  public:
    CollectiveAssignmentContext(C_statementContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    C_suffixesContext *c_suffixes();
    antlr4::tree::TerminalNode *ASSIGN();
    C_exprContext *c_expr();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollectiveVariableDeclarationContext : public C_statementContext {
  public:
    CollectiveVariableDeclarationContext(C_statementContext *ctx);

    Cdf_full_declarationContext *cdf_full_declaration();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContextualAssignmentContext : public C_statementContext {
  public:
    ContextualAssignmentContext(C_statementContext *ctx);

    antlr4::tree::TerminalNode *CTX_KW();
    antlr4::tree::TerminalNode *PERIOD();
    antlr4::tree::TerminalNode *IDENTIFIER();
    C_suffixesContext *c_suffixes();
    antlr4::tree::TerminalNode *ASSIGN();
    C_exprContext *c_expr();
    antlr4::tree::TerminalNode *SEMICOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  C_statementContext* c_statement();

  class  Named_outputContext : public antlr4::ParserRuleContext {
  public:
    Named_outputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_outputContext* named_output();

  class  P_named_outputContext : public antlr4::ParserRuleContext {
  public:
    P_named_outputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    P_named_outputContext() = default;
    void copyFrom(P_named_outputContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FunctionOutputContext : public P_named_outputContext {
  public:
    FunctionOutputContext(P_named_outputContext *ctx);

    Named_outputContext *named_output();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ActuatorOutputContext : public P_named_outputContext {
  public:
    ActuatorOutputContext(P_named_outputContext *ctx);

    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *ACTUATOR_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PARENTH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *R_PARENTH();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  P_named_outputContext* p_named_output();

  class  Df_parameter_declContext : public antlr4::ParserRuleContext {
  public:
    Df_parameter_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Df_typeContext *df_type();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Df_parameter_declContext* df_parameter_decl();

  class  Df_typeContext : public antlr4::ParserRuleContext {
  public:
    Df_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Df_typeContext() = default;
    void copyFrom(Df_typeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BoolTypeContext : public Df_typeContext {
  public:
    BoolTypeContext(Df_typeContext *ctx);

    antlr4::tree::TerminalNode *BOOL_KW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntTypeContext : public Df_typeContext {
  public:
    IntTypeContext(Df_typeContext *ctx);

    antlr4::tree::TerminalNode *INT_KW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FloatTypeContext : public Df_typeContext {
  public:
    FloatTypeContext(Df_typeContext *ctx);

    antlr4::tree::TerminalNode *FLOAT_KW();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Df_typeContext* df_type();

  class  Pdf_parameter_typeContext : public antlr4::ParserRuleContext {
  public:
    Pdf_parameter_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Pdf_parameter_typeContext() = default;
    void copyFrom(Pdf_parameter_typeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SensorParameterTypeContext : public Pdf_parameter_typeContext {
  public:
    SensorParameterTypeContext(Pdf_parameter_typeContext *ctx);

    antlr4::tree::TerminalNode *SENSOR_KW();
    Df_typeContext *df_type();
    SuffixesContext *suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionParameterTypeContext : public Pdf_parameter_typeContext {
  public:
    FunctionParameterTypeContext(Pdf_parameter_typeContext *ctx);

    Df_typeContext *df_type();
    SuffixesContext *suffixes();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Pdf_parameter_typeContext* pdf_parameter_type();

  class  Pdf_parameter_declContext : public antlr4::ParserRuleContext {
  public:
    Pdf_parameter_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pdf_parameter_typeContext *pdf_parameter_type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pdf_parameter_declContext* pdf_parameter_decl();

  class  Cdf_defaulted_declContext : public antlr4::ParserRuleContext {
  public:
    Cdf_defaulted_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Df_typeContext *df_type();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    C_exprContext *c_expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cdf_defaulted_declContext* cdf_defaulted_decl();

  class  Cdf_full_declarationContext : public antlr4::ParserRuleContext {
  public:
    Cdf_full_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Df_typeContext *df_type();
    SuffixesContext *suffixes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    C_exprContext *c_expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cdf_full_declarationContext* cdf_full_declaration();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

