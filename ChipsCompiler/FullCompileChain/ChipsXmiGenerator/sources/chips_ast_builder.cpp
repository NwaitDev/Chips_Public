#include "chips_ast_builder.hpp"
#include "../generated/ChipsParser.h"


#define UNIMPLEMENTED_METHOD \
  throw std::runtime_error(std::string("unimplemented ") + __func__ + " error.")



// Context helper methods

int line_of(antlr4::ParserRuleContext* c) { return c->getStart()->getLine(); }
int col_of(antlr4::ParserRuleContext* c) { return c->getStart()->getCharPositionInLine(); }

void chips_ast_builder::declare_contextual(const std::string& var, dataflow_type type)
{
  m_contextuals[m_current_def_name][var] = type;
}

std::optional<dataflow_type> chips_ast_builder::find_symbol(const std::string& var) const
{
  auto node = m_contextuals.find(m_current_def_name);
  if (node == m_contextuals.end()) return std::nullopt;
  auto it = node->second.find(var);
  if (it == node->second.end()) return std::nullopt;
  return it->second;
}

void chips_ast_builder::declare_parameter(const std::string& function, const std::string& var, dataflow_type type)
{
  auto& params = m_parameters[function];
  if (params.find(var) != params.end())
  {
    throw std::runtime_error("duplicate parameter '" + var + "' in function '" + function + "'");
  }
  params[var] = type;
}

std::optional<dataflow_type> chips_ast_builder::find_parameter(const std::string& function, const std::string& var) const
{
  auto fn = m_parameters.find(function);
  if (fn == m_parameters.end()) return std::nullopt;
  auto it = fn->second.find(var);
  if (it == fn->second.end()) return std::nullopt;
  return it->second;
}



// Type inference methods

namespace {

bool is_numeric(dataflow_type t)
{
  return t == dataflow_type::INT || t == dataflow_type::FLOAT;
}

std::string type_name(dataflow_type t)
{
  switch (t)
  {
    case dataflow_type::INT: return "int";
    case dataflow_type::FLOAT: return "float";
    case dataflow_type::BOOL: return "bool";
  }
  return "?";
}
}

void chips_ast_builder::type_fail(antlr4::ParserRuleContext* ctx, const std::string& msg) const
{
  throw std::runtime_error(
      "type inference failed at line " + std::to_string(line_of(ctx)) +
      " in '" + m_current_def_name + "': " + msg +
      " (expression: " + ctx->getText() + ")");
}

dataflow_type chips_ast_builder::lookup_variable(const std::string& name, antlr4::ParserRuleContext* ctx) const
{
  if (auto t = find_symbol(name)) return *t;
  if (auto p = find_parameter(m_current_def_name, name)) return *p;
  type_fail(ctx, "undeclared variable '" + name + "'");
}

