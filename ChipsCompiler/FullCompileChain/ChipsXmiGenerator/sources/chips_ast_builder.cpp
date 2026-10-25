#include "chips_ast_builder.hpp"
#include "../generated/ChipsParser.h"
#include "meta_type_conversions.hpp"
#include "metamodel_enums.hpp"
#include "type_utils.hpp"
#include "ast_node_definitions.tpp"
#include <any>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#define UNIMPLEMENTED_METHOD \
  throw std::runtime_error(std::string("unimplemented ") + __func__ + " error.")

#define VERBOSE false

#define VERBOSE_VISIT_ENTER                              \
  do                                                     \
  {                                                      \
    if (VERBOSE)                                         \
      std::cout << "entering " << __func__ << std::endl; \
  } while (0);

#define VERBOSE_VISIT_LEAVE                             \
  do                                                    \
  {                                                     \
    if (VERBOSE)                                        \
      std::cout << "leaving " << __func__ << std::endl; \
  } while (0);

template <typename Variant>
void append_statements(std::vector<Variant> &target, const std::any &visited) {
  try
  {
    const auto *statements = std::any_cast<std::vector<Variant>>(&visited);
    if (statements == nullptr)
    {
      throw std::runtime_error(std::string("statement visitor returned ") + visited.type().name() +
                               " instead of a vector of statements");
    }
    target.insert(target.end(), statements->begin(), statements->end());
  }
  catch (const std::exception &e)
  {
    std::cerr << "trying to any_cast:\n"
              << visited.type().name();
    std::cerr << e.what() << '\n';
  }
}

int line_of(antlr4::ParserRuleContext *c) { return c->getStart()->getLine(); }
int col_of(antlr4::ParserRuleContext *c) {
  return c->getStart()->getCharPositionInLine();
}

template <typename V>
V *resolve_variable_node(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                         const std::string &name) {
  if (V *node = b.venv.lookup_variable_node<V>(name))
  {
    return node;
  }
  semantic_fail(ctx, "cannot resolve the declaration of variable '" + name + "'");
}

template <dataflow_type dft>
contextual_variable<dft> *resolve_contextual_node(chips_ast_builder &b,
                                                  antlr4::ParserRuleContext *ctx,
                                                  const std::string &name) {
  if (auto *node = b.venv.lookup_contextual_node<contextual_variable<dft>>("ctx." + name))
  {
    return node;
  }
  semantic_fail(ctx, "cannot resolve the declaration of contextual variable 'ctx." + name + "'");
}

template <block_type bt>
block_variable<bt> *resolve_block_node(chips_ast_builder &b,
                                       antlr4::ParserRuleContext *ctx,
                                       const std::string &name) {
  if (auto *node = b.venv.lookup_block_node<bt>(name))
  {
    return node;
  }
  semantic_fail(ctx, "cannot resolve the declaration of block '" + name + "'");
}

template <typename F>
auto by_type(dataflow_type type, F &&f) -> decltype(f(
    std::integral_constant<dataflow_type, dataflow_type::INT>{})) {
  switch (type)
  {
  case dataflow_type::INT:
    return f(std::integral_constant<dataflow_type, dataflow_type::INT>{});
  case dataflow_type::FLOAT:
    return f(std::integral_constant<dataflow_type, dataflow_type::FLOAT>{});
  case dataflow_type::BOOL:
    return f(std::integral_constant<dataflow_type, dataflow_type::BOOL>{});
  }
  throw std::runtime_error("unknown dataflow_type");
}

template <typename F>
std::any by_env(const chips_ast_builder &b, F &&f) {
  if (b.venv.system_reached())
  {
    return f(std::integral_constant<expression_env, expression_env::SYSTEM>{});
  }
  return f(std::integral_constant<expression_env, expression_env::PRIMITIVE>{});
}

template <dataflow_type dft, expression_env expenv>
rvalue<dft, expenv> *as_rvalue(const rvalue_variant<expenv> &v) {
  if constexpr (expenv == expression_env::COLLECTIVE)
  {
    rvalue<dft, expenv> *converted = std::visit(
        [](auto *p) -> rvalue<dft, expenv> *
        {
          if (auto *i = dynamic_cast<input *>(p))
          {
            return i;
          }
          if (auto *s = dynamic_cast<stop *>(p))
          {
            return s;
          }
          return nullptr;
        },
        v);
    if (converted != nullptr)
    {
      return converted;
    }
  }
  return std::get<rvalue<dft, expenv> *>(v);
}

template <expression_env expenv>
bool is_free(const rvalue_variant<expenv> &v) {
  if constexpr (expenv == expression_env::COLLECTIVE)
  {
    return std::visit(
        [](auto *p)
        {
          return dynamic_cast<input *>(p) != nullptr ||
                 dynamic_cast<stop *>(p) != nullptr;
        },
        v);
  }
  return false;
}

template <expression_env expenv>
rvalue_variant<expenv> eval(chips_ast_builder &b, antlr4::tree::ParseTree *t) {
  return std::any_cast<rvalue_variant<expenv>>(t->accept(&b));
}

template <typename Variant, typename Base, std::size_t I = 0>
Variant narrow(Base *p) {
  if constexpr (I == std::variant_size_v<Variant>)
  {
    throw std::runtime_error("cannot narrow expression node");
  }
  else
  {
    using Alt = std::variant_alternative_t<I, Variant>;
    if (Alt q = dynamic_cast<Alt>(p))
      return Variant(q);
    return narrow<Variant, Base, I + 1>(p);
  }
}

template <statement_env stenv, recurring_statement recstt, typename Node>
std::vector<typename SttEnvToSttVariant<stenv>::type> as_statement(Node *node) {
  return {typename SttEnvToSttVariant<stenv>::type(static_cast<statement<stenv, recstt> *>(node))};
}

template <statement_env stenv, typename StmtCtx>
std::vector<typename SttEnvToSttVariant<stenv>::type>
visit_body(chips_ast_builder &b, const std::vector<StmtCtx *> &stmts) {
  using body_t = typename SttEnvToSttVariant<stenv>::type;
  std::vector<body_t> body{};
  visitor_env::scope_guard guard(b.venv);
  for (StmtCtx *s : stmts)
  {
    append_statements(body, s->accept(&b));
  }
  return body;
}

template <statement_env stenv>
bool_rvalue_expression_variant<SttEnvToExpEnv<stenv>::value>
to_bool_condition(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                  const rvalue_variant<SttEnvToExpEnv<stenv>::value> &v) {
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  if constexpr (expenv == expression_env::COLLECTIVE)
  {
    input_constraint constraint = b.checker.inference.infer(ctx);

    if (constraint.contains_input)
    {
      b.checker.inference.force_input(ctx, dataflow_type::BOOL);
    }
  }
  auto *cond = std::get_if<rvalue<dataflow_type::BOOL, expenv> *>(&v);
  if (cond == nullptr)
  {
    type_fail(b.venv, ctx,
              "condition must be bool, got " +
                  type_name(dataflow_type_of(v)));
  }
  return narrow<bool_rvalue_expression_variant<expenv>>(*cond);
}

template <statement_env stenv, typename StmtCtx>
std::vector<typename SttEnvToSttVariant<stenv>::type> build_if(chips_ast_builder &b,
                                                               antlr4::ParserRuleContext *ctx,
                                                               antlr4::ParserRuleContext *cond_ctx,
                                                               const std::vector<StmtCtx *> &stmts) {
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto condition = to_bool_condition<stenv>(
      b, cond_ctx, std::any_cast<rvalue_variant<expenv>>(cond_ctx->accept(&b)));
  auto body = visit_body<stenv>(b, stmts);
  auto *node = b.make_node<if_statement<stenv>>(line, column, condition, if_section<stenv>(line, column, body));
  return as_statement<stenv, recurring_statement::IF>(node);
}

template <statement_env stenv, typename IfCtx, typename StmtCtx>
std::vector<typename SttEnvToSttVariant<stenv>::type>
build_if_else(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
              IfCtx *if_ctx, const std::vector<StmtCtx *> &else_stmts) {
  using variant_t = typename SttEnvToSttVariant<stenv>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto visited = std::any_cast<std::vector<variant_t>>(if_ctx->accept(&b));
  auto *if_node = static_cast<if_statement<stenv> *>(
      std::get<statement<stenv, recurring_statement::IF> *>(visited.front()));
  auto else_body = visit_body<stenv>(b, else_stmts);
  auto *node = b.make_node<if_else_statement<stenv>>(
      line, column, *if_node, else_section<stenv>(line, column, else_body));
  return as_statement<stenv, recurring_statement::IF>(node);
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_iterated_variable(
    chips_ast_builder &b, ChipsParser::Loop_inContext *ctx,
    const std::vector<int_rvalue_expression_variant<expenv>> &dims) {
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto *var = resolve_variable_node<var_t>(b, ctx, ctx->IDENTIFIER()->getText());
  auto *expr =
      b.make_node<variable_expression<dft, expenv>>(line, column, var, dims);
  return rvalue_variant<expenv>(static_cast<rvalue<dft, expenv> *>(expr));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_iterated_variable(
    chips_ast_builder &b, ChipsParser::C_loop_inContext *ctx,
    const std::vector<int_rvalue_expression_variant<expenv>> &dims) {
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto *var = resolve_variable_node<var_t>(b, ctx, ctx->IDENTIFIER()->getText());
  auto *expr =
      b.make_node<variable_expression<dft, expenv>>(line, column, var, dims);
  return rvalue_variant<expenv>(static_cast<rvalue<dft, expenv> *>(expr));
}

template <expression_env expenv>
iterable_variant<expenv> build_iterable(chips_ast_builder &b, ChipsParser::Loop_inContext *ctx) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  if (ctx->L_PARENTH() != nullptr)
  {
    std::vector<rvalue_variant<expenv>> params{};
    for (ChipsParser::ExprContext *e : ctx->expr())
    {
      params.push_back(std::any_cast<rvalue_variant<expenv>>(e->accept(&b)));
    }

    if (params.size() != 1 || !std::holds_alternative<rvalue<dataflow_type::INT, expenv> *>(params[0]))
    {
      type_fail(b.venv, ctx, "'" + name + "' takes exactly one int parameter");
    }
    return iterable_variant<expenv>(
        b.make_node<chips::function<dataflow_type::INT, expenv>>(line, column, name, params));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expenv>>>(ctx->suffixes()->accept(&b));
  switch (resolve_variable(b.venv, name, ctx))
  {
  case dataflow_type::INT:
    return iterable_variant<expenv>(build_iterated_variable<dataflow_type::INT, expenv>(b, ctx, dims));
  case dataflow_type::FLOAT:
    return iterable_variant<expenv>(build_iterated_variable<dataflow_type::FLOAT, expenv>(b, ctx, dims));
  case dataflow_type::BOOL:
    return iterable_variant<expenv>(build_iterated_variable<dataflow_type::BOOL, expenv>(b, ctx, dims));
  }
  throw std::runtime_error("unknown dataflow_type in build_iterable");
}

template <expression_env expenv>
iterable_variant<expenv> build_iterable(chips_ast_builder &b,
                                        ChipsParser::C_loop_inContext *ctx) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  if (ctx->L_PARENTH() != nullptr)
  {
    std::vector<rvalue_variant<expenv>> params{};
    for (ChipsParser::C_exprContext *e : ctx->c_expr())
    {
      params.push_back(std::any_cast<rvalue_variant<expenv>>(e->accept(&b)));
    }

    if (params.size() != 1 ||
        !std::holds_alternative<rvalue<dataflow_type::INT, expenv> *>(
            params[0]))
    {
      type_fail(b.venv, ctx, "'" + name + "' takes exactly one int parameter");
    }
    return iterable_variant<expenv>(
        b.make_node<chips::function<dataflow_type::INT, expenv>>(line, column,
                                                                 name, params));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expenv>>>(ctx->c_suffixes()->accept(&b));

  auto variable = b.venv.lookup_variable(name);

  if (variable != std::nullopt)
  {
    switch (*variable)
    {
    case dataflow_type::INT:
      return iterable_variant<expenv>(
          build_iterated_variable<dataflow_type::INT, expenv>(b, ctx, dims));
    case dataflow_type::FLOAT:
      return iterable_variant<expenv>(
          build_iterated_variable<dataflow_type::FLOAT, expenv>(b, ctx, dims));
    case dataflow_type::BOOL:
      return iterable_variant<expenv>(
          build_iterated_variable<dataflow_type::BOOL, expenv>(b, ctx, dims));
    }
    throw std::runtime_error("unknown dataflow_type in build_iterable");
  }
  semantic_fail(ctx, std::string("cannot find the variable" + name));
}

template <expression_env expenv>
dataflow_type iterable_type(const iterable_variant<expenv> &v) {
  return dataflow_type_of(v);
}

template <statement_env stenv, dataflow_type dft, typename StmtCtx>
std::vector<typename SttEnvToSttVariant<stenv>::type>
build_foreach(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
              const std::string &name,
              const iterable_variant<SttEnvToExpEnv<stenv>::value> &iterable,
              const std::vector<StmtCtx *> &stmts) {
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  using decl_t = dataflow_declaration<dft, stenv>;
  using variable_t = typename SttEnvToVariableKind<dft, stenv>::type;
  using body_t = typename SttEnvToSttVariant<stenv>::type;

  int line = line_of(ctx);
  int column = col_of(ctx);

  variable_t variable(line, column, name,
                      std::vector<int_rvalue_expression_variant<expenv>>{});
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);

  std::vector<body_t> body{};
  {
    visitor_env::scope_guard guard(b.venv);
    b.venv.declare_variable<dft>(name);
    b.venv.declare_variable_node(name, &decl->m_variable);
    for (StmtCtx *s : stmts)
    {
      append_statements(body, s->accept(&b));
    }
  }

  auto *node = b.make_node<foreach_statement<stenv, dft>>(line, column, decl,
                                                          iterable, body);
  return as_statement<stenv, recurring_statement::FOREACH>(node);
}

template <block_type bt>
block_expression_variant build_block_expression(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const std::string &name,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>
        &dims) {
  auto *var = resolve_block_node<bt>(b, ctx, name);
  return block_expression_variant(
      b.make_node<system_variable_block_expression<bt>>(
          line_of(ctx), col_of(ctx), var, dims));
}

block_expression_variant make_block_expression(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const std::string &name,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>
        &dims) {
  switch (b.venv.lookup_block(name, ctx).first)
  {
  case block_type::LOGICAL:
    return build_block_expression<block_type::LOGICAL>(b, ctx, name, dims);
  case block_type::PHYSICAL:
    return build_block_expression<block_type::PHYSICAL>(b, ctx, name, dims);
  case block_type::OBJECT:
    return build_block_expression<block_type::OBJECT>(b, ctx, name, dims);
  }
  throw std::runtime_error("unknown block_type");
}

node_variable_expression *node_of(const block_expression_variant &block) {
  if (auto *p =
          std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(
              &block))
    return *p;
  if (auto *o =
          std::get_if<system_variable_block_expression<block_type::OBJECT> *>(
              &block))
    return *o;
  return nullptr;
}

functional_block_variant functional_of(antlr4::ParserRuleContext *ctx,
                                       const block_expression_variant &block) {
  if (auto *l =
          std::get_if<system_variable_block_expression<block_type::LOGICAL> *>(
              &block))
    return functional_block_variant(*l);
  if (auto *p =
          std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(
              &block))
    return functional_block_variant(*p);
  semantic_fail(ctx, "an object has neither parameters nor outputs");
}

template <block_type bt>
typename BlockTypeToBlockDef<bt>::type *
definition_of(const chips_ast_builder &b, const std::string &name) {
  if constexpr (bt == block_type::LOGICAL)
    return b.venv.lookup_logical(name);
  else if constexpr (bt == block_type::PHYSICAL)
    return b.venv.lookup_physical(name);
  else
    return b.venv.lookup_object(name);
}

template <block_type bt>
std::vector<system_statement_variant> build_block_declaration(
    chips_ast_builder &b, ChipsParser::ObjectDeclarationContext *ctx,
    typename BlockTypeToBlockDef<bt>::type *definition,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>
        &dims) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER(1)->getText();

  block_variable<bt> variable(line, column, name, dims);
  auto *decl =
      b.make_node<block_declaration<bt>>(line, column, definition, variable);
  decl->m_variable.m_declaration = decl;
  b.venv.declare_block(name, bt, ctx->IDENTIFIER(0)->getText(), &decl->m_variable);
  return {system_statement_variant(static_cast<system_statement<recurring_statement::DECLARATION> *>(decl))};
}

template <dataflow_kind dfk, dataflow_type dft, typename List>
feeder_variant build_output_feeder(chips_ast_builder &b,
                                   antlr4::ParserRuleContext *ctx,
                                   const functional_block_variant &block,
                                   List &outputs, const std::string &name) {
  for (auto &candidate : outputs)
  {
    auto *typed = std::get_if<function_output<dfk, dft> *>(&candidate);
    if (typed != nullptr && (*typed)->get_name() == name)
    {
      auto *node = b.make_node<feeder_block_expression<dfk, dft>>(
          line_of(ctx), col_of(ctx), block, *typed);
      return feeder_variant(static_cast<feeder<dfk, dft> *>(node));
    }
  }
  semantic_fail(ctx, "output '" + name + "' not found");
}

s_expr_variant resolve_block_output(chips_ast_builder &b,
                                    antlr4::ParserRuleContext *ctx,
                                    ChipsParser::BlockContext *block_ctx,
                                    const std::string &output) {
  auto block = std::any_cast<block_expression_variant>(block_ctx->accept(&b));
  std::string definition =
      b.venv.lookup_block(block_ctx->IDENTIFIER()->getText(), block_ctx).second;

  if (auto *channel = b.venv.lookup_channel(definition, output))
  {
    return s_expr_variant(b.make_node<channel_feeder>(line_of(ctx), col_of(ctx),
                                                      node_of(block), channel));
  }

  functional_block_variant source = functional_of(ctx, block);
  if (auto type = b.venv.lookup_actuator(definition, output))
  {
    auto *physical = b.venv.lookup_physical(definition);
    return s_expr_variant(by_type(*type, [&](auto t)
                                  {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_output_feeder<dataflow_kind::PHYSICAL, dft>(
          b, ctx, source, physical->m_actuators, output); }));
  }
  if (auto type = b.venv.lookup_output(definition, output))
  {
    auto *function = b.venv.lookup_function(definition);
    return s_expr_variant(by_type(*type, [&](auto t)
                                  {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_output_feeder<dataflow_kind::LOGICAL, dft>(
          b, ctx, source, function->get_outputs(), output); }));
  }
  semantic_fail(ctx,
                "'" + output +
                    "' is neither an output, an actuator nor a channel of '" +
                    definition + "'");
}

template <dataflow_kind dfk, dataflow_type dft, typename List>
std::vector<system_statement_variant>
feed_parameter(chips_ast_builder &b, ChipsParser::FeedingStatementContext *ctx,
               const functional_block_variant &block, List &parameters,
               const feeder_variant &source) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  function_parameter<dfk, dft> *parameter = nullptr;
  for (auto &candidate : parameters)
  {
    auto *typed = std::get_if<function_parameter<dfk, dft> *>(&candidate);
    if (typed != nullptr && (*typed)->get_name() == name)
    {
      parameter = *typed;
    }
  }
  auto *fed = std::get_if<feeder<dfk, dft> *>(&source);
  if (parameter == nullptr || fed == nullptr)
  {
    semantic_fail(ctx,
                  "parameter '" + name + "' cannot be fed by this expression");
  }
  auto *node = b.make_node<feeding_statement<dfk, dft>>(
      line, column, eater<dfk, dft>(line, column, block, parameter), *fed);
  return {system_statement_variant(static_cast<system_statement<recurring_statement::FEEDING> *>(node))};
}

template <dataflow_type dft>
feeder_variant as_feeder(rvalue<dft, expression_env::SYSTEM> *value) {
  return feeder_variant(
      static_cast<feeder<dataflow_kind::LOGICAL, dft> *>(value));
}

template <dataflow_type result, dataflow_kind dfk, dataflow_type inner_type>
feeder_variant build_collective_cast(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                     collective_function_definition *collective, feeder<dfk, inner_type> *inner) {
  auto *cast = b.make_node<collective_cast<dfk, result>>(line_of(ctx), col_of(ctx), collective, *inner);
  return feeder_variant(static_cast<feeder<dfk, result> *>(cast));
}

template <dataflow_type dft>
system_statement_variant build_system_declaration(
    chips_ast_builder &b, ChipsParser::StatementDeclarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>
        &dims) {
  using decl_t = dataflow_declaration<dft, statement_env::SYSTEM>;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_system_variable<dft> variable(line, column, name, dims);
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);
  b.venv.declare_variable<dft>(name);
  b.venv.declare_variable_node(name, &decl->m_variable);
  return system_statement_variant(
      static_cast<system_statement<recurring_statement::DECLARATION> *>(decl));
}

template <dataflow_type dft>
std::vector<system_statement_variant> build_system_assignment(
    chips_ast_builder &b, ChipsParser::StatementAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>
        &dims,
    const rvalue_variant<expression_env::SYSTEM> &rhs) {
  using assign_t = dataflow_assignment<dft, statement_env::SYSTEM>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = resolve_variable_node<dataflow_system_variable<dft>>(
      b, ctx, ctx->IDENTIFIER()->getText());
  auto *lhs = b.make_node<variable_expression<dft, expression_env::SYSTEM>>(
      line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, as_rvalue<dft>(rhs));
  return {system_statement_variant(static_cast<system_statement<recurring_statement::ASSIGNMENT> *>(assign))};
}

template <block_type bt>
std::vector<system_statement_variant> build_block_foreach(
    chips_ast_builder &b, ChipsParser::S_loop_statementContext *ctx,
    const std::string &name, system_variable_block_expression<bt> *iterable) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string definition = b.venv.lookup_block(iterable->get_variable()->get_name(), ctx).second;

  block_variable<bt> variable(
      line, column, name,
      std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{});
  auto *decl = b.make_node<block_declaration<bt>>(line, column, definition_of<bt>(b, definition), variable);
  decl->m_variable.m_declaration = decl;

  std::vector<system_statement_variant> body{};
  {
    visitor_env::scope_guard guard(b.venv);
    b.venv.declare_block(name, bt, definition, &decl->m_variable);
    for (ChipsParser::S_statementContext *stmt : ctx->s_statement())
    {
      append_statements(body, stmt->accept(&b));
    }
  }
  auto *node = b.make_node<block_foreach_statement<bt>>(line, column, decl, iterable, body);
  return {system_statement_variant(static_cast<system_statement<recurring_statement::FOREACH> *>(node))};
}