void chips_ast_builder::check_suffixes(ChipsParser::SuffixesContext* ctx) const
{
  for (ChipsParser::ExprContext* e : ctx->expr())
  {
    dataflow_type t = infer_type(e);
    if (t != dataflow_type::INT) type_fail(e, "array index must be int, got " + type_name(t));
  }
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::ExprContext* e) const
{
  auto relational = [&](auto* c) {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (!is_numeric(l) || l != r)
      type_fail(c, "comparison needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };
  auto equality = [&](auto* c) {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (l != r) type_fail(c, "equality needs operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };
  auto logical = [&](auto* c) {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (l != dataflow_type::BOOL || r != dataflow_type::BOOL)
      type_fail(c, "logical operator needs bool operands, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };

  if (auto c = dynamic_cast<ChipsParser::LTContext*>(e)) return relational(c);
  if (auto c = dynamic_cast<ChipsParser::GTContext*>(e)) return relational(c);
  if (auto c = dynamic_cast<ChipsParser::LEQContext*>(e)) return relational(c);
  if (auto c = dynamic_cast<ChipsParser::GEQContext*>(e)) return relational(c);
  if (auto c = dynamic_cast<ChipsParser::EQContext*>(e)) return equality(c);
  if (auto c = dynamic_cast<ChipsParser::NEQContext*>(e)) return equality(c);
  if (auto c = dynamic_cast<ChipsParser::ANDContext*>(e)) return logical(c);
  if (auto c = dynamic_cast<ChipsParser::ORContext*>(e)) return logical(c);
  if (auto c = dynamic_cast<ChipsParser::PassExpr0Context*>(e)) return infer_type(c->expr0());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr0Context* e) const
{
  auto additive = [&](auto* c) {
    dataflow_type l = infer_type(c->expr01());
    dataflow_type r = infer_type(c->expr0());
    if (!is_numeric(l) || l != r)
      type_fail(c, "arithmetic needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return l;
  };

  if (auto c = dynamic_cast<ChipsParser::PLUSContext*>(e)) return additive(c);
  if (auto c = dynamic_cast<ChipsParser::SUBContext*>(e)) return additive(c);
  if (auto c = dynamic_cast<ChipsParser::PassExpr01Context*>(e)) return infer_type(c->expr01());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr01Context* e) const
{
  if (auto c = dynamic_cast<ChipsParser::NegateContext*>(e))
  {
    dataflow_type t = infer_type(c->expr1());
    if (!is_numeric(t)) type_fail(c, "unary minus needs a numeric operand, got " + type_name(t));
    return t;
  }
  if (auto c = dynamic_cast<ChipsParser::PassExpr1Context*>(e)) return infer_type(c->expr1());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr1Context* e) const
{
  auto multiplicative = [&](auto* c) {
    dataflow_type l = infer_type(c->expr2());
    dataflow_type r = infer_type(c->expr1());
    if (!is_numeric(l) || l != r)
      type_fail(c, "arithmetic needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return l;
  };

  if (auto c = dynamic_cast<ChipsParser::MULTContext*>(e)) return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::DIVContext*>(e)) return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::MODContext*>(e))
  {
    dataflow_type l = infer_type(c->expr2());
    dataflow_type r = infer_type(c->expr1());
    if (l != dataflow_type::INT || r != dataflow_type::INT)
      type_fail(c, "modulo needs int operands, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::INT;
  }
  if (auto c = dynamic_cast<ChipsParser::NOTContext*>(e))
  {
    dataflow_type t = infer_type(c->expr2());
    if (t != dataflow_type::BOOL) type_fail(c, "'!' needs a bool operand, got " + type_name(t));
    return dataflow_type::BOOL;
  }
  if (auto c = dynamic_cast<ChipsParser::PassExpr2Context*>(e)) return infer_type(c->expr2());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr2Context* e) const
{
  if (dynamic_cast<ChipsParser::IntLiteralContext*>(e)) return dataflow_type::INT;
  if (dynamic_cast<ChipsParser::FloatLiteralContext*>(e)) return dataflow_type::FLOAT;
  if (dynamic_cast<ChipsParser::BoolLiteralContext*>(e)) return dataflow_type::BOOL;

  if (auto c = dynamic_cast<ChipsParser::VarContext*>(e))
  {
    check_suffixes(c->suffixes());
    return lookup_variable(c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::VarContextContext*>(e))
  {
    check_suffixes(c->suffixes());
    return lookup_variable("ctx." + c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::ParensContext*>(e)) return infer_type(c->expr());

  if (auto c = dynamic_cast<ChipsParser::CastAsContext*>(e))
  {
    ChipsParser::CastContext* cast = c->cast();
    dataflow_type target;
    if (dynamic_cast<ChipsParser::IntTypeContext*>(cast->df_type())) target = dataflow_type::INT;
    else if (dynamic_cast<ChipsParser::FloatTypeContext*>(cast->df_type())) target = dataflow_type::FLOAT;
    else type_fail(cast, "cannot cast to bool");
    dataflow_type operand = infer_type(cast->expr());
    if (!is_numeric(operand)) type_fail(cast, "cast needs a numeric operand, got " + type_name(operand));
    return target;
  }

  if (auto c = dynamic_cast<ChipsParser::FunctionContext*>(e))
  {
    std::string name = c->IDENTIFIER()->getText();
    std::vector<ChipsParser::ExprContext*> args = c->expr();

    if (name == "range" || name == "zeros" || name == "ones")
    {
      if (args.size() != 1) type_fail(c, "'" + name + "' takes exactly one int parameter");
      dataflow_type t = infer_type(args[0]);
      if (t != dataflow_type::INT) type_fail(c, "'" + name + "' takes an int parameter, got " + type_name(t));
      return dataflow_type::INT;
    }
    if (name == "randin01")
    {
      if (!args.empty()) type_fail(c, "'randin01' takes no parameter");
      return dataflow_type::FLOAT;
    }
    if (name == "is_fresh")
    {
      if (args.size() != 1) type_fail(c, "'is_fresh' takes exactly one parameter");
      infer_type(args[0]);
      return dataflow_type::BOOL;
    }
    type_fail(c, "unknown function '" + name + "'");
  }

  type_fail(e, "unsupported expression");
}




// Visit methods

std::any chips_ast_builder::visitProgram(ChipsParser::ProgramContext *ctx)
{
  std::vector<definition_variant> defs{};
  for (ChipsParser::PreambleContext* def : ctx->preamble())
  {
    definition_variant dv = std::any_cast<definition_variant>(def->accept(this));
    defs.push_back(dv);
  }

  system_section_node system =  std::any_cast<system_section_node>(ctx->system()->accept(this));
  return program_node(
      line_of(ctx),
      col_of(ctx),
      std::string("ChipsModel"),
      preamble_section_node(0,0,defs),
      system
    );
}

std::any chips_ast_builder::visitSystem(ChipsParser::SystemContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) 
{
    return ctx->function_def()->accept(this);
}


std::any chips_ast_builder::visitCollectiveOperationDefinition(
    ChipsParser::CollectiveOperationDefinitionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitObject_def(ChipsParser::Object_defContext *ctx) 
{
  m_current_def_name = ctx->IDENTIFIER()->getText();
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNode_mapping(ChipsParser::Node_mappingContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) 
{
  return ctx->p_function_def()->accept(this);
}


std::any
chips_ast_builder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitL_function_def(ChipsParser::L_function_defContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitP_function_def(ChipsParser::P_function_defContext *ctx)
{
  m_current_def_name = std::string(ctx->IDENTIFIER()->getText());
  std::vector<function_parameter_variant> parameters{};
  std::vector<physical_parameter_variant> sensors{};
  with_section with = std::any_cast<with_section>(ctx->with_section()->accept(this));
  init_section init = std::any_cast<init_section>(ctx->init_section()->accept(this));
  then_section then = std::any_cast<then_section>(ctx->then_section()->accept(this));
  std::vector<function_output_variant> outputs{};
  std::vector<physical_output_variant> actuators{};

  return definition_variant(make_node<physical_definition>(
    line_of(ctx),
    col_of(ctx),
    ctx->IDENTIFIER()->getText(), parameters, sensors,
    with, init, then,
    outputs, actuators
  ));
}


std::any chips_ast_builder::visitC_signature(ChipsParser::C_signatureContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_keywords(ChipsParser::C_keywordsContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitWith_section(ChipsParser::With_sectionContext *ctx) 
{
  with_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::With_statementContext* stmt : ctx->with_statement())
  {
    section.add_statement(std::any_cast<node_statement_variant>(stmt->accept(this)));
  }
  return section;
}

std::any chips_ast_builder::visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx)
{
  auto* decl = make_node<node_element_declaration<node_element::CHANNEL>>(
      line_of(ctx),
      col_of(ctx),
      ctx->IDENTIFIER(0)->getText(),
      ctx->IDENTIFIER(1)->getText()
  );
  return node_statement_variant(decl);
}



template<dataflow_type dft>
node_statement_variant build_contextual_declaration(
    chips_ast_builder& builder,
    ChipsParser::ContextualDeclarationContext* ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>& dims)
{
  using decl_t = typename DfTypeToContextualDeclType<dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  std::optional<rvalue_primitive_variant> init;
  if (ctx->expr() != nullptr)
  {
    dataflow_type t = builder.infer_type(ctx->expr());
    if (t != dft)
    {
      builder.type_fail(ctx->expr(), "contextual variable '" + name + "' is declared " +
                        type_name(dft) + " but initialized with " + type_name(t));
    }
    init = std::any_cast<rvalue_primitive_variant>(ctx->expr()->accept(&builder));
  }

  contextual_variable<dft> variable(line, column, name, dims);
  decl_t* decl = builder.make_node<decl_t>(line, column, variable, name);
  decl->m_variable_type.set_declaration(decl);
  if (init) decl->set_initializer(*init);

  builder.declare_contextual(name, dft);
  return node_statement_variant(decl);
}
  
std::any chips_ast_builder::visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx)
{
  dataflow_type type = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));

  switch (type)
  {
    case dataflow_type::INT:
      return build_contextual_declaration<dataflow_type::INT>(*this, ctx, dims);
    case dataflow_type::FLOAT:
      return build_contextual_declaration<dataflow_type::FLOAT>(*this, ctx, dims);
    case dataflow_type::BOOL:
      return build_contextual_declaration<dataflow_type::BOOL>(*this, ctx, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitContextualDeclaration");
}

std::any chips_ast_builder::visitWithRegularStatement(
    ChipsParser::WithRegularStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitInit_section(ChipsParser::Init_sectionContext *ctx)
{
  init_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext* stmt : ctx->statement())
  {
    section.add_statement(std::any_cast<primitive_statement_variant>(stmt->accept(this)));
  }
  return section;
}

std::any chips_ast_builder::visitThen_section(ChipsParser::Then_sectionContext *ctx)
{
  then_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext* stmt : ctx->statement())
  {
    section.add_statement(std::any_cast<primitive_statement_variant>(stmt->accept(this)));
  }
  return section;
}

namespace {
constexpr expression_env PRIM = expression_env::PRIMITIVE;
using dims_t = std::vector<int_rvalue_expression_variant<PRIM>>;

template<dataflow_type dft, expression_env e> using gt_t = chips::gt<e, dft>;
template<dataflow_type dft, expression_env e> using lt_t = chips::lt<e, dft>;
template<dataflow_type dft, expression_env e> using geq_t = chips::geq<e, dft>;
template<dataflow_type dft, expression_env e> using leq_t = chips::leq<e, dft>;

dataflow_type type_of(const rvalue_primitive_variant& v)
{
  switch (v.index())
  {
    case 0: return dataflow_type::INT;
    case 1: return dataflow_type::FLOAT;
    default: return dataflow_type::BOOL;
  }
}

template<dataflow_type dft>
rvalue<dft, PRIM>* as_rvalue(const rvalue_primitive_variant& v)
{
  return std::get<rvalue<dft, PRIM>*>(v);
}

rvalue_primitive_variant eval(chips_ast_builder& b, antlr4::tree::ParseTree* t)
{
  return std::any_cast<rvalue_primitive_variant>(t->accept(&b));
}

template<typename Variant, typename Base, std::size_t I = 0>
Variant narrow(Base* p)
{
  if constexpr (I == std::variant_size_v<Variant>)
  {
    throw std::runtime_error("cannot narrow expression node");
  }
  else
  {
    using Alt = std::variant_alternative_t<I, Variant>;
    if (Alt q = dynamic_cast<Alt>(p)) return Variant(q);
    return narrow<Variant, Base, I + 1>(p);
  }
}

template<template<dataflow_type, expression_env> class Node, dataflow_type dft>
rvalue_primitive_variant build_binary(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                      const rvalue_primitive_variant& l, const rvalue_primitive_variant& r)
{
  using node_t = Node<dft, PRIM>;
  return rvalue_primitive_variant(
      b.make_node<node_t>(line_of(ctx), col_of(ctx), as_rvalue<dft>(l), as_rvalue<dft>(r)));
}

template<template<dataflow_type, expression_env> class Node>
rvalue_primitive_variant build_numeric(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                       const rvalue_primitive_variant& l, const rvalue_primitive_variant& r)
{
  switch (type_of(l))
  {
    case dataflow_type::INT: return build_binary<Node, dataflow_type::INT>(b, ctx, l, r);
    case dataflow_type::FLOAT: return build_binary<Node, dataflow_type::FLOAT>(b, ctx, l, r);
    default: break;
  }
  throw std::runtime_error("numeric operands expected");
}

template<template<dataflow_type, expression_env> class Node>
rvalue_primitive_variant build_any(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                   const rvalue_primitive_variant& l, const rvalue_primitive_variant& r)
{
  switch (type_of(l))
  {
    case dataflow_type::INT: return build_binary<Node, dataflow_type::INT>(b, ctx, l, r);
    case dataflow_type::FLOAT: return build_binary<Node, dataflow_type::FLOAT>(b, ctx, l, r);
    case dataflow_type::BOOL: return build_binary<Node, dataflow_type::BOOL>(b, ctx, l, r);
  }
  throw std::runtime_error("unknown dataflow_type");
}

template<template<dataflow_type, expression_env> class Node>
rvalue_primitive_variant build_unary_numeric(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                             const rvalue_primitive_variant& operand)
{
  switch (type_of(operand))
  {
    case dataflow_type::INT:
      return rvalue_primitive_variant(
          b.make_node<Node<dataflow_type::INT, PRIM>>(line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(operand)));
    case dataflow_type::FLOAT:
      return rvalue_primitive_variant(
          b.make_node<Node<dataflow_type::FLOAT, PRIM>>(line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::FLOAT>(operand)));
    default: break;
  }
  throw std::runtime_error("numeric operand expected");
}

template<dataflow_type dft>
rvalue_primitive_variant build_var(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                   const std::string& name, const dims_t& dims)
{
  auto* var = b.make_node<dataflow_primitive_variable<dft>>(line_of(ctx), col_of(ctx), name, dims_t{});
  return rvalue_primitive_variant(
      b.make_node<variable_expression<dft, PRIM>>(line_of(ctx), col_of(ctx), var, dims));
}

template<dataflow_type dft>
rvalue_primitive_variant build_ctx_var(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                       const std::string& name, const dims_t& dims)
{
  auto* var = b.make_node<contextual_variable<dft>>(line_of(ctx), col_of(ctx), name, dims_t{});
  return rvalue_primitive_variant(
      b.make_node<variable_contextual_expression<dft, PRIM>>(line_of(ctx), col_of(ctx), var, dims));
}

template<dataflow_type dft>
rvalue_primitive_variant build_function(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                        const std::string& name, const std::vector<rvalue_primitive_variant>& params)
{
  return rvalue_primitive_variant(
      b.make_node<chips::function<dft, PRIM>>(line_of(ctx), col_of(ctx), name, params));
}

template<dataflow_type dft>
rvalue_primitive_variant build_cast(chips_ast_builder& b, antlr4::ParserRuleContext* ctx,
                                    const rvalue_primitive_variant& operand)
{
  constexpr dataflow_type other = dft == dataflow_type::INT ? dataflow_type::FLOAT : dataflow_type::INT;
  if (type_of(operand) == dft) return operand;
  return rvalue_primitive_variant(
      b.make_node<cast_as<dft, PRIM>>(line_of(ctx), col_of(ctx), as_rvalue<other>(operand)));
}
}


std::any chips_ast_builder::visitLT(ChipsParser::LTContext *ctx)
{
  infer_type(ctx);
  return build_numeric<lt_t>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}


std::any chips_ast_builder::visitGT(ChipsParser::GTContext *ctx)
{
  infer_type(ctx);
  return build_numeric<gt_t>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}
std::any chips_ast_builder::visitLEQ(ChipsParser::LEQContext *ctx)
{
  infer_type(ctx);
  return build_numeric<leq_t>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}

std::any chips_ast_builder::visitGEQ(ChipsParser::GEQContext *ctx)
{
  infer_type(ctx);
  return build_numeric<geq_t>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}

std::any chips_ast_builder::visitNEQ(ChipsParser::NEQContext *ctx)
{
  infer_type(ctx);
  return build_any<chips::neq>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}

std::any chips_ast_builder::visitEQ(ChipsParser::EQContext *ctx)
{
  infer_type(ctx);
  return build_any<chips::eq>(*this, ctx, eval(*this, ctx->expr0()), eval(*this, ctx->expr()));
}


std::any chips_ast_builder::visitAND(ChipsParser::ANDContext *ctx)
{
  infer_type(ctx);
  rvalue_primitive_variant l = eval(*this, ctx->expr0());
  rvalue_primitive_variant r = eval(*this, ctx->expr());
  return rvalue_primitive_variant(make_node<and_operator<PRIM>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitOR(ChipsParser::ORContext *ctx)
{
  infer_type(ctx);
  rvalue_primitive_variant l = eval(*this, ctx->expr0());
  rvalue_primitive_variant r = eval(*this, ctx->expr());
  return rvalue_primitive_variant(make_node<or_operator<PRIM>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx)
{
  return ctx->expr0()->accept(this);
}

std::any chips_ast_builder::visitPLUS(ChipsParser::PLUSContext *ctx)
{
  infer_type(ctx);
  return build_numeric<chips::plus>(*this, ctx, eval(*this, ctx->expr01()), eval(*this, ctx->expr0()));
}

std::any chips_ast_builder::visitSUB(ChipsParser::SUBContext *ctx)
{
  infer_type(ctx);
  return build_numeric<chips::minus>(*this, ctx, eval(*this, ctx->expr01()), eval(*this, ctx->expr0()));
}

std::any chips_ast_builder::visitPassExpr01(ChipsParser::PassExpr01Context *ctx)
{
  return ctx->expr01()->accept(this);
}

std::any chips_ast_builder::visitNegate(ChipsParser::NegateContext *ctx)
{
  infer_type(ctx);
  return build_unary_numeric<chips::uminus_operator>(*this, ctx, eval(*this, ctx->expr1()));
}

std::any chips_ast_builder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx)
{
  return ctx->expr1()->accept(this);
}

std::any chips_ast_builder::visitMULT(ChipsParser::MULTContext *ctx)
{
  infer_type(ctx);
  return build_numeric<chips::mult>(*this, ctx, eval(*this, ctx->expr2()), eval(*this, ctx->expr1()));
}

std::any chips_ast_builder::visitDIV(ChipsParser::DIVContext *ctx)
{
  infer_type(ctx);
  return build_numeric<chips::div>(*this, ctx, eval(*this, ctx->expr2()), eval(*this, ctx->expr1()));
}


std::any chips_ast_builder::visitMOD(ChipsParser::MODContext *ctx)
{
  infer_type(ctx);
  rvalue_primitive_variant l = eval(*this, ctx->expr2());
  rvalue_primitive_variant r = eval(*this, ctx->expr1());
  return rvalue_primitive_variant(make_node<mod<PRIM>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(l), as_rvalue<dataflow_type::INT>(r)));
}

std::any chips_ast_builder::visitNOT(ChipsParser::NOTContext *ctx)
{
  infer_type(ctx);
  rvalue_primitive_variant operand = eval(*this, ctx->expr2());
  return rvalue_primitive_variant(make_node<not_operator<PRIM>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(operand)));
}

std::any chips_ast_builder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx)
{
  return ctx->expr2()->accept(this);
}

std::any chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx)
{
  return rvalue_primitive_variant(make_node<direct<dataflow_type::INT, PRIM>>(
      line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
}

std::any chips_ast_builder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx)
{
  return rvalue_primitive_variant(make_node<direct<dataflow_type::FLOAT, PRIM>>(
      line_of(ctx), col_of(ctx), std::stod(ctx->FLOAT()->getText())));
}

std::any chips_ast_builder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx)
{
  return rvalue_primitive_variant(make_node<direct<dataflow_type::BOOL, PRIM>>(
      line_of(ctx), col_of(ctx), ctx->BOOL()->getText() == "true"));
}

std::any chips_ast_builder::visitVar(ChipsParser::VarContext *ctx)
{
  dataflow_type t = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  dims_t dims = std::any_cast<dims_t>(ctx->suffixes()->accept(this));
  switch (t)
  {
    case dataflow_type::INT: return build_var<dataflow_type::INT>(*this, ctx, name, dims);
    case dataflow_type::FLOAT: return build_var<dataflow_type::FLOAT>(*this, ctx, name, dims);
    case dataflow_type::BOOL: return build_var<dataflow_type::BOOL>(*this, ctx, name, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitVar");
}
std::any chips_ast_builder::visitParens(ChipsParser::ParensContext *ctx)
{
  return ctx->expr()->accept(this);
}

std::any chips_ast_builder::visitVarContext(ChipsParser::VarContextContext *ctx)
{
  dataflow_type t = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  dims_t dims = std::any_cast<dims_t>(ctx->suffixes()->accept(this));
  switch (t)
  {
    case dataflow_type::INT: return build_ctx_var<dataflow_type::INT>(*this, ctx, name, dims);
    case dataflow_type::FLOAT: return build_ctx_var<dataflow_type::FLOAT>(*this, ctx, name, dims);
    case dataflow_type::BOOL: return build_ctx_var<dataflow_type::BOOL>(*this, ctx, name, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitVarContext");
}

std::any chips_ast_builder::visitFunction(ChipsParser::FunctionContext *ctx)
{
  dataflow_type t = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_primitive_variant> params{};
  for (ChipsParser::ExprContext* e : ctx->expr())
  {
    params.push_back(eval(*this, e));
  }
  switch (t)
  {
    case dataflow_type::INT: return build_function<dataflow_type::INT>(*this, ctx, name, params);
    case dataflow_type::FLOAT: return build_function<dataflow_type::FLOAT>(*this, ctx, name, params);
    case dataflow_type::BOOL: return build_function<dataflow_type::BOOL>(*this, ctx, name, params);
  }
  throw std::runtime_error("unknown dataflow_type in visitFunction");
}

std::any chips_ast_builder::visitCastAs(ChipsParser::CastAsContext *ctx)
{
  infer_type(ctx);
  return ctx->cast()->accept(this);
}

std::any chips_ast_builder::visitCast(ChipsParser::CastContext *ctx)
{
  dataflow_type target = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  rvalue_primitive_variant operand = eval(*this, ctx->expr());
  switch (target)
  {
    case dataflow_type::INT: return build_cast<dataflow_type::INT>(*this, ctx, operand);
    case dataflow_type::FLOAT: return build_cast<dataflow_type::FLOAT>(*this, ctx, operand);
    default: break;
  }
  throw std::runtime_error("cast to bool is not allowed");
}


std::any chips_ast_builder::visitCStoplessExpression(
    ChipsParser::CStoplessExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStop(ChipsParser::StopContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCLT(ChipsParser::CLTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCGT(ChipsParser::CGTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCLEQ(ChipsParser::CLEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCGEQ(ChipsParser::CGEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNEQ(ChipsParser::CNEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCEQ(ChipsParser::CEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCAND(ChipsParser::CANDContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCOR(ChipsParser::CORContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCPLUS(ChipsParser::CPLUSContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCSUB(ChipsParser::CSUBContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNegate(ChipsParser::CNegateContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCMULT(ChipsParser::CMULTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCDIV(ChipsParser::CDIVContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCMOD(ChipsParser::CMODContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNOT(ChipsParser::CNOTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCVariableExpression(
    ChipsParser::CVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCINT(ChipsParser::CINTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCFLOAT(ChipsParser::CFLOATContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCBOOL(ChipsParser::CBOOLContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitINPUT(ChipsParser::INPUTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCtxVariableExpression(
    ChipsParser::CtxVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitChanneledAccuExpression(
    ChipsParser::ChanneledAccuExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCCastAs(ChipsParser::CCastAsContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_cast(ChipsParser::C_castContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSuffixes(ChipsParser::SuffixesContext *ctx)
{
  check_suffixes(ctx);
  dims_t dims{};
  for (ChipsParser::ExprContext* e : ctx->expr())
  {
    dims.push_back(narrow<int_rvalue_expression_variant<PRIM>>(as_rvalue<dataflow_type::INT>(eval(*this, e))));
  }
  return dims;
}




std::any chips_ast_builder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableVariableExpression(
    ChipsParser::SSuffixableVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableFunctionCallExpression(
    ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableBlockOutputExpression(
    ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitBlock(ChipsParser::BlockContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitLoop_in(ChipsParser::Loop_inContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLoop_statement(ChipsParser::Loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitS_if_else_statement(
    ChipsParser::S_if_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_if_else_statement(
    ChipsParser::C_if_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitIf_statement(ChipsParser::If_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


template<dataflow_type dft>
primitive_statement_variant build_primitive_declaration(
    chips_ast_builder& builder,
    ChipsParser::StatementDeclarationContext* ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>& dims)
{
  using decl_t = dataflow_declaration<dft, statement_env::DEFINITION>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  dataflow_primitive_variable<dft> variable(line, column, ctx->IDENTIFIER()->getText(), dims);
  decl_t* decl = builder.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);
  return primitive_statement_variant(static_cast<primitive_statement<recurring_statement::DECLARATION>*>(decl));
}


std::any chips_ast_builder::visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx)
{
  dataflow_type type = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));

  switch (type)
  {
    case dataflow_type::INT:
      return build_primitive_declaration<dataflow_type::INT>(*this, ctx, dims);
    case dataflow_type::FLOAT:
      return build_primitive_declaration<dataflow_type::FLOAT>(*this, ctx, dims);
    case dataflow_type::BOOL:
      return build_primitive_declaration<dataflow_type::BOOL>(*this, ctx, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitStatementDeclaration");
}


std::any chips_ast_builder::visitStatementAssignment(
    ChipsParser::StatementAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


template<dataflow_type dft>
primitive_statement_variant build_contextual_assignment(
    chips_ast_builder& builder,
    ChipsParser::StatementContextualAssignmentContext* ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>& dims,
    const rvalue_primitive_variant& rhs)
{
  using assign_t = dataflow_assignment<dft, statement_env::DEFINITION>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto* var = builder.make_node<contextual_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>{});
  auto* lhs = builder.make_node<variable_contextual_expression<dft, expression_env::PRIMITIVE>>(var);
  auto* assign = builder.make_node<assign_t>(line, column, lhs, std::get<rvalue<dft, expression_env::PRIMITIVE>*>(rhs));
  return primitive_statement_variant(static_cast<primitive_statement<recurring_statement::ASSIGNMENT>*>(assign));
}


std::any chips_ast_builder::visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx)
{
  std::string name = ctx->IDENTIFIER()->getText();
  std::optional<dataflow_type> type = find_symbol(name);
  if (!type)
  {
    throw std::runtime_error("undeclared contextual variable '" + name + "' at line " + std::to_string(line_of(ctx)));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  auto rhs = std::any_cast<rvalue_primitive_variant>(ctx->expr()->accept(this));

  switch (*type)
  {
    case dataflow_type::INT:
      return build_contextual_assignment<dataflow_type::INT>(*this, ctx, dims, rhs);
    case dataflow_type::FLOAT:
      return build_contextual_assignment<dataflow_type::FLOAT>(*this, ctx, dims, rhs);
    case dataflow_type::BOOL:
      return build_contextual_assignment<dataflow_type::BOOL>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error("unknown dataflow_type in visitStatementContextualAssignment");
}


std::any chips_ast_builder::visitStatementLoop(ChipsParser::StatementLoopContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementIf(ChipsParser::StatementIfContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitRegularStatement(ChipsParser::RegularStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSBlockOutputExpression(
    ChipsParser::SBlockOutputExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSCollectiveCastExpression(
    ChipsParser::SCollectiveCastExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollective_operation(
    ChipsParser::Collective_operationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveVariableDeclaration(
    ChipsParser::CollectiveVariableDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveAssignment(
    ChipsParser::CollectiveAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitContextualAssignment(
    ChipsParser::ContextualAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveLoopStatement(
    ChipsParser::CollectiveLoopStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveIfElseStatement(
    ChipsParser::CollectiveIfElseStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveIfStatement(
    ChipsParser::CollectiveIfStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNamed_output(ChipsParser::Named_outputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitIntType(ChipsParser::IntTypeContext *ctx)
{
  return dataflow_type::INT;
}

std::any chips_ast_builder::visitFloatType(ChipsParser::FloatTypeContext *ctx)
{
  return dataflow_type::FLOAT;
}

std::any chips_ast_builder::visitBoolType(ChipsParser::BoolTypeContext *ctx)
{
  return dataflow_type::BOOL;
}


std::any chips_ast_builder::visitFunctionParameterType(
    ChipsParser::FunctionParameterTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSensorParameterType(
    ChipsParser::SensorParameterTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCdf_full_declaration(
    ChipsParser::Cdf_full_declarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}

#undef UNIMPLEMENTED_METHOD