template <dataflow_type dft>
system_iterable_variant
build_system_iterable_variable(chips_ast_builder &b,
                               antlr4::ParserRuleContext *ctx,
                               const std::string &name) {
  auto *var = resolve_variable_node<dataflow_system_variable<dft>>(b, ctx, name);
  auto *expr = b.make_node<variable_expression<dft, expression_env::SYSTEM>>(
      line_of(ctx), col_of(ctx), var);
  return system_iterable_variant(iterable_variant<expression_env::SYSTEM>(
      rvalue_variant<expression_env::SYSTEM>(
          static_cast<rvalue<dft, expression_env::SYSTEM> *>(expr))));
}

static bool is_node_definition(ChipsParser::PreambleContext *def) {
  if (dynamic_cast<ChipsParser::ObjectDefinitionContext *>(def) != nullptr)
    return true;
  auto *function = dynamic_cast<ChipsParser::FunctionDefinitionContext *>(def);
  return function != nullptr &&
         dynamic_cast<ChipsParser::PhysicalDefinitionContext *>(function->function_def()) != nullptr;
}

// Visit methods

std::any chips_ast_builder::visitProgram(ChipsParser::ProgramContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::vector<ChipsParser::PreambleContext *> preambles = ctx->preamble();
  std::vector<std::optional<definition_variant>> slots(preambles.size());
  for (std::size_t i = 0; i < preambles.size(); ++i)
    if (is_node_definition(preambles[i]))
      slots[i] = std::any_cast<definition_variant>(preambles[i]->accept(this));
  for (std::size_t i = 0; i < preambles.size(); ++i)
    if (!slots[i].has_value())
      slots[i] = std::any_cast<definition_variant>(preambles[i]->accept(this));

  std::vector<definition_variant> defs{};
  for (const auto &slot : slots)
    defs.push_back(*slot);

  system_section_node system =
      std::any_cast<system_section_node>(ctx->system()->accept(this));
  return program_node(line_of(ctx), col_of(ctx), std::string("ChipsModel"),
                      preamble_section_node(0, 0, defs), system);
}

std::any chips_ast_builder::visitSystem(ChipsParser::SystemContext *ctx) {
  VERBOSE_VISIT_ENTER
  venv.m_system_reached = true;
  venv.m_current_def_name.clear();
  venv.m_support_name.clear();
  visitor_env::scope_guard system_scope(venv);

  std::vector<system_statement_variant> statements{};
  for (ChipsParser::S_statementContext *stmt : ctx->s_statement())
  {
    append_statements(statements, stmt->accept(this));
  }
  return system_section_node(line_of(ctx), col_of(ctx), statements);
}

std::any chips_ast_builder::visitObjectDefinition(
    ChipsParser::ObjectDefinitionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->object_def()->accept(this);
}

std::any
chips_ast_builder::visitObject_def(ChipsParser::Object_defContext *ctx) {
  VERBOSE_VISIT_ENTER
  venv.m_current_def_name = ctx->IDENTIFIER()->getText();
  visitor_env::scope_guard object_scope(venv);
  with_section with =
      std::any_cast<with_section>(ctx->with_section()->accept(this));

  auto *object = make_node<object_definition>(line_of(ctx), col_of(ctx),
                                              venv.m_current_def_name, with);
  venv.declare_definition(venv.m_current_def_name, object);
  return definition_variant(object);
}

std::any chips_ast_builder::visitFunctionDefinition(
    ChipsParser::FunctionDefinitionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->function_def()->accept(this);
}

std::any chips_ast_builder::visitCollectiveOperationDefinition(
    ChipsParser::CollectiveOperationDefinitionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->collective_op_def()->accept(this);
}

std::any chips_ast_builder::visitLogicalDefintion(
    ChipsParser::LogicalDefintionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->l_function_def()->accept(this);
}

std::any chips_ast_builder::visitPhysicalDefinition(
    ChipsParser::PhysicalDefinitionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->p_function_def()->accept(this);
}

std::any
chips_ast_builder::visitC_keywords(ChipsParser::C_keywordsContext *ctx) {
  VERBOSE_VISIT_ENTER
  if (ctx->SPREAD_KW() != nullptr)
  {
    return collective_function_type::SPREAD;
  }
  return collective_function_type::COLLECT;
}

template <dataflow_type dft>
collective_parameter_variant interpret_collective_param(
    ChipsParser::Cdf_defaulted_declContext *ctx, chips_ast_builder *self,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>
        &dims) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_collective_variable<dft> variable(line, column, name, dims);
  auto *decl =
      self->make_node<dataflow_declaration<dft, statement_env::COLLECTIVE>>(
          line, column, variable);
  decl->m_variable.set_declaration(decl);

  std::optional<dataflow_type> t = self->checker.infer_type(ctx->c_expr());
  if (t.has_value() && *t != dft)
  {
    type_fail(self->venv, ctx->c_expr(),
              "accumulator '" + name + "' is declared " + type_name(dft) +
                  " but its default value is " + type_name(*t));
  }
  auto *default_value = std::get<rvalue<dft, expression_env::COLLECTIVE> *>(
      std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(
          ctx->c_expr()->accept(self)));

  auto *param = self->make_node<collective_parameter<dft>>(line, column, name,
                                                           decl, default_value);
  self->venv.declare_variable<dft>(name);
  self->venv.declare_variable_node(name, &decl->m_variable);
  return collective_parameter_variant(param);
}

std::any chips_ast_builder::visitCdf_defaulted_decl(
    ChipsParser::Cdf_defaulted_declContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type dft =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  switch (dft)
  {
  case dataflow_type::INT:
    return interpret_collective_param<dataflow_type::INT>(ctx, this, dims);
  case dataflow_type::FLOAT:
    return interpret_collective_param<dataflow_type::FLOAT>(ctx, this, dims);
  case dataflow_type::BOOL:
    return interpret_collective_param<dataflow_type::BOOL>(ctx, this, dims);
  }
  throw std::runtime_error("Unknown dataflow type!");
}

std::any chips_ast_builder::visitC_default_output(
    ChipsParser::C_default_outputContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    expressions.push_back(
        std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(
            e->accept(this)));
  }
  return default_output(line_of(ctx), col_of(ctx), expressions);
}

std::any chips_ast_builder::visitC_channeled_output(
    ChipsParser::C_channeled_outputContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  auto *channel = venv.lookup_channel(venv.m_support_name, name);
  if (channel == nullptr)
  {
    semantic_fail(ctx, "channel '" + name + "' is not declared in node '" +
                           venv.m_support_name + "'");
  }

  std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    expressions.push_back(
        std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(
            e->accept(this)));
  }
  return channeled_output(line_of(ctx), col_of(ctx), channel, expressions);
}

std::any chips_ast_builder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) {
  VERBOSE_VISIT_ENTER

  venv.expected_type_for_input = std::nullopt;

  ChipsParser::C_signatureContext *signature = ctx->c_signature();
  std::string name = signature->IDENTIFIER(0)->getText();
  std::string support_name = signature->IDENTIFIER(1)->getText();
  int line = line_of(ctx);
  int column = col_of(ctx);

  node_definition *support = venv.lookup_node(support_name);
  if (support == nullptr)
  {
    semantic_fail(signature, "node '" + support_name + "' is not defined before this point");
  }
  venv.m_current_def_name = name;
  venv.m_support_name = support_name;
  visitor_env::scope_guard function_scope(venv);

  collective_function_type type = std::any_cast<collective_function_type>(signature->c_keywords()->accept(this));

  std::vector<collective_parameter_variant> accumulators{};
  for (ChipsParser::Cdf_defaulted_declContext *decl : signature->cdf_defaulted_decl())
  {
    checker.visit(decl);
    accumulators.push_back(std::any_cast<collective_parameter_variant>(decl->accept(this)));
  }
  accumulator_definition accumulator(line_of(signature), col_of(signature), accumulators);

  collectiveops_section operations(line, column);
  for (ChipsParser::C_statementContext *stmt : ctx->c_statement())
  {
    checker.visit(stmt);
    append_statements(operations.get_statements(), stmt->accept(this));
  }

  checker.visit(ctx);
  std::vector<rvalue_variant<expression_env::COLLECTIVE>> target_expressions{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    target_expressions.push_back(std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(e->accept(this)));
  }
  target_output target(line, column, target_expressions);

  std::vector<channeled_output> channeled{};
  std::unordered_set<std::string> covered{};
  for (ChipsParser::C_channeled_outputContext *out : ctx->c_channeled_output())
  {
    checker.visit(out);
    channeled.push_back(std::any_cast<channeled_output>(out->accept(this)));
    covered.insert(out->IDENTIFIER()->getText());
  }

  std::optional<default_output> default_out;
  if (ctx->c_default_output() != nullptr)
  {
    if (covered.size() == venv.channel_count(support_name))
    {
      semantic_fail(ctx->c_default_output(),
                    "default output is unreachable: every channel of node '" + support_name +
                        "' already has an output");
    }
    checker.visit(ctx->c_default_output());
    default_out = std::any_cast<default_output>(ctx->c_default_output()->accept(this));
  }

  auto *function = make_node<collective_function_definition>(
      line, column, name, type, accumulator, support, operations, target, default_out, channeled);
  venv.declare_collective(name, function);
  venv.m_support_name.clear();
  return definition_variant(function);
}

template <dataflow_type dft, dataflow_kind dfk, expression_env expenv,
          typename Ctx>
std::any
interpret_param(Ctx *ctx, chips_ast_builder *self,
                std::vector<int_rvalue_expression_variant<expenv>> dims) {
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_primitive_variable<dft> variable(line, column, name, dims);
  auto *decl =
      self->make_node<dataflow_declaration<dft, statement_env::DEFINITION>>(
          line, column, variable);
  decl->m_variable.set_declaration(decl);
  self->venv.declare_variable_node(name, &decl->m_variable);

  rvalue<dft, expression_env::PRIMITIVE> *default_value = nullptr;
  if (ctx->expr() != nullptr)
  {
    dataflow_type t = self->checker.infer_type(ctx->expr());
    if (t != dft)
    {
      type_fail(self->venv, ctx->expr(),
                "parameter '" + name + "' is declared " + type_name(dft) +
                    " but its default value is " + type_name(t));
    }
    default_value = std::get<rvalue<dft, expression_env::PRIMITIVE> *>(
        std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(
            ctx->expr()->accept(self)));
  }

  auto *param = self->make_node<function_parameter<dfk, dft>>(
      line, column, name, decl, default_value);
  if constexpr (dfk == dataflow_kind::PHYSICAL)
  {
    self->venv.declare_sensor(self->venv.current_definition(), name, dft);
    return physical_parameter_variant(param);
  }
  else
  {
    return function_parameter_variant(param);
  }
}

std::any chips_ast_builder::visitL_function_def(
    ChipsParser::L_function_defContext *ctx) {
  VERBOSE_VISIT_ENTER
  venv.m_current_def_name = ctx->IDENTIFIER()->getText();
  visitor_env::scope_guard function_scope(venv);
  venv.m_in_logical = true;

  std::vector<function_parameter_variant> parameters{};
  for (ChipsParser::Df_parameter_declContext *param :
       ctx->df_parameter_decl())
  {
    parameters.push_back(
        std::any_cast<function_parameter_variant>(param->accept(this)));
    venv.declare_parameter(
        venv.m_current_def_name, param->IDENTIFIER()->getText(),
        std::any_cast<dataflow_type>(param->df_type()->accept(this)));
  }

  init_section init =
      std::any_cast<init_section>(ctx->init_section()->accept(this));
  then_section then =
      std::any_cast<then_section>(ctx->then_section()->accept(this));

  std::vector<function_output_variant> outputs{};
  for (ChipsParser::Named_outputContext *out : ctx->named_output())
  {
    outputs.push_back(
        std::any_cast<function_output_variant>(out->accept(this)));
  }

  auto *logical = make_node<logical_definition>(
      line_of(ctx), col_of(ctx), ctx->IDENTIFIER()->getText(), parameters, init,
      then, outputs);
  
  venv.declare_definition(venv.m_current_def_name, logical);
  venv.m_in_logical = false;
  return definition_variant(logical);
}

std::any chips_ast_builder::visitDf_parameter_decl(
    ChipsParser::Df_parameter_declContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type dft =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims{};
  if (ctx->suffixes() != nullptr)
  {
    dims = std::any_cast<
        std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
        ctx->suffixes()->accept(this));
  }

  switch (dft)
  {
  case dataflow_type::INT:
    return interpret_param<dataflow_type::INT, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::FLOAT:
    return interpret_param<dataflow_type::FLOAT, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::BOOL:
    return interpret_param<dataflow_type::BOOL, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  }
  throw std::runtime_error("Unknown dataflow type!");
}

std::any chips_ast_builder::visitP_function_def(
    ChipsParser::P_function_defContext *ctx) {
  VERBOSE_VISIT_ENTER
  venv.m_current_def_name = std::string(ctx->IDENTIFIER()->getText());
  visitor_env::scope_guard function_scope(venv);

  std::vector<function_parameter_variant> parameters{};
  std::vector<physical_parameter_variant> sensors{};
  for (ChipsParser::Pdf_parameter_declContext *param :
       ctx->pdf_parameter_decl())
  {
    std::string name = param->IDENTIFIER()->getText();
    ChipsParser::Pdf_parameter_typeContext *ptype = param->pdf_parameter_type();

    if (auto *sensor =
            dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptype))
    {
      sensors.push_back(
          std::any_cast<physical_parameter_variant>(param->accept(this)));
      venv.declare_parameter(
          venv.m_current_def_name, name,
          std::any_cast<dataflow_type>(sensor->df_type()->accept(this)));
    }
    else
    {
      auto *fn =
          dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptype);
      parameters.push_back(
          std::any_cast<function_parameter_variant>(param->accept(this)));
      venv.declare_parameter(
          venv.m_current_def_name, name,
          std::any_cast<dataflow_type>(fn->df_type()->accept(this)));
    }
  }

  with_section with =
      std::any_cast<with_section>(ctx->with_section()->accept(this));
  init_section init =
      std::any_cast<init_section>(ctx->init_section()->accept(this));
  then_section then =
      std::any_cast<then_section>(ctx->then_section()->accept(this));
  std::vector<function_output_variant> outputs{};
  std::vector<physical_output_variant> actuators{};
  for (ChipsParser::P_named_outputContext *out : ctx->p_named_output())
  {
    if (dynamic_cast<ChipsParser::ActuatorOutputContext *>(out) != nullptr)
    {
      actuators.push_back(
          std::any_cast<physical_output_variant>(out->accept(this)));
    }
    else
    {
      outputs.push_back(
          std::any_cast<function_output_variant>(out->accept(this)));
    }
  }

  auto *physical = make_node<physical_definition>(
      line_of(ctx), col_of(ctx), ctx->IDENTIFIER()->getText(), parameters,
      sensors, with, init, then, outputs, actuators);

  venv.declare_definition(venv.m_current_def_name, physical);

  return definition_variant(physical);
}

std::any
chips_ast_builder::visitC_signature(ChipsParser::C_signatureContext *ctx) {
  VERBOSE_VISIT_ENTER
  UNIMPLEMENTED_METHOD;
}

std::any
chips_ast_builder::visitWith_section(ChipsParser::With_sectionContext *ctx) {
  VERBOSE_VISIT_ENTER
  with_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::With_statementContext *stmt : ctx->with_statement())
  {
    append_statements(section.get_statements(), stmt->accept(this));
  }
  return section;
}

std::any chips_ast_builder::visitChannelDeclaration(
    ChipsParser::ChannelDeclarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto *decl = make_node<node_element_declaration<node_element::CHANNEL>>(
      line_of(ctx), col_of(ctx), ctx->IDENTIFIER(0)->getText(),
      ctx->IDENTIFIER(1)->getText());
  venv.declare_channel(ctx->IDENTIFIER(1)->getText(), decl);
  return std::vector<node_statement_variant>{node_statement_variant(decl)};
}

template <dataflow_type dft>
std::vector<node_statement_variant> build_contextual_declaration(
    chips_ast_builder &builder, ChipsParser::ContextualDeclarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>
        &dims) {
  using decl_t = typename DfTypeToContextualDeclType<dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  rvalue<dft, expression_env::PRIMITIVE> *value = nullptr;
  if (ctx->expr() != nullptr)
  {
    dataflow_type t = builder.checker.infer_type(ctx->expr());
    builder.checker.visit(ctx);
    value =
        as_rvalue<dft>(eval<expression_env::PRIMITIVE>(builder, ctx->expr()));
  }

  contextual_variable<dft> variable(line, column, name, dims);
  decl_t *decl = builder.make_node<decl_t>(line, column, variable, name);
  decl->m_variable_type.set_declaration(decl);
  builder.venv.declare_contextual("ctx." + name, dft, &decl->m_variable_type);

  std::vector<node_statement_variant> statements{node_statement_variant(decl)};
  if (value != nullptr)
  {
    auto *var = &decl->m_variable_type;
    auto *lhs = builder.make_node<
        variable_contextual_expression<dft, expression_env::PRIMITIVE>>(
        line, column, var);
    auto *assign =
        builder.make_node<dataflow_assignment<dft, statement_env::NODE>>(
            line, column, lhs, value);
    statements.push_back(node_statement_variant(
        static_cast<node_statement<recurring_statement::ASSIGNMENT> *>(
            assign)));
  }
  return statements;
}

std::any chips_ast_builder::visitContextualDeclaration(
    ChipsParser::ContextualDeclarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type type =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
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
  throw std::runtime_error(
      "unknown dataflow_type in visitContextualDeclaration");
}

node_statement_variant
to_node_statement(const primitive_statement_variant &statement) {
  return std::visit([](auto *node) -> node_statement_variant
                    { return node; },
                    statement);
}

std::any chips_ast_builder::visitWithRegularStatement(
    ChipsParser::WithRegularStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto statements = std::any_cast<std::vector<primitive_statement_variant>>(
      ctx->statement()->accept(this));
  std::vector<node_statement_variant> converted{};
  for (const primitive_statement_variant &statement : statements)
  {
    converted.push_back(to_node_statement(statement));
  }
  return converted;
}

std::any
chips_ast_builder::visitInit_section(ChipsParser::Init_sectionContext *ctx) {
  VERBOSE_VISIT_ENTER
  init_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext *stmt : ctx->statement())
  {
    append_statements(section.get_statements(), stmt->accept(this));
  }
  return section;
}

std::any
chips_ast_builder::visitThen_section(ChipsParser::Then_sectionContext *ctx) {
  VERBOSE_VISIT_ENTER
  then_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext *stmt : ctx->statement())
  {
    append_statements<primitive_statement_variant>(section.get_statements(), stmt->accept(this));
  }
  return section;
}

template <expression_env expenv>
dataflow_type type_of(const rvalue_variant<expenv> &v) {
  switch (v.index())
  {
  case 0:
    return dataflow_type::INT;
  case 1:
    return dataflow_type::FLOAT;
  default:
    return dataflow_type::BOOL;
  }
}

template <template <dataflow_type, expression_env> class Node,
          dataflow_type dft, expression_env expenv>
rvalue_variant<expenv>
build_binary(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
             const rvalue_variant<expenv> &l, const rvalue_variant<expenv> &r) {
  using node_t = Node<dft, expenv>;
  return rvalue_variant<expenv>(b.make_node<node_t>(
      line_of(ctx), col_of(ctx), as_rvalue<dft>(l), as_rvalue<dft>(r)));
}

template <template <dataflow_type, expression_env> class Node,
          expression_env expenv>
rvalue_variant<expenv> build_numeric(chips_ast_builder &b,
                                     antlr4::ParserRuleContext *ctx,
                                     const rvalue_variant<expenv> &l,
                                     const rvalue_variant<expenv> &r) {
  dataflow_type type =
      is_free<expenv>(l) ? type_of<expenv>(r) : type_of<expenv>(l);
  switch (type)
  {
  case dataflow_type::INT:
    return build_binary<Node, dataflow_type::INT>(b, ctx, l, r);
  case dataflow_type::FLOAT:
    return build_binary<Node, dataflow_type::FLOAT>(b, ctx, l, r);
  default:
    break;
  }
  throw std::runtime_error("numeric operands expected");
}

template <template <dataflow_type, expression_env> class Node,
          expression_env expenv>
rvalue_variant<expenv>
build_any(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
          const rvalue_variant<expenv> &l, const rvalue_variant<expenv> &r) {
  switch (type_of<expenv>(l))
  {
  case dataflow_type::INT:
    return build_binary<Node, dataflow_type::INT>(b, ctx, l, r);
  case dataflow_type::FLOAT:
    return build_binary<Node, dataflow_type::FLOAT>(b, ctx, l, r);
  case dataflow_type::BOOL:
    return build_binary<Node, dataflow_type::BOOL>(b, ctx, l, r);
  }
  throw std::runtime_error("unknown dataflow_type");
}

template <template <dataflow_type dft, expression_env expenv> class Node,
          expression_env expenv>
rvalue_variant<expenv>
build_unary_numeric(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                    const rvalue_variant<expenv> &operand) {
  switch (type_of<expenv>(operand))
  {
  case dataflow_type::INT:
    return rvalue_variant<expenv>(b.make_node<Node<dataflow_type::INT, expenv>>(
        line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(operand)));
  case dataflow_type::FLOAT:
    return rvalue_variant<expenv>(
        b.make_node<Node<dataflow_type::FLOAT, expenv>>(
            line_of(ctx), col_of(ctx),
            as_rvalue<dataflow_type::FLOAT>(operand)));
  default:
    break;
  }
  throw std::runtime_error("numeric operand expected");
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv>
build_var(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
          const std::string &name,
          const std::vector<int_rvalue_expression_variant<expenv>> &dims) {
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  auto *var = resolve_variable_node<var_t>(b, ctx, name);
  return rvalue_variant<expenv>(b.make_node<variable_expression<dft, expenv>>(
      line_of(ctx), col_of(ctx), var, dims));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv>
build_ctx_var(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
              const std::string &name,
              const std::vector<int_rvalue_expression_variant<expenv>> &dims) {
  auto *var = resolve_contextual_node<dft>(b, ctx, name);
  return rvalue_variant<expenv>(
      b.make_node<variable_contextual_expression<dft, expenv>>(
          line_of(ctx), col_of(ctx), var, dims));
}

template <dataflow_type dft>
rvalue_variant<expression_env::COLLECTIVE> build_channeled_accu(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    node_element_declaration<node_element::CHANNEL> *channel,
    const std::string &accumulator,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>
        &dims) {
  auto *var = resolve_variable_node<dataflow_collective_variable<dft>>(
      b, ctx, accumulator);
  auto *expr = b.make_node<channeled_accumulator_expression<dft>>(
      line_of(ctx), col_of(ctx), channel, var, dims);
  return rvalue_variant<expression_env::COLLECTIVE>(
      static_cast<rvalue<dft, expression_env::COLLECTIVE> *>(expr));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv>
build_function(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
               const std::string &name,
               const std::vector<rvalue_variant<expenv>> &params) {
  return rvalue_variant<expenv>(b.make_node<chips::function<dft, expenv>>(
      line_of(ctx), col_of(ctx), name, params));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_cast(chips_ast_builder &b,
                                  antlr4::ParserRuleContext *ctx,
                                  const rvalue_variant<expenv> &operand) {
  constexpr dataflow_type other =
      dft == dataflow_type::INT ? dataflow_type::FLOAT : dataflow_type::INT;

  if (type_of<expenv>(operand) == dft)
    return operand;

  return rvalue_variant<expenv>(b.make_node<cast_as<dft, expenv>>(
      line_of(ctx), col_of(ctx), as_rvalue<other>(operand)));
}

std::any chips_ast_builder::visitLT(ChipsParser::LTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<lt>(*this, ctx, eval<e>(*this, ctx->expr0()),
                             eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitGT(ChipsParser::GTContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type dft = checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<gt>(*this, ctx, eval<e>(*this, ctx->expr0()),
                             eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitLEQ(ChipsParser::LEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type dft = checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<leq>(*this, ctx, eval<e>(*this, ctx->expr0()),
                              eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitGEQ(ChipsParser::GEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type dft = checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<geq>(*this, ctx, eval<e>(*this, ctx->expr0()),
                              eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitEQ(ChipsParser::EQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_any<chips::eq>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitNEQ(ChipsParser::NEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_any<chips::neq>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr())); });
}

std::any chips_ast_builder::visitAND(ChipsParser::ANDContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    rvalue_variant<e> l = eval<e>(*this, ctx->expr0());
    rvalue_variant<e> r = eval<e>(*this, ctx->expr());
    return rvalue_variant<e>(make_node<and_operator<e>>(
        line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r))); });
}

std::any chips_ast_builder::visitOR(ChipsParser::ORContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    rvalue_variant<e> l = eval<e>(*this, ctx->expr0());
    rvalue_variant<e> r = eval<e>(*this, ctx->expr());
    return rvalue_variant<e>(make_node<or_operator<e>>(
        line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r))); });
}

std::any chips_ast_builder::visitPLUS(ChipsParser::PLUSContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<chips::plus>(*this, ctx, eval<e>(*this, ctx->expr01()), eval<e>(*this, ctx->expr0())); });
}

std::any chips_ast_builder::visitSUB(ChipsParser::SUBContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<chips::minus>(*this, ctx, eval<e>(*this, ctx->expr01()), eval<e>(*this, ctx->expr0())); });
}

std::any chips_ast_builder::visitNegate(ChipsParser::NegateContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_unary_numeric<chips::uminus_operator>(*this, ctx, eval<e>(*this, ctx->expr1())); });
}

std::any chips_ast_builder::visitMULT(ChipsParser::MULTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<chips::mult>(*this, ctx, eval<e>(*this, ctx->expr2()), eval<e>(*this, ctx->expr1())); });
}

std::any chips_ast_builder::visitDIV(ChipsParser::DIVContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<chips::div>(*this, ctx, eval<e>(*this, ctx->expr2()), eval<e>(*this, ctx->expr1())); });
}

std::any chips_ast_builder::visitMOD(ChipsParser::MODContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    rvalue_variant<e> l = eval<e>(*this, ctx->expr2());
    rvalue_variant<e> r = eval<e>(*this, ctx->expr1());
    return rvalue_variant<e>(make_node<mod<e>>(
        line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(l), as_rvalue<dataflow_type::INT>(r))); });
}

std::any chips_ast_builder::visitNOT(ChipsParser::NOTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    rvalue_variant<e> operand = eval<e>(*this, ctx->expr2());
    return rvalue_variant<e>(make_node<not_operator<e>>(
        line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(operand))); });
}

std::any chips_ast_builder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->expr0()->accept(this);
}

std::any
chips_ast_builder::visitPassExpr01(ChipsParser::PassExpr01Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->expr01()->accept(this);
}

std::any chips_ast_builder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->expr1()->accept(this);
}

std::any chips_ast_builder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->expr2()->accept(this);
}

// std::any chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext
// *ctx)
// {
//   VERBOSE_VISIT_ENTER
//   return
//   rvalue_variant<expression_env::PRIMITIVE>(make_node<direct<dataflow_type::INT,
//   expression_env::PRIMITIVE>>(
//       line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
// }

std::any
chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx) {
  VERBOSE_VISIT_ENTER
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return rvalue_variant<e>(make_node<direct<dataflow_type::INT, e>>(
        line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText()))); });
}

std::any
chips_ast_builder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) {
  VERBOSE_VISIT_ENTER
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return rvalue_variant<e>(make_node<direct<dataflow_type::FLOAT, e>>(
        line_of(ctx), col_of(ctx), std::stod(ctx->FLOAT()->getText()))); });
}

std::any
chips_ast_builder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) {
  VERBOSE_VISIT_ENTER
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    return rvalue_variant<e>(make_node<direct<dataflow_type::BOOL, e>>(
        line_of(ctx), col_of(ctx), ctx->BOOL()->getText()=="true")); });
}

std::any chips_ast_builder::visitVar(ChipsParser::VarContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type type = checker.infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<e>>>(
        ctx->suffixes()->accept(this));
    return by_type(type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_var<dft, e>(*this, ctx, name, dims);
    }); });
}

std::any chips_ast_builder::visitParens(ChipsParser::ParensContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->expr()->accept(this);
}

std::any
chips_ast_builder::visitVarContext(ChipsParser::VarContextContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type t = checker.infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims =
      std::any_cast<std::vector<
          int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
          ctx->suffixes()->accept(this));
  switch (t)
  {
  case dataflow_type::INT:
    return build_ctx_var<dataflow_type::INT, expression_env::PRIMITIVE>(
        *this, ctx, name, dims);
  case dataflow_type::FLOAT:
    return build_ctx_var<dataflow_type::FLOAT, expression_env::PRIMITIVE>(
        *this, ctx, name, dims);
  case dataflow_type::BOOL:
    return build_ctx_var<dataflow_type::BOOL, expression_env::PRIMITIVE>(
        *this, ctx, name, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitVarContext");
}

std::any chips_ast_builder::visitFunction(ChipsParser::FunctionContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type type = checker.infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    std::vector<rvalue_variant<e>> params{};
    for (ChipsParser::ExprContext *expr : ctx->expr())
    {
      params.push_back(eval<e>(*this, expr));
    }
    return by_type(type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_function<dft, e>(*this, ctx, name, params);
    }); });
}

std::any chips_ast_builder::visitCastAs(ChipsParser::CastAsContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return ctx->cast()->accept(this);
}
std::any chips_ast_builder::visitCast(ChipsParser::CastContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type target = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    rvalue_variant<e> operand = eval<e>(*this, ctx->expr());
    switch (target)
    {
    case dataflow_type::INT:
      return build_cast<dataflow_type::INT, e>(*this, ctx, operand);
    case dataflow_type::FLOAT:
      return build_cast<dataflow_type::FLOAT, e>(*this, ctx, operand);
    case dataflow_type::BOOL:
      break;
    }
    throw std::runtime_error("cast to bool is not allowed"); });
}

std::any chips_ast_builder::visitSuffixes(ChipsParser::SuffixesContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.check_suffixes(ctx);
  return by_env(*this, [&](auto env)
                {
    constexpr expression_env e = decltype(env)::value;
    std::vector<int_rvalue_expression_variant<e>> dims{};
    for (ChipsParser::ExprContext *expr : ctx->expr())
    {
      dims.push_back(narrow<int_rvalue_expression_variant<e>>(
          as_rvalue<dataflow_type::INT>(eval<e>(*this, expr))));
    }
    return dims; });
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

std::any chips_ast_builder::visitCStoplessExpression(
    ChipsParser::CStoplessExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr()->accept(this);
}

std::any chips_ast_builder::visitStop(ChipsParser::StopContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto *node = make_node<stop>(line_of(ctx), col_of(ctx));
  return rvalue_variant<expression_env::COLLECTIVE>(
      static_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE> *>(
          node));
}

std::any chips_ast_builder::visitINPUT(ChipsParser::INPUTContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto *node = make_node<input>(line_of(ctx), col_of(ctx));
  return by_type(venv.expected_type_for_input.value_or(dataflow_type::INT), [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return rvalue_variant<expression_env::COLLECTIVE>(
        static_cast<rvalue<dft, expression_env::COLLECTIVE> *>(node)); });
}

std::any chips_ast_builder::visitCLT(ChipsParser::CLTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<lt>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCGT(ChipsParser::CGTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<gt>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCLEQ(ChipsParser::CLEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<leq>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCGEQ(ChipsParser::CGEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<geq>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCNEQ(ChipsParser::CNEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_any<chips::neq>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCEQ(ChipsParser::CEQContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_any<chips::eq>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCAND(ChipsParser::CANDContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0());
  rvalue_variant<expression_env::COLLECTIVE> r =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<and_operator<expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l),
          as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitCOR(ChipsParser::CORContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0());
  rvalue_variant<expression_env::COLLECTIVE> r =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<or_operator<expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l),
          as_rvalue<dataflow_type::BOOL>(r)));
}

std::any
chips_ast_builder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr0()->accept(this);
}

std::any chips_ast_builder::visitCPLUS(ChipsParser::CPLUSContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<chips::plus>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr01()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()));
}

std::any chips_ast_builder::visitCSUB(ChipsParser::CSUBContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<chips::minus>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr01()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()));
}

std::any
chips_ast_builder::visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr01()->accept(this);
}

std::any chips_ast_builder::visitCNegate(ChipsParser::CNegateContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_unary_numeric<chips::uminus_operator>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any
chips_ast_builder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr1()->accept(this);
}

std::any chips_ast_builder::visitCMULT(ChipsParser::CMULTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<chips::mult>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any chips_ast_builder::visitCDIV(ChipsParser::CDIVContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return build_numeric<chips::div>(
      *this, ctx,
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2()),
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any chips_ast_builder::visitCMOD(ChipsParser::CMODContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2());
  rvalue_variant<expression_env::COLLECTIVE> r =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1());
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<mod<expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(l),
          as_rvalue<dataflow_type::INT>(r)));
}

std::any chips_ast_builder::visitCNOT(ChipsParser::CNOTContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> operand =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2());
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<not_operator<expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(operand)));
}

std::any
chips_ast_builder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr2()->accept(this);
}

std::any chips_ast_builder::visitCINT(ChipsParser::CINTContext *ctx) {
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<direct<dataflow_type::INT, expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
}

std::any chips_ast_builder::visitCFLOAT(ChipsParser::CFLOATContext *ctx) {
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), std::stod(ctx->FLOAT()->getText())));
}

std::any chips_ast_builder::visitCBOOL(ChipsParser::CBOOLContext *ctx) {
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(
      make_node<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>>(
          line_of(ctx), col_of(ctx), ctx->BOOL()->getText() == "true"));
}

std::any chips_ast_builder::visitCVariableExpression(
    ChipsParser::CVariableExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims =
      std::any_cast<std::vector<
          int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
          ctx->c_suffixes()->accept(this));
  if (auto type = checker.infer_type(ctx))
  {
    switch (*type)
    {
    case dataflow_type::INT:
      return build_var<dataflow_type::INT, expression_env::COLLECTIVE>(
          *this, ctx, name, dims);
    case dataflow_type::FLOAT:
      return build_var<dataflow_type::FLOAT, expression_env::COLLECTIVE>(
          *this, ctx, name, dims);
    case dataflow_type::BOOL:
      return build_var<dataflow_type::BOOL, expression_env::COLLECTIVE>(
          *this, ctx, name, dims);
    }
  }
  throw std::runtime_error("unknown dataflow_type in VisitCVariableExpression");
}

std::any
chips_ast_builder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr()->accept(this);
}

std::any chips_ast_builder::visitCtxVariableExpression(
    ChipsParser::CtxVariableExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER

  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims =
      std::any_cast<std::vector<
          int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
          ctx->c_suffixes()->accept(this));
  if (auto t = checker.infer_type(ctx))
  {
    switch (*t)
    {
    case dataflow_type::INT:
      return build_ctx_var<dataflow_type::INT>(*this, ctx, name, dims);
    case dataflow_type::FLOAT:
      return build_ctx_var<dataflow_type::FLOAT>(*this, ctx, name, dims);
    case dataflow_type::BOOL:
      return build_ctx_var<dataflow_type::BOOL>(*this, ctx, name, dims);
    }
  }
  throw std::runtime_error("unknown dataflow_type in visitCtxVariableExpression");
}

std::any
chips_ast_builder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_variant<expression_env::COLLECTIVE>> params{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    params.push_back(eval<expression_env::COLLECTIVE>(*this, e));
  }
  if (auto t = checker.infer_type(ctx))
  {
    switch (*t)
    {
    case dataflow_type::INT:
      return build_function<dataflow_type::INT, expression_env::COLLECTIVE>(
          *this, ctx, name, params);
    case dataflow_type::FLOAT:
      return build_function<dataflow_type::FLOAT, expression_env::COLLECTIVE>(
          *this, ctx, name, params);
    case dataflow_type::BOOL:
      return build_function<dataflow_type::BOOL, expression_env::COLLECTIVE>(
          *this, ctx, name, params);
    }
  }
  throw std::runtime_error("unknown dataflow_type in visitFunction");
}

std::any chips_ast_builder::visitCCastAs(ChipsParser::CCastAsContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.infer_type(ctx);
  return ctx->c_cast()->accept(this);
}

std::any chips_ast_builder::visitC_cast(ChipsParser::C_castContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type target =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  rvalue_variant<expression_env::COLLECTIVE> operand =
      eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  switch (target)
  {
  case dataflow_type::INT:
    return build_cast<dataflow_type::INT, expression_env::COLLECTIVE>(
        *this, ctx, operand);
  case dataflow_type::FLOAT:
    return build_cast<dataflow_type::FLOAT, expression_env::COLLECTIVE>(
        *this, ctx, operand);
  default:
    break;
  }
  throw std::runtime_error("cast to bool is not allowed");
}

std::any
chips_ast_builder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.check_suffixes(ctx);
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims{};
  for (ChipsParser::C_stopless_exprContext *e : ctx->c_stopless_expr())
  {
    dims.push_back(
        narrow<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(
            as_rvalue<dataflow_type::INT>(
                eval<expression_env::COLLECTIVE>(*this, e))));
  }
  return dims;
}

std::any chips_ast_builder::visitChanneledAccuExpression(
    ChipsParser::ChanneledAccuExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::optional<dataflow_type> type = checker.infer_type(ctx);
  std::string accumulator = ctx->IDENTIFIER(1)->getText();
  auto *channel = venv.lookup_channel(venv.m_support_name, ctx->IDENTIFIER(0)->getText());
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));

  if (type.has_value())
  {
    switch (*type)
    {
    case dataflow_type::INT:
      return build_channeled_accu<dataflow_type::INT>(*this, ctx, channel,
                                                      accumulator, dims);
    case dataflow_type::FLOAT:
      return build_channeled_accu<dataflow_type::FLOAT>(*this, ctx, channel,
                                                        accumulator, dims);
    case dataflow_type::BOOL:
      return build_channeled_accu<dataflow_type::BOOL>(*this, ctx, channel,
                                                       accumulator, dims);
    }
  }
  throw std::runtime_error(
      "unknown dataflow_type in visitChanneledAccuExpression");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

std::any chips_ast_builder::visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  if (venv.is_block(name))
  {
    return system_iterable_variant(make_block_expression(
        *this, ctx, name, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{}));
  }
  return by_type(resolve_variable(venv, name, ctx), [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_system_iterable_variable<dft>(*this, ctx, name); });
}

std::any chips_ast_builder::visitSSuffixableFunctionCallExpression(
    ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  if (name != "range" && name != "zeros" && name != "ones")
  {
    semantic_fail(ctx, "cannot iterate over the result of '" + name + "'");
  }
  std::vector<rvalue_variant<expression_env::SYSTEM>> params{};
  for (ChipsParser::ExprContext *e : ctx->expr())
  {
    params.push_back(eval<expression_env::SYSTEM>(*this, e));
  }
  if (params.size() != 1 ||
      !std::holds_alternative<
          rvalue<dataflow_type::INT, expression_env::SYSTEM> *>(params[0]))
  {
    semantic_fail(ctx, "'" + name + "' takes exactly one int parameter");
  }
  return system_iterable_variant(iterable_variant<expression_env::SYSTEM>(
      make_node<chips::function<dataflow_type::INT, expression_env::SYSTEM>>(
          line_of(ctx), col_of(ctx), name, params)));
}

std::any chips_ast_builder::visitSSuffixableBlockOutputExpression(
    ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  semantic_fail(ctx, "the output of a functional block cannot be iterated on "
                     "in the system section");
}

std::any chips_ast_builder::visitBlock(ChipsParser::BlockContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
      ctx->suffixes()->accept(this));
  return make_block_expression(*this, ctx, ctx->IDENTIFIER()->getText(), dims);
}

std::any chips_ast_builder::visitLoop_in(ChipsParser::Loop_inContext *ctx) {
  return build_iterable<expression_env::PRIMITIVE>(*this, ctx);
}

std::any chips_ast_builder::visitLoop_statement(
    ChipsParser::Loop_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::DEFINITION;
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type dft = std::any_cast<dataflow_type>(checker.visit(ctx->loop_in()));
  auto iterable = std::any_cast<iterable_variant<expression_env::PRIMITIVE>>(
      ctx->loop_in()->accept(this));
  switch (dft)
  {
  case dataflow_type::INT:
    return build_foreach<env, dataflow_type::INT>(*this, ctx, name, iterable,
                                                  ctx->statement());
  case dataflow_type::FLOAT:
    return build_foreach<env, dataflow_type::FLOAT>(*this, ctx, name, iterable,
                                                    ctx->statement());
  case dataflow_type::BOOL:
    return build_foreach<env, dataflow_type::BOOL>(*this, ctx, name, iterable,
                                                   ctx->statement());
  }
  throw std::runtime_error("unknown dataflow_type in visitLoop_statement");
}

std::any chips_ast_builder::visitC_loop_statement(
    ChipsParser::C_loop_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::COLLECTIVE;
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type dft = std::any_cast<dataflow_type>(checker.visit(ctx->c_loop_in()));
  auto iterable =
      build_iterable<expression_env::COLLECTIVE>(*this, ctx->c_loop_in());
  switch (dft)
  {
  case dataflow_type::INT:
    return build_foreach<env, dataflow_type::INT>(*this, ctx, name, iterable,
                                                  ctx->c_statement());
  case dataflow_type::FLOAT:
    return build_foreach<env, dataflow_type::FLOAT>(*this, ctx, name, iterable,
                                                    ctx->c_statement());
  case dataflow_type::BOOL:
    return build_foreach<env, dataflow_type::BOOL>(*this, ctx, name, iterable,
                                                   ctx->c_statement());
  }
  throw std::runtime_error("unknown dataflow_type in visitC_loop_statement");
}

std::any chips_ast_builder::visitC_loop_in(ChipsParser::C_loop_inContext *ctx) {
  return build_iterable<expression_env::COLLECTIVE>(*this, ctx);
}

std::any chips_ast_builder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.visit(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  auto iterable = std::any_cast<system_iterable_variant>(ctx->s_suffixable_expr()->accept(this));

  if (auto *block = std::get_if<block_expression_variant>(&iterable))
  {
    return std::visit(
        [&](auto *expression)
        {
          return build_block_foreach(*this, ctx, name, expression);
        },
        *block);
  }

  auto dataflow = std::get<iterable_variant<expression_env::SYSTEM>>(iterable);
  return by_type(iterable_type<expression_env::SYSTEM>(dataflow), [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_foreach<statement_env::SYSTEM, dft>(*this, ctx, name, dataflow, ctx->s_statement()); });
}

std::any chips_ast_builder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::DEFINITION;
  return build_if_else<env>(*this, ctx, ctx->if_statement(), ctx->statement());
}

std::any chips_ast_builder::visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::SYSTEM;
  return build_if_else<env>(*this, ctx, ctx->s_if_statement(), ctx->s_statement());
}

std::any chips_ast_builder::visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::COLLECTIVE;
  return build_if_else<env>(*this, ctx, ctx->c_if_statement(), ctx->c_statement());
}

std::any chips_ast_builder::visitIf_statement(ChipsParser::If_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return build_if<statement_env::DEFINITION>(*this, ctx, ctx->expr(), ctx->statement());
}

std::any chips_ast_builder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return build_if<statement_env::SYSTEM>(*this, ctx, ctx->expr(), ctx->s_statement());
}

std::any chips_ast_builder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return build_if<statement_env::COLLECTIVE>(*this, ctx, ctx->c_expr(), ctx->c_statement());
}

template <statement_env stenv, dataflow_type dft, typename Ctx>
std::vector<typename SttEnvToSttVariant<stenv>::type> build_declaration(
    chips_ast_builder &b, Ctx *ctx, antlr4::ParserRuleContext *initializer,
    const std::vector<
        int_rvalue_expression_variant<SttEnvToExpEnv<stenv>::value>> &dims) {
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  using decl_t = dataflow_declaration<dft, stenv>;
  using variable_t = typename SttEnvToVariableKind<dft, stenv>::type;
  using assign_t = dataflow_assignment<dft, stenv>;
  using body_t = typename SttEnvToSttVariant<stenv>::type;

  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  rvalue<dft, expenv> *value = nullptr;
  if (initializer != nullptr)
  {
    value = as_rvalue<dft>(eval<expenv>(b, initializer));
  }

  variable_t variable(line, column, name, dims);
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);
  b.venv.declare_variable<dft>(name);
  b.venv.declare_variable_node(name, &decl->m_variable);

  std::vector<body_t> statements{body_t(
      static_cast<statement<stenv, recurring_statement::DECLARATION> *>(decl))};
  if (value != nullptr)
  {
    auto *var = &decl->m_variable;
    auto *lhs =
        b.make_node<variable_expression<dft, expenv>>(line, column, var);
    auto *assign = b.make_node<assign_t>(line, column, lhs, value);
    statements.push_back(
        body_t(static_cast<statement<stenv, recurring_statement::ASSIGNMENT> *>(
            assign)));
  }
  return statements;
}

std::any chips_ast_builder::visitStatementDeclaration(
    ChipsParser::StatementDeclarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type type =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  if (ctx->expr() != nullptr)
  {
    dataflow_type init = checker.infer_type(ctx->expr());
    checker.visit(ctx);
  }
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  return by_type(type, [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_declaration<statement_env::DEFINITION, dft>(*this, ctx,
                                                             ctx->expr(), dims); });
}

std::any
chips_ast_builder::visitStatementLoop(ChipsParser::StatementLoopContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->loop_statement()->accept(this);
}

std::any chips_ast_builder::visitStatementIfElse(
    ChipsParser::StatementIfElseContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->if_else_statement()->accept(this);
}

std::any
chips_ast_builder::visitStatementIf(ChipsParser::StatementIfContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->if_statement()->accept(this);
}

std::any chips_ast_builder::visitSLoopStatement(
    ChipsParser::SLoopStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->s_loop_statement()->accept(this);
}

std::any chips_ast_builder::visitSIfElseStatement(
    ChipsParser::SIfElseStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->s_if_else_statement()->accept(this);
}

std::any
chips_ast_builder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->s_if_statement()->accept(this);
}

std::any chips_ast_builder::visitCollectiveLoopStatement(
    ChipsParser::CollectiveLoopStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_loop_statement()->accept(this);
}

std::any chips_ast_builder::visitCollectiveIfElseStatement(
    ChipsParser::CollectiveIfElseStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_if_else_statement()->accept(this);
}

std::any chips_ast_builder::visitCollectiveIfStatement(
    ChipsParser::CollectiveIfStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->c_if_statement()->accept(this);
}

std::any chips_ast_builder::visitCdf_full_declaration(
    ChipsParser::Cdf_full_declarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  dataflow_type type =
      std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  if (ctx->c_expr() != nullptr)
  {
    std::optional<dataflow_type> init = checker.infer_type(ctx->c_expr());
    checker.visit(ctx);
  }
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  return by_type(type, [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_declaration<statement_env::COLLECTIVE, dft>(
        *this, ctx, ctx->c_expr(), dims); });
}

std::any chips_ast_builder::visitRegularStatement(
    ChipsParser::RegularStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  ChipsParser::StatementContext *statement = ctx->statement();

  if (auto *decl =
          dynamic_cast<ChipsParser::StatementDeclarationContext *>(statement))
  {
    dataflow_type type =
        std::any_cast<dataflow_type>(decl->df_type()->accept(this));
    if (decl->expr() != nullptr)
    {
      dataflow_type init = checker.infer_type(decl->expr());
      checker.visit(ctx);
    }
    auto dims = std::any_cast<
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
        decl->suffixes()->accept(this));
    return by_type(type, [&](auto t)
                   {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_declaration<statement_env::SYSTEM, dft>(
        *this, decl, decl->expr(), dims
      ); });
  }

  if (auto *assign =
          dynamic_cast<ChipsParser::StatementAssignmentContext *>(statement))
  {
    std::string name = assign->IDENTIFIER()->getText();
    dataflow_type type;
    auto t = venv.lookup_variable(name);
    if (t != std::nullopt)
    {
      type = *t;
    }
    else
    {
      semantic_fail(ctx, std::string("cannot retrieve the variable of ") + name);
    }
    dataflow_type rhs_type = checker.infer_type(assign->expr());
    checker.visit(ctx);
    auto dims = std::any_cast<
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
        assign->suffixes()->accept(this));
    auto rhs = eval<expression_env::SYSTEM>(*this, assign->expr());
    return by_type(type, [&](auto t)
                   {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_system_assignment<dft>(*this, assign, dims, rhs); });
  }

  semantic_fail(statement,
                "this statement is not allowed in the system section");
}

template <dataflow_type dft, expression_env expenv, statement_env sttenv>
std::any build_variable_assignment(
    chips_ast_builder &builder, ChipsParser::StatementAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expenv>> &dims,
    const rvalue_variant<expression_env::PRIMITIVE> &rhs) {
  using assign_t = dataflow_assignment<dft, sttenv>;
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = resolve_variable_node<var_t>(builder, ctx, ctx->IDENTIFIER()->getText());
  auto *lhs = builder.make_node<variable_expression<dft, expenv>>(
      line, column, var, dims);
  auto *assign = builder.make_node<assign_t>(
      line, column, lhs, std::get<rvalue<dft, expenv> *>(rhs));
  std::vector<primitive_statement_variant> result{
      primitive_statement_variant(
          static_cast<primitive_statement<recurring_statement::ASSIGNMENT> *>(assign))};
  return result;
}
std::any chips_ast_builder::visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.visit(ctx);
  dataflow_type type = resolve_variable(venv, ctx->IDENTIFIER()->getText(), ctx);

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  auto rhs = eval<expression_env::PRIMITIVE>(*this, ctx->expr());

  switch (type)
  {
  case dataflow_type::INT:
    return build_variable_assignment<dataflow_type::INT, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  case dataflow_type::FLOAT:
    return build_variable_assignment<dataflow_type::FLOAT, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  case dataflow_type::BOOL:
    return build_variable_assignment<dataflow_type::BOOL, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error("unknown dataflow_type in visitStatementAssignment");
}

template <dataflow_type dft>
std::vector<primitive_statement_variant> build_contextual_assignment(
    chips_ast_builder &builder,
    ChipsParser::StatementContextualAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>
        &dims,
    const rvalue_variant<expression_env::PRIMITIVE> &rhs) {
  using assign_t = dataflow_assignment<dft, statement_env::DEFINITION>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = resolve_contextual_node<dft>(builder, ctx, ctx->IDENTIFIER()->getText());
  auto *lhs = builder.make_node<
      variable_contextual_expression<dft, expression_env::PRIMITIVE>>(
      line, column, var, dims);
  auto *assign = builder.make_node<assign_t>(
      line, column, lhs,
      std::get<rvalue<dft, expression_env::PRIMITIVE> *>(rhs));
  std::vector<primitive_statement_variant> result{
      primitive_statement_variant(
          static_cast<primitive_statement<recurring_statement::ASSIGNMENT> *>(assign))};
  return result;
}

std::any chips_ast_builder::visitStatementContextualAssignment(
    ChipsParser::StatementContextualAssignmentContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type type = resolve_variable(venv, "ctx." + name, ctx);
  checker.visit(ctx);
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  auto rhs = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(
      ctx->expr()->accept(this));

  switch (type)
  {
  case dataflow_type::INT:
    return build_contextual_assignment<dataflow_type::INT>(*this, ctx, dims, rhs);
  case dataflow_type::FLOAT:
    return build_contextual_assignment<dataflow_type::FLOAT>(*this, ctx, dims, rhs);
  case dataflow_type::BOOL:
    return build_contextual_assignment<dataflow_type::BOOL>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error(
      "unknown dataflow_type in visitStatementContextualAssignment");
}

std::any chips_ast_builder::visitObjectDeclaration(
    ChipsParser::ObjectDeclarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string definition = ctx->IDENTIFIER(0)->getText();
  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
      ctx->suffixes()->accept(this));

  if (auto *logical = venv.lookup_logical(definition))
    return build_block_declaration<block_type::LOGICAL>(*this, ctx, logical,
                                                        dims);
  if (auto *physical = venv.lookup_physical(definition))
    return build_block_declaration<block_type::PHYSICAL>(*this, ctx, physical,
                                                         dims);
  if (auto *object = venv.lookup_object(definition))
    return build_block_declaration<block_type::OBJECT>(*this, ctx, object,
                                                       dims);
  semantic_fail(ctx, "definition '" + definition + "' is not defined");
}

std::any chips_ast_builder::visitFeedingStatement(
    ChipsParser::FeedingStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.visit(ctx);
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string target = ctx->IDENTIFIER()->getText();
  auto block = std::any_cast<block_expression_variant>(ctx->block()->accept(this));
  std::string definition = venv.lookup_block(ctx->block()->IDENTIFIER()->getText(), ctx->block()).second;
  auto source = std::any_cast<s_expr_variant>(ctx->s_expr()->accept(this));

  if (auto *channel = venv.lookup_channel(definition, target))
  {
    auto *fed = std::get_if<channel_feeder *>(&source);
    if (fed == nullptr)
    {
      semantic_fail(ctx->s_expr(), "channel '" + target + "' must be plugged to a channel");
    }
    if (channel->get_variable() != (*fed)->get_feeding_channel()->get_variable())
    {
      semantic_fail(ctx->s_expr(),
                    "incompatible channel types: '" + channel->get_variable() +
                        "' and '" + (*fed)->get_feeding_channel()->get_variable() + "'");
    }
    auto *eating =
        make_node<channel_eater>(line, column, node_of(block), channel);
    auto *plugging = make_node<channel_plugging>(line, column, eating, *fed);
    return std::vector<system_statement_variant>{
        system_statement_variant(static_cast<system_statement<recurring_statement::PLUGGING> *>(plugging))};
  }

  std::optional<dataflow_type> type = venv.lookup_parameter(definition, target);
  if (!type.has_value())
  {
    semantic_fail(ctx, "'" + target +
                           "' is neither a parameter nor a channel of '" +
                           definition + "'");
  }
  auto *dataflow = std::get_if<feeder_variant>(&source);
  if (dataflow == nullptr)
  {
    semantic_fail(ctx->s_expr(),
                  "parameter '" + target + "' must be fed by a dataflow");
  }
  functional_block_variant eating = functional_of(ctx, block);

  if (venv.lookup_sensor(definition, target).has_value())
  {
    auto *physical = venv.lookup_physical(definition);
    return by_type(*type, [&](auto t)
                   {
      constexpr dataflow_type dft = decltype(t)::value;
      return feed_parameter<dataflow_kind::PHYSICAL, dft>(
          *this, ctx, eating, physical->m_sensors, *dataflow); });
  }
  auto *function = venv.lookup_function(definition);
  return by_type(*type, [&](auto t)
                 {
    constexpr dataflow_type dft = decltype(t)::value;
    return feed_parameter<dataflow_kind::LOGICAL, dft>(
        *this, ctx, eating, function->get_parameters(), *dataflow); });
}

std::any chips_ast_builder::visitLinkingStatement(
    ChipsParser::LinkingStatementContext *ctx) {
  VERBOSE_VISIT_ENTER
  using system_dims_t =
      std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>;
  auto linked = make_block_expression(
      *this, ctx, ctx->IDENTIFIER(0)->getText(),
      std::any_cast<system_dims_t>(ctx->suffixes(0)->accept(this)));
  auto supporting = make_block_expression(
      *this, ctx, ctx->IDENTIFIER(1)->getText(),
      std::any_cast<system_dims_t>(ctx->suffixes(1)->accept(this)));

  linkable *linked_component =
      std::visit([](auto *e) -> linkable *
                 { return e; }, linked);
  support *support_node = nullptr;
  if (auto *p =
          std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(
              &supporting))
    support_node = *p;
  else if (auto *o = std::get_if<
               system_variable_block_expression<block_type::OBJECT> *>(
               &supporting))
    support_node = *o;
  else
    semantic_fail(ctx, "a logical block cannot support another component");

  auto *node = make_node<linking_statement>(line_of(ctx), col_of(ctx),
                                            linked_component, support_node);
  return std::vector<system_statement_variant>{system_statement_variant(static_cast<system_statement<recurring_statement::LINKING> *>(node))};
}

std::any chips_ast_builder::visitSBlockOutputExpression(
    ChipsParser::SBlockOutputExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  return resolve_block_output(*this, ctx, ctx->block(),
                              ctx->IDENTIFIER()->getText());
}

std::any chips_ast_builder::visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.visit(ctx);
  auto *collective = std::any_cast<collective_function_definition *>(ctx->collective_operation()->accept(this));
  s_expr_variant inner = resolve_block_output(*this, ctx, ctx->block(), ctx->IDENTIFIER()->getText());
  auto *dataflow = std::get_if<feeder_variant>(&inner);
  if (dataflow == nullptr)
  {
    semantic_fail(ctx, "a collective operation cannot be applied to a channel");
  }
  return s_expr_variant(by_type(collective_result_type(collective), [&](auto t)
                                {
    constexpr dataflow_type result = decltype(t)::value;
    return std::visit([&](auto *source) { return build_collective_cast<result>(*this, ctx, collective, source); }, *dataflow); }));
}

std::any chips_ast_builder::visitSRegularExpression(
    ChipsParser::SRegularExpressionContext *ctx) {
  VERBOSE_VISIT_ENTER
  auto value = eval<expression_env::SYSTEM>(*this, ctx->expr());
  return s_expr_variant(
      std::visit([](auto *v)
                 { return as_feeder(v); }, value));
}

std::any chips_ast_builder::visitCollective_operation(
    ChipsParser::Collective_operationContext *ctx) {
  VERBOSE_VISIT_ENTER
  return venv.lookup_collective(ctx->IDENTIFIER()->getText(), ctx);
}

std::any chips_ast_builder::visitCollectiveVariableDeclaration(
    ChipsParser::CollectiveVariableDeclarationContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->cdf_full_declaration()->accept(this);
}

template <dataflow_type dft>
std::vector<collective_statement_variant> build_collective_assignment(
    chips_ast_builder &b, ChipsParser::CollectiveAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims,
    const rvalue_variant<expression_env::COLLECTIVE> &rhs) {
  using assign_t = dataflow_assignment<dft, statement_env::COLLECTIVE>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = resolve_variable_node<dataflow_collective_variable<dft>>(
      b, ctx, ctx->IDENTIFIER()->getText());
  auto *lhs = b.make_node<variable_expression<dft, expression_env::COLLECTIVE>>(line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, as_rvalue<dft>(rhs));
  return {collective_statement_variant(static_cast<collective_statement<recurring_statement::ASSIGNMENT> *>(assign))};
}

std::any chips_ast_builder::visitCollectiveAssignment(
    ChipsParser::CollectiveAssignmentContext *ctx) {
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type type;
  auto t = venv.lookup_variable(name);
  if (t != std::nullopt) {
    type = *t;
  } else {
    semantic_fail(ctx, std::string("cannot retrieve the variable ") + name);
  }
  std::optional<dataflow_type> rhs_type = checker.infer_type(ctx->c_expr());
  if (rhs_type.has_value() && *rhs_type != type) {
    type_fail(venv, ctx->c_expr(), "cannot assign " + type_name(*rhs_type) + " to '" + name + "' of type " + type_name(type));
  }

  auto dims = std::any_cast<
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  auto rhs = eval<expression_env::COLLECTIVE>(*this, ctx->c_expr());

  switch (type) {
  case dataflow_type::INT:
    return build_collective_assignment<dataflow_type::INT>(*this, ctx, dims,
                                                           rhs);
  case dataflow_type::FLOAT:
    return build_collective_assignment<dataflow_type::FLOAT>(*this, ctx, dims,
                                                             rhs);
  case dataflow_type::BOOL:
    return build_collective_assignment<dataflow_type::BOOL>(*this, ctx, dims,
                                                            rhs);
  }
  throw std::runtime_error(
      "unknown dataflow_type in visitCollectiveAssignment");
}
template <dataflow_type dft>
std::vector<collective_statement_variant> build_collective_contextual_assignment(
    chips_ast_builder &b, ChipsParser::ContextualAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims,
    const rvalue_variant<expression_env::COLLECTIVE> &rhs) {
  using assign_t = dataflow_assignment<dft, statement_env::COLLECTIVE>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = resolve_contextual_node<dft>(b, ctx, ctx->IDENTIFIER()->getText());
  auto *lhs = b.make_node<variable_contextual_expression<dft, expression_env::COLLECTIVE>>(line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, as_rvalue<dft>(rhs));
  return {collective_statement_variant(static_cast<collective_statement<recurring_statement::ASSIGNMENT> *>(assign))};
}

std::any chips_ast_builder::visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) {
  VERBOSE_VISIT_ENTER
  checker.visit(ctx);
  dataflow_type type = resolve_variable(venv, "ctx." + ctx->IDENTIFIER()->getText(), ctx);

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  auto rhs = eval<expression_env::COLLECTIVE>(*this, ctx->c_expr());

  return by_type(type, [&](auto t) {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_collective_contextual_assignment<dft>(*this, ctx, dims, rhs); });
}

template <dataflow_type dft, dataflow_kind dfk, typename Ctx>
std::any interpret_output(Ctx *ctx, chips_ast_builder *self) {
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_variant<expression_env::PRIMITIVE>> expressions{};
  for (ChipsParser::ExprContext *e : ctx->expr()) {
    dataflow_type t = self->checker.infer_type(e);
    if (t != dft) {
      type_fail(self->venv, e, "output '" + name + "' mixes " + type_name(dft) + " and " + type_name(t) + " expressions");
    }
    expressions.push_back(
        std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(
            e->accept(self)));
  }

  auto *output = self->make_node<function_output<dfk, dft>>(
      line_of(ctx), col_of(ctx), name, expressions);
  if constexpr (dfk == dataflow_kind::PHYSICAL) {
    self->venv.declare_actuator(self->venv.current_definition(), name, dft);
    return physical_output_variant(output);
  } else {
    self->venv.declare_output(self->venv.current_definition(), name, dft);
    return function_output_variant(output);
  }
}

template <dataflow_kind dfk, typename Ctx>
std::any dispatch_output(Ctx *ctx, chips_ast_builder *self) {
  switch (self->checker.infer_type(ctx->expr(0))) {
  case dataflow_type::INT:
    return interpret_output<dataflow_type::INT, dfk>(ctx, self);
  case dataflow_type::FLOAT:
    return interpret_output<dataflow_type::FLOAT, dfk>(ctx, self);
  case dataflow_type::BOOL:
    return interpret_output<dataflow_type::BOOL, dfk>(ctx, self);
  }
  throw std::runtime_error("unknown dataflow_type in dispatch_output");
}

std::any
chips_ast_builder::visitNamed_output(ChipsParser::Named_outputContext *ctx) {
  VERBOSE_VISIT_ENTER
  return dispatch_output<dataflow_kind::LOGICAL>(ctx, this);
}

std::any chips_ast_builder::visitActuatorOutput(
    ChipsParser::ActuatorOutputContext *ctx) {
  VERBOSE_VISIT_ENTER
  return dispatch_output<dataflow_kind::PHYSICAL>(ctx, this);
}

std::any chips_ast_builder::visitFunctionOutput(
    ChipsParser::FunctionOutputContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->named_output()->accept(this);
}

std::any chips_ast_builder::visitIntType(ChipsParser::IntTypeContext *ctx) {
  VERBOSE_VISIT_ENTER
  return dataflow_type::INT;
}

std::any chips_ast_builder::visitFloatType(ChipsParser::FloatTypeContext *ctx) {
  VERBOSE_VISIT_ENTER
  return dataflow_type::FLOAT;
}

std::any chips_ast_builder::visitBoolType(ChipsParser::BoolTypeContext *ctx) {
  VERBOSE_VISIT_ENTER
  return dataflow_type::BOOL;
}

std::any chips_ast_builder::visitFunctionParameterType(
    ChipsParser::FunctionParameterTypeContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->df_type()->accept(this);
}

std::any chips_ast_builder::visitSensorParameterType(
    ChipsParser::SensorParameterTypeContext *ctx) {
  VERBOSE_VISIT_ENTER
  return ctx->df_type()->accept(this);
}

std::any chips_ast_builder::visitPdf_parameter_decl(
    ChipsParser::Pdf_parameter_declContext *ctx) {
  VERBOSE_VISIT_ENTER
  ChipsParser::Pdf_parameter_typeContext *ptcontext = ctx->pdf_parameter_type();
  dataflow_type dft;
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims{};

  if (ChipsParser::SensorParameterTypeContext *sensorp =
          dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptcontext);
      sensorp != nullptr) {
    dft = std::any_cast<dataflow_type>(sensorp->df_type()->accept(this));
    if (sensorp->suffixes() != nullptr) {
      dims = std::any_cast<std::vector<
          int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
          sensorp->suffixes()->accept(this));
    }

    switch (dft) {
    case dataflow_type::INT:
      return interpret_param<dataflow_type::INT, dataflow_kind::PHYSICAL,
                             expression_env::PRIMITIVE>(ctx, this, dims);
    case dataflow_type::FLOAT:
      return interpret_param<dataflow_type::FLOAT, dataflow_kind::PHYSICAL,
                             expression_env::PRIMITIVE>(ctx, this, dims);
    case dataflow_type::BOOL:
      return interpret_param<dataflow_type::BOOL, dataflow_kind::PHYSICAL,
                             expression_env::PRIMITIVE>(ctx, this, dims);
    }
    throw std::runtime_error("Unknown dataflow type!");
  }

  ChipsParser::FunctionParameterTypeContext *fparamp =
      dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptcontext);
  dft = std::any_cast<dataflow_type>(fparamp->df_type()->accept(this));
  if (fparamp->suffixes() != nullptr) {
    dims = std::any_cast<
        std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
        fparamp->suffixes()->accept(this));
  }

  switch (dft) {
  case dataflow_type::INT:
    return interpret_param<dataflow_type::INT, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::FLOAT:
    return interpret_param<dataflow_type::FLOAT, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::BOOL:
    return interpret_param<dataflow_type::BOOL, dataflow_kind::LOGICAL,
                           expression_env::PRIMITIVE>(ctx, this, dims);
  }
  throw std::runtime_error("Unknown dataflow type!");
}

#undef UNIMPLEMENTED_METHOD