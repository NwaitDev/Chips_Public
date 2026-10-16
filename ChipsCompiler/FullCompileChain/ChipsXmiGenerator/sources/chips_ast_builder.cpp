#include "chips_ast_builder.hpp"
#include "../generated/ChipsParser.h"
#include <unordered_set>

#define UNIMPLEMENTED_METHOD \
  throw std::runtime_error(std::string("unimplemented ") + __func__ + " error.")

#define VERBOSE true

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

// Context helper methods

int line_of(antlr4::ParserRuleContext *c) { return c->getStart()->getLine(); }
int col_of(antlr4::ParserRuleContext *c) { return c->getStart()->getCharPositionInLine(); }

[[noreturn]] void semantic_fail(antlr4::ParserRuleContext *ctx, const std::string &msg)
{
  throw std::runtime_error("error at line " + std::to_string(ctx->getStart()->getLine()) + ", column " +
                           std::to_string(ctx->getStart()->getCharPositionInLine() + 1) + ": " + msg);
}


void chips_ast_builder::declare_channel(const std::string &channel, node_element_declaration<node_element::CHANNEL> *decl)
{
  auto &channels = m_channels[m_current_def_name];
  if (channels.find(channel) != channels.end())
  {
    throw std::runtime_error("duplicate channel '" + channel + "' in node '" + m_current_def_name + "'");
  }
  channels[channel] = decl;
}

node_element_declaration<node_element::CHANNEL> *chips_ast_builder::lookup_channel(const std::string &node, const std::string &channel) const
{
  auto n = m_channels.find(node);
  if (n == m_channels.end())
    return nullptr;
  auto it = n->second.find(channel);
  return it == n->second.end() ? nullptr : it->second;
}

std::size_t chips_ast_builder::channel_count(const std::string &node) const
{
  auto n = m_channels.find(node);
  return n == m_channels.end() ? 0 : n->second.size();
}

void chips_ast_builder::declare_contextual(const std::string &var, dataflow_type type)
{
  m_contextuals[m_current_def_name][var] = type;
}

std::optional<dataflow_type> chips_ast_builder::lookup_contextual(const std::string &var) const
{
  const std::string &owner = m_support_name.empty() ? m_current_def_name : m_support_name;
  auto node = m_contextuals.find(owner);
  if (node == m_contextuals.end())
    return std::nullopt;
  auto it = node->second.find(var);
  if (it == node->second.end())
    return std::nullopt;
  return it->second;
}

void chips_ast_builder::declare_parameter(const std::string &function, const std::string &var, dataflow_type type)
{
  auto &params = m_parameters[function];
  if (params.find(var) != params.end())
  {
    throw std::runtime_error("duplicate parameter '" + var + "' in function '" + function + "'");
  }
  params[var] = type;
}

std::optional<dataflow_type> chips_ast_builder::lookup_parameter(const std::string &function, const std::string &var) const
{
  auto fn = m_parameters.find(function);
  if (fn == m_parameters.end())
    return std::nullopt;
  auto it = fn->second.find(var);
  if (it == fn->second.end())
    return std::nullopt;
  return it->second;
}

template <typename F>
auto by_type(dataflow_type type, F &&f) -> decltype(f(std::integral_constant<dataflow_type, dataflow_type::INT>{}))
{
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
std::any by_env(const chips_ast_builder &b, F &&f)
{
  if (b.system_reached())
  {
    return f(std::integral_constant<expression_env, expression_env::SYSTEM>{});
  }
  return f(std::integral_constant<expression_env, expression_env::PRIMITIVE>{});
}

void chips_ast_builder::push_scope()
{
  m_scopes.emplace_back();
  m_block_scopes.emplace_back();
}

void chips_ast_builder::pop_scope()
{
  m_scopes.pop_back();
  m_block_scopes.pop_back();
}

bool chips_ast_builder::definition_exists(const std::string &name) const
{
  return m_logicals.count(name) > 0 || m_physicals.count(name) > 0 || m_objects.count(name) > 0;
}

void chips_ast_builder::declare_definition(const std::string &name, logical_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_logicals[name] = definition;
}

void chips_ast_builder::declare_definition(const std::string &name, physical_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_physicals[name] = definition;
}

void chips_ast_builder::declare_definition(const std::string &name, object_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_objects[name] = definition;
}

logical_definition *chips_ast_builder::lookup_logical(const std::string &name) const
{
  auto it = m_logicals.find(name);
  return it == m_logicals.end() ? nullptr : it->second;
}

physical_definition *chips_ast_builder::lookup_physical(const std::string &name) const
{
  auto it = m_physicals.find(name);
  return it == m_physicals.end() ? nullptr : it->second;
}

object_definition *chips_ast_builder::lookup_object(const std::string &name) const
{
  auto it = m_objects.find(name);
  return it == m_objects.end() ? nullptr : it->second;
}

node_definition *chips_ast_builder::lookup_node(const std::string &name) const
{
  if (auto *object = lookup_object(name))
  {
    return object;
  }
  return lookup_physical(name);
}

function_definition *chips_ast_builder::lookup_function(const std::string &name) const
{
  if (auto *logical = lookup_logical(name))
  {
    return logical;
  }
  return lookup_physical(name);
}

void chips_ast_builder::declare_block(const std::string &name, block_type type, const std::string &definition)
{
  auto &scope = m_block_scopes.back();
  if (scope.find(name) != scope.end())
  {
    throw std::runtime_error("duplicate block '" + name + "'");
  }
  scope[name] = {type, definition};
}

std::pair<block_type, std::string> chips_ast_builder::lookup_block(const std::string &name, antlr4::ParserRuleContext *ctx) const
{
  for (auto scope = m_block_scopes.rbegin(); scope != m_block_scopes.rend(); ++scope)
  {
    auto it = scope->find(name);
    if (it != scope->end())
    {
      return it->second;
    }
  }
  semantic_fail(ctx, "block '" + name + "' is not declared");
}

bool chips_ast_builder::is_block(const std::string &name) const
{
  for (auto scope = m_block_scopes.rbegin(); scope != m_block_scopes.rend(); ++scope)
  {
    if (scope->find(name) != scope->end())
    {
      return true;
    }
  }
  return false;
}

std::optional<dataflow_type> chips_ast_builder::lookup_sensor(const std::string &function, const std::string &sensor) const
{
  auto fn = m_sensors.find(function);
  if (fn == m_sensors.end())
    return std::nullopt;
  auto it = fn->second.find(sensor);
  return it == fn->second.end() ? std::nullopt : std::optional<dataflow_type>(it->second);
}

std::optional<dataflow_type> chips_ast_builder::lookup_actuator(const std::string &function, const std::string &actuator) const
{
  auto fn = m_actuators.find(function);
  if (fn == m_actuators.end())
    return std::nullopt;
  auto it = fn->second.find(actuator);
  return it == fn->second.end() ? std::nullopt : std::optional<dataflow_type>(it->second);
}

template <dataflow_type type>
void chips_ast_builder::declare_variable(const std::string &name)
{
  if (m_scopes.empty())
  {
    throw std::runtime_error("variable '" + name + "' declared outside of any scope");
  }
  if (m_scopes.back().find(name) != m_scopes.back().end())
  {
    throw std::runtime_error("duplicate variable '" + name + "' in '" + m_current_def_name + "'");
  }
  m_scopes.back()[name] = type;
}

std::optional<dataflow_type> chips_ast_builder::lookup_variable(const std::string &name) const
{
  for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
  {
    auto found = it->find(name);
    if (found != it->end())
      return found->second;
  }
  return std::nullopt;
}

void chips_ast_builder::declare_output(const std::string &function, const std::string &name, dataflow_type type)
{
  auto &outs = m_outputs[function];
  if (outs.find(name) != outs.end())
  {
    throw std::runtime_error("duplicate output '" + name + "' in function '" + function + "'");
  }
  outs[name] = type;
}

std::optional<dataflow_type> chips_ast_builder::lookup_output(const std::string &function, const std::string &name) const
{
  auto fn = m_outputs.find(function);
  if (fn == m_outputs.end())
    return std::nullopt;
  auto it = fn->second.find(name);
  if (it == fn->second.end())
    return std::nullopt;
  return it->second;
}

void chips_ast_builder::declare_sensor(const std::string &function, const std::string &sensor, dataflow_type type)
{
  auto &sensors = m_sensors[function];
  if (sensors.find(sensor) != sensors.end())
  {
    throw std::runtime_error("duplicate sensor '" + sensor + "' in physical '" + function + "'");
  }
  sensors[sensor] = type;
}

void chips_ast_builder::declare_actuator(const std::string &function, const std::string &actuator, dataflow_type type)
{
  auto &actuators = m_actuators[function];
  if (actuators.find(actuator) != actuators.end())
  {
    throw std::runtime_error("duplicate actuator '" + actuator + "' in physical '" + function + "'");
  }
  actuators[actuator] = type;
}

dataflow_type chips_ast_builder::iterator_type(ChipsParser::Loop_inContext *ctx) const
{
  std::string name = ctx->IDENTIFIER()->getText();
  if (ctx->L_PARENTH() != nullptr)
  {
    if (name == "range" || name == "zeros" || name == "ones")
      return dataflow_type::INT;
    type_fail(ctx, "cannot iterate over the result of '" + name + "'");
  }
  return lookup_variable(name, ctx);
}

dataflow_type chips_ast_builder::iterator_type(ChipsParser::C_loop_inContext *ctx) const
{
  std::string name = ctx->IDENTIFIER()->getText();
  if (ctx->L_PARENTH() != nullptr)
  {
    if (name == "range" || name == "zeros" || name == "ones")
      return dataflow_type::INT;
    type_fail(ctx, "cannot iterate over the result of '" + name + "'");
  }
  return lookup_variable(name, ctx);
}

// Type inference methods

bool is_numeric(dataflow_type t)
{
  return t == dataflow_type::INT || t == dataflow_type::FLOAT;
}

std::string type_name(dataflow_type t)
{
  switch (t)
  {
  case dataflow_type::INT:
    return "int";
  case dataflow_type::FLOAT:
    return "float";
  case dataflow_type::BOOL:
    return "bool";
  }
  return "?";
}

void chips_ast_builder::type_fail(antlr4::ParserRuleContext *ctx, const std::string &msg) const
{
  throw std::runtime_error(
      "type inference failed at line " + std::to_string(line_of(ctx)) +
      " in '" + m_current_def_name + "': " + msg +
      " (expression: " + ctx->getText() + ")");
}

dataflow_type chips_ast_builder::lookup_variable(const std::string &name, antlr4::ParserRuleContext *ctx) const
{
  if (name.rfind("ctx.", 0) == 0)
  {
    if (auto t = lookup_contextual(name))
      return *t;
  }
  else
  {
    if (auto t = lookup_variable(name))
      return *t;
    if (auto p = lookup_parameter(m_current_def_name, name))
      return *p;
  }
  type_fail(ctx, "undeclared variable '" + name + "'");
}

std::optional<dataflow_type> unify_types(const chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                         const std::optional<dataflow_type> &l, const std::optional<dataflow_type> &r)
{
  if (l.has_value() && r.has_value() && *l != *r)
  {
    b.type_fail(ctx, "operands must have the same type, got " + type_name(*l) + " and " + type_name(*r));
  }
  return l.has_value() ? l : r;
}


std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_exprContext *e) const
{
  if (auto c = dynamic_cast<ChipsParser::CStoplessExpressionContext *>(e))
    return infer_type(c->c_stopless_expr());
  return std::nullopt;
}

std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_stopless_exprContext *e) const
{
  auto relational = [&](auto *c)
  {
    auto u = unify_types(*this, c, infer_type(c->c_stopless_expr0()), infer_type(c->c_stopless_expr()));
    if (u.has_value() && !is_numeric(*u))
      type_fail(c, "comparison needs numeric operands, got " + type_name(*u));
    return std::optional<dataflow_type>(dataflow_type::BOOL);
  };
  auto equality = [&](auto *c)
  {
    unify_types(*this, c, infer_type(c->c_stopless_expr0()), infer_type(c->c_stopless_expr()));
    return std::optional<dataflow_type>(dataflow_type::BOOL);
  };
  auto logical = [&](auto *c)
  {
      auto l = constrain_type(
          *this, c->c_stopless_expr0(),
          infer_type(c->c_stopless_expr0()),
          dataflow_type::BOOL);

      auto r = constrain_type(
          *this, c->c_stopless_expr(),
          infer_type(c->c_stopless_expr()),
          dataflow_type::BOOL);

      return std::optional<dataflow_type>(dataflow_type::BOOL);
  };

  if (auto c = dynamic_cast<ChipsParser::CLTContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::CGTContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::CLEQContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::CGEQContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::CEQContext *>(e))
    return equality(c);
  if (auto c = dynamic_cast<ChipsParser::CNEQContext *>(e))
    return equality(c);
  if (auto c = dynamic_cast<ChipsParser::CANDContext *>(e))
    return logical(c);
  if (auto c = dynamic_cast<ChipsParser::CORContext *>(e))
    return logical(c);
  if (auto c = dynamic_cast<ChipsParser::PassCExpr0Context *>(e))
    return infer_type(c->c_stopless_expr0());
  type_fail(e, "unsupported expression");
}

std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_stopless_expr0Context *e) const
{
  auto additive = [&](auto *c)
  {
    auto u = unify_types(*this, c, infer_type(c->c_stopless_expr01()), infer_type(c->c_stopless_expr0()));
    if (u.has_value() && !is_numeric(*u))
      type_fail(c, "arithmetic needs numeric operands, got " + type_name(*u));
    return u;
  };

  if (auto c = dynamic_cast<ChipsParser::CPLUSContext *>(e))
    return additive(c);
  if (auto c = dynamic_cast<ChipsParser::CSUBContext *>(e))
    return additive(c);
  if (auto c = dynamic_cast<ChipsParser::PassCExpr01Context *>(e))
    return infer_type(c->c_stopless_expr01());
  type_fail(e, "unsupported expression");
}

std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_stopless_expr01Context *e) const
{
  if (auto c = dynamic_cast<ChipsParser::CNegateContext *>(e))
  {
    auto t = infer_type(c->c_stopless_expr1());
    if (t.has_value() && !is_numeric(*t))
      type_fail(c, "unary minus needs a numeric operand, got " + type_name(*t));
    return t;
  }
  if (auto c = dynamic_cast<ChipsParser::PassCExpr1Context *>(e))
    return infer_type(c->c_stopless_expr1());
  type_fail(e, "unsupported expression");
}

std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_stopless_expr1Context *e) const
{
  auto multiplicative = [&](auto *c)
  {
    auto u = unify_types(*this, c, infer_type(c->c_stopless_expr2()), infer_type(c->c_stopless_expr1()));
    if (u.has_value() && !is_numeric(*u))
      type_fail(c, "arithmetic needs numeric operands, got " + type_name(*u));
    return u;
  };

  if (auto c = dynamic_cast<ChipsParser::CMULTContext *>(e))
    return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::CDIVContext *>(e))
    return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::CMODContext *>(e))
  {
    auto u = unify_types(*this, c, infer_type(c->c_stopless_expr2()), infer_type(c->c_stopless_expr1()));
    if (u.has_value() && *u != dataflow_type::INT)
      type_fail(c, "modulo needs int operands, got " + type_name(*u));
    return dataflow_type::INT;
  }
  if (auto c = dynamic_cast<ChipsParser::CNOTContext *>(e))
  {
    auto t = infer_type(c->c_stopless_expr2());
    if (t.has_value() && *t != dataflow_type::BOOL)
      type_fail(c, "'!' needs a bool operand, got " + type_name(*t));
    return dataflow_type::BOOL;
  }
  if (auto c = dynamic_cast<ChipsParser::PassCExpr2Context *>(e))
    return infer_type(c->c_stopless_expr2());
  type_fail(e, "unsupported expression");
}

std::optional<dataflow_type> chips_ast_builder::infer_type(ChipsParser::C_stopless_expr2Context *e) const
{
  if (dynamic_cast<ChipsParser::CINTContext *>(e))
    return dataflow_type::INT;
  if (dynamic_cast<ChipsParser::CFLOATContext *>(e))
    return dataflow_type::FLOAT;
  if (dynamic_cast<ChipsParser::CBOOLContext *>(e))
    return dataflow_type::BOOL;
  if (dynamic_cast<ChipsParser::INPUTContext *>(e))
    return m_collective_input_type;

  if (auto c = dynamic_cast<ChipsParser::CVariableExpressionContext *>(e))
  {
    check_suffixes(c->c_suffixes());
    return lookup_variable(c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::CtxVariableExpressionContext *>(e))
  {
    check_suffixes(c->c_suffixes());
    return lookup_variable("ctx." + c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::ChanneledAccuExpressionContext *>(e))
  {
    check_suffixes(c->c_suffixes());
    std::string channel = c->IDENTIFIER(0)->getText();
    if (lookup_channel(m_support_name, channel) == nullptr)
      type_fail(c, "channel '" + channel + "' is not declared in node '" + m_support_name + "'");
    return lookup_variable(c->IDENTIFIER(1)->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::CParenthesisContext *>(e))
    return infer_type(c->c_stopless_expr());

  if (auto c = dynamic_cast<ChipsParser::CCastAsContext *>(e))
  {
    ChipsParser::C_castContext *cast = c->c_cast();
    dataflow_type target;
    if (dynamic_cast<ChipsParser::IntTypeContext *>(cast->df_type()))
      target = dataflow_type::INT;
    else if (dynamic_cast<ChipsParser::FloatTypeContext *>(cast->df_type()))
      target = dataflow_type::FLOAT;
    else
      type_fail(cast, "cannot cast to bool");
    auto operand = infer_type(cast->c_stopless_expr());
    if (operand.has_value() && !is_numeric(*operand))
      type_fail(cast, "cast needs a numeric operand, got " + type_name(*operand));
    return target;
  }

  if (auto c = dynamic_cast<ChipsParser::FunctionCallContext *>(e))
  {
    std::string name = c->IDENTIFIER()->getText();
    std::vector<ChipsParser::C_exprContext *> args = c->c_expr();
    if (name == "range" || name == "zeros" || name == "ones")
    {
      if (args.size() != 1)
        type_fail(c, "'" + name + "' takes exactly one int parameter");
      auto t = infer_type(args[0]);
      if (t.has_value() && *t != dataflow_type::INT)
        type_fail(c, "'" + name + "' takes an int parameter, got " + type_name(*t));
      return dataflow_type::INT;
    }
    if (name == "randin01")
    {
      if (!args.empty())
        type_fail(c, "'randin01' takes no parameter");
      return dataflow_type::FLOAT;
    }
    if (name == "is_fresh")
    {
      if (args.size() != 1)
        type_fail(c, "'is_fresh' takes exactly one parameter");
      return dataflow_type::BOOL;
    }
    if (name == "imin" || name == "imax")
    {
      if (args.size() != 2)
        type_fail(c, "'imin/imax' takes exactly two parameters");
      return dataflow_type::INT;
    }
    if (name == "fmin" || name == "fmax")
    {
      if (args.size() != 2)
        type_fail(c, "'fmin/fmax' takes exactly two parameters");
      return dataflow_type::FLOAT;
    }
    type_fail(c, "unknown function '" + name + "'");
  }

  type_fail(e, "unsupported expression");
}

void chips_ast_builder::check_suffixes(ChipsParser::SuffixesContext *ctx) const
{
  for (ChipsParser::ExprContext *e : ctx->expr())
  {
    dataflow_type t = infer_type(e);
    if (t != dataflow_type::INT)
      type_fail(e, "array index must be int, got " + type_name(t));
  }
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::ExprContext *e) const
{
  auto relational = [&](auto *c)
  {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (!is_numeric(l) || l != r)
      type_fail(c, "comparison needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };
  auto equality = [&](auto *c)
  {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (l != r)
      type_fail(c, "equality needs operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };
  auto logical = [&](auto *c)
  {
    dataflow_type l = infer_type(c->expr0());
    dataflow_type r = infer_type(c->expr());
    if (l != dataflow_type::BOOL || r != dataflow_type::BOOL)
      type_fail(c, "logical operator needs bool operands, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::BOOL;
  };

  if (auto c = dynamic_cast<ChipsParser::LTContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::GTContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::LEQContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::GEQContext *>(e))
    return relational(c);
  if (auto c = dynamic_cast<ChipsParser::EQContext *>(e))
    return equality(c);
  if (auto c = dynamic_cast<ChipsParser::NEQContext *>(e))
    return equality(c);
  if (auto c = dynamic_cast<ChipsParser::ANDContext *>(e))
    return logical(c);
  if (auto c = dynamic_cast<ChipsParser::ORContext *>(e))
    return logical(c);
  if (auto c = dynamic_cast<ChipsParser::PassExpr0Context *>(e))
    return infer_type(c->expr0());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr0Context *e) const
{
  auto additive = [&](auto *c)
  {
    dataflow_type l = infer_type(c->expr01());
    dataflow_type r = infer_type(c->expr0());
    if (!is_numeric(l) || l != r)
      type_fail(c, "arithmetic needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return l;
  };

  if (auto c = dynamic_cast<ChipsParser::PLUSContext *>(e))
    return additive(c);
  if (auto c = dynamic_cast<ChipsParser::SUBContext *>(e))
    return additive(c);
  if (auto c = dynamic_cast<ChipsParser::PassExpr01Context *>(e))
    return infer_type(c->expr01());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr01Context *e) const
{
  if (auto c = dynamic_cast<ChipsParser::NegateContext *>(e))
  {
    dataflow_type t = infer_type(c->expr1());
    if (!is_numeric(t))
      type_fail(c, "unary minus needs a numeric operand, got " + type_name(t));
    return t;
  }
  if (auto c = dynamic_cast<ChipsParser::PassExpr1Context *>(e))
    return infer_type(c->expr1());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr1Context *e) const
{
  auto multiplicative = [&](auto *c)
  {
    dataflow_type l = infer_type(c->expr2());
    dataflow_type r = infer_type(c->expr1());
    if (!is_numeric(l) || l != r)
      type_fail(c, "arithmetic needs two numeric operands of the same type, got " + type_name(l) + " and " + type_name(r));
    return l;
  };

  if (auto c = dynamic_cast<ChipsParser::MULTContext *>(e))
    return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::DIVContext *>(e))
    return multiplicative(c);
  if (auto c = dynamic_cast<ChipsParser::MODContext *>(e))
  {
    dataflow_type l = infer_type(c->expr2());
    dataflow_type r = infer_type(c->expr1());
    if (l != dataflow_type::INT || r != dataflow_type::INT)
      type_fail(c, "modulo needs int operands, got " + type_name(l) + " and " + type_name(r));
    return dataflow_type::INT;
  }
  if (auto c = dynamic_cast<ChipsParser::NOTContext *>(e))
  {
    dataflow_type t = infer_type(c->expr2());
    if (t != dataflow_type::BOOL)
      type_fail(c, "'!' needs a bool operand, got " + type_name(t));
    return dataflow_type::BOOL;
  }
  if (auto c = dynamic_cast<ChipsParser::PassExpr2Context *>(e))
    return infer_type(c->expr2());
  type_fail(e, "unsupported expression");
}

dataflow_type chips_ast_builder::infer_type(ChipsParser::Expr2Context *e) const
{
  if (dynamic_cast<ChipsParser::IntLiteralContext *>(e))
    return dataflow_type::INT;
  if (dynamic_cast<ChipsParser::FloatLiteralContext *>(e))
    return dataflow_type::FLOAT;
  if (dynamic_cast<ChipsParser::BoolLiteralContext *>(e))
    return dataflow_type::BOOL;

  if (auto c = dynamic_cast<ChipsParser::VarContext *>(e))
  {
    check_suffixes(c->suffixes());
    return lookup_variable(c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::VarContextContext *>(e))
  {
    check_suffixes(c->suffixes());
    return lookup_variable("ctx." + c->IDENTIFIER()->getText(), c);
  }

  if (auto c = dynamic_cast<ChipsParser::ParensContext *>(e))
    return infer_type(c->expr());

  if (auto c = dynamic_cast<ChipsParser::CastAsContext *>(e))
  {
    ChipsParser::CastContext *cast = c->cast();
    dataflow_type target;
    if (dynamic_cast<ChipsParser::IntTypeContext *>(cast->df_type()))
      target = dataflow_type::INT;
    else if (dynamic_cast<ChipsParser::FloatTypeContext *>(cast->df_type()))
      target = dataflow_type::FLOAT;
    else
      type_fail(cast, "cannot cast to bool");
    dataflow_type operand = infer_type(cast->expr());
    if (!is_numeric(operand))
      type_fail(cast, "cast needs a numeric operand, got " + type_name(operand));
    return target;
  }

  if (auto c = dynamic_cast<ChipsParser::FunctionContext *>(e))
  {
    std::string name = c->IDENTIFIER()->getText();
    std::vector<ChipsParser::ExprContext *> args = c->expr();

    if (name == "range" || name == "zeros" || name == "ones")
    {
      if (args.size() != 1)
        type_fail(c, "'" + name + "' takes exactly one int parameter");
      dataflow_type t = infer_type(args[0]);
      if (t != dataflow_type::INT)
        type_fail(c, "'" + name + "' takes an int parameter, got " + type_name(t));
      return dataflow_type::INT;
    }
    if (name == "randin01")
    {
      if (!args.empty())
        type_fail(c, "'randin01' takes no parameter");
      return dataflow_type::FLOAT;
    }
    if (name == "is_fresh")
    {
      if (args.size() != 1)
        type_fail(c, "'is_fresh' takes exactly one parameter");
      infer_type(args[0]);
      return dataflow_type::BOOL;
    }
    if (name == "imin" || name == "imax")
    {
      if (args.size() != 2)
        type_fail(c, "'imin/imax' takes exactly two parameters");
      return dataflow_type::INT;
    }
    if (name == "fmin" || name == "fmax")
    {
      if (args.size() != 2)
        type_fail(c, "'fmin/fmax' takes exactly two parameters");
      return dataflow_type::FLOAT;
    }
    type_fail(c, "unknown function '" + name + "'");
  }

  type_fail(e, "unsupported expression");
}

template <dataflow_type dft, expression_env expenv>
rvalue<dft, expenv> *as_rvalue(const rvalue_variant<expenv> &v)
{
  if constexpr (expenv == expression_env::COLLECTIVE)
  {
    rvalue<dft, expenv> *converted = std::visit([](auto *p) -> rvalue<dft, expenv> * {
      if (auto *i = dynamic_cast<input *>(p))
      {
        i->m_resolved = dft;
        return i;
      }
      if (auto *s = dynamic_cast<stop *>(p))
      {
        return s;
      }
      return nullptr;
    }, v);
    if (converted != nullptr)
    {
      return converted;
    }
  }
  return std::get<rvalue<dft, expenv> *>(v);
}

template <expression_env expenv>
bool is_free(const rvalue_variant<expenv> &v)
{
  if constexpr (expenv == expression_env::COLLECTIVE)
  {
    return std::visit([](auto *p) { return dynamic_cast<input *>(p) != nullptr || dynamic_cast<stop *>(p) != nullptr; }, v);
  }
  return false;
}

template <expression_env expenv>
rvalue_variant<expenv> eval(chips_ast_builder &b, antlr4::tree::ParseTree *t)
{
  return std::any_cast<rvalue_variant<expenv>>(t->accept(&b));
}

template <typename Variant, typename Base, std::size_t I = 0>
Variant narrow(Base *p)
{
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

template <dataflow_type dft, expression_env expenv>
constexpr dataflow_type dataflow_type_of(const rvalue<dft, expenv> *)
{
  return dft;
}

template <typename... Ts>
dataflow_type dataflow_type_of(const std::variant<Ts...> &v)
{
  return std::visit([](const auto &alt)
                    { return dataflow_type_of(alt); }, v);
}

template <statement_env stenv, recurring_statement recstt, typename Node>
typename SttEnvToSttVariant<stenv>::type as_statement(Node *node)
{
  return typename SttEnvToSttVariant<stenv>::type(static_cast<statement<stenv, recstt> *>(node));
}

template <statement_env stenv, typename StmtCtx>
std::vector<typename SttEnvToSttVariant<stenv>::type>
visit_body(chips_ast_builder &b, const std::vector<StmtCtx *> &stmts)
{
  using body_t = typename SttEnvToSttVariant<stenv>::type;
  std::vector<body_t> body{};
  chips_ast_builder::scope_guard guard(b);
  for (StmtCtx *s : stmts)
  {
    body.push_back(std::any_cast<body_t>(s->accept(&b)));
  }
  return body;
}

template <statement_env stenv>
bool_rvalue_expression_variant<SttEnvToExpEnv<stenv>::value>
to_bool_condition(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                  const rvalue_variant<SttEnvToExpEnv<stenv>::value> &v)
{
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  auto *cond = std::get_if<rvalue<dataflow_type::BOOL, expenv> *>(&v);
  if (cond == nullptr)
  {
    b.type_fail(ctx, "condition must be bool, got " + type_name(dataflow_type_of(v)));
  }
  return narrow<bool_rvalue_expression_variant<expenv>>(*cond);
}

template <statement_env stenv, typename StmtCtx>
if_statement<stenv> *build_if(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                              antlr4::ParserRuleContext *cond_ctx, const std::vector<StmtCtx *> &stmts)
{
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto condition = to_bool_condition<stenv>(b, cond_ctx, std::any_cast<rvalue_variant<expenv>>(cond_ctx->accept(&b)));
  auto body = visit_body<stenv>(b, stmts);
  return b.make_node<if_statement<stenv>>(line, column, condition, if_section<stenv>(line, column, body));
}

template <statement_env stenv, typename IfCtx, typename StmtCtx>
typename SttEnvToSttVariant<stenv>::type
build_if_else(chips_ast_builder &b, antlr4::ParserRuleContext *ctx, IfCtx *if_ctx,
              const std::vector<StmtCtx *> &else_stmts)
{
  using variant_t = typename SttEnvToSttVariant<stenv>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  variant_t visited = std::any_cast<variant_t>(if_ctx->accept(&b));
  auto *if_node = static_cast<if_statement<stenv> *>(std::get<statement<stenv, recurring_statement::IF> *>(visited));
  auto else_body = visit_body<stenv>(b, else_stmts);
  auto *node = b.make_node<if_else_statement<stenv>>(line, column, *if_node,
                                                     else_section<stenv>(line, column, else_body));
  return as_statement<stenv, recurring_statement::IF>(node);
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_iterated_variable(chips_ast_builder &b, ChipsParser::Loop_inContext *ctx,
                                               const std::vector<int_rvalue_expression_variant<expenv>> &dims)
{
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto *var = b.make_node<var_t>(line, column, ctx->IDENTIFIER()->getText(),
                                 std::vector<int_rvalue_expression_variant<expenv>>{});
  auto *expr = b.make_node<variable_expression<dft, expenv>>(line, column, var, dims);
  return rvalue_variant<expenv>(static_cast<rvalue<dft, expenv> *>(expr));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_iterated_variable(chips_ast_builder &b, ChipsParser::C_loop_inContext *ctx,
                                               const std::vector<int_rvalue_expression_variant<expenv>> &dims)
{
  using var_t = typename DataflowVariableAliasType<expenv, dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  auto *var = b.make_node<var_t>(line, column, ctx->IDENTIFIER()->getText(),
                                 std::vector<int_rvalue_expression_variant<expenv>>{});
  auto *expr = b.make_node<variable_expression<dft, expenv>>(line, column, var, dims);
  return rvalue_variant<expenv>(static_cast<rvalue<dft, expenv> *>(expr));
}

template <expression_env expenv>
iterable_variant<expenv> build_iterable(chips_ast_builder &b, ChipsParser::Loop_inContext *ctx)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  if (ctx->L_PARENTH() != nullptr)
  {
    std::vector<rvalue_variant<expenv>> params{};
    for (ChipsParser::ExprContext *e : ctx->expr()) {
      params.push_back(std::any_cast<rvalue_variant<expenv>>(e->accept(&b)));
    }

    if (params.size() != 1 || !std::holds_alternative<rvalue<dataflow_type::INT, expenv> *>(params[0]))
    {
      b.type_fail(ctx, "'" + name + "' takes exactly one int parameter");
    }
    return iterable_variant<expenv>(
        b.make_node<chips::function<dataflow_type::INT, expenv>>(line, column, name, params));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expenv>>>(ctx->suffixes()->accept(&b));
  switch (b.lookup_variable(name, ctx))
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
iterable_variant<expenv> build_iterable(chips_ast_builder &b, ChipsParser::C_loop_inContext *ctx)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  if (ctx->L_PARENTH() != nullptr)
  {
    std::vector<rvalue_variant<expenv>> params{};
    for (ChipsParser::C_exprContext *e : ctx->c_expr()) {
      params.push_back(std::any_cast<rvalue_variant<expenv>>(e->accept(&b)));
    }

    if (params.size() != 1 || !std::holds_alternative<rvalue<dataflow_type::INT, expenv> *>(params[0]))
    {
      b.type_fail(ctx, "'" + name + "' takes exactly one int parameter");
    }
    return iterable_variant<expenv>(
        b.make_node<chips::function<dataflow_type::INT, expenv>>(line, column, name, params));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expenv>>>(ctx->suffixes()->accept(&b));
  switch (b.lookup_variable(name, ctx))
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
dataflow_type iterable_type(const iterable_variant<expenv> &v)
{
  return dataflow_type_of(v);
}

template <statement_env stenv, dataflow_type dft, typename StmtCtx>
typename SttEnvToSttVariant<stenv>::type
build_foreach(chips_ast_builder &b, antlr4::ParserRuleContext *ctx, const std::string &name,
              const iterable_variant<SttEnvToExpEnv<stenv>::value> &iterable,
              const std::vector<StmtCtx *> &stmts)
{
  constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
  using decl_t = dataflow_declaration<dft, stenv>;
  using variable_t = typename SttEnvToVariableKind<dft, stenv>::type;
  using body_t = typename SttEnvToSttVariant<stenv>::type;

  int line = line_of(ctx);
  int column = col_of(ctx);

  variable_t variable(line, column, name, std::vector<int_rvalue_expression_variant<expenv>>{});
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);

  std::vector<body_t> body{};
  {
    chips_ast_builder::scope_guard guard(b);
    b.declare_variable<dft>(name);
    for (StmtCtx *s : stmts)
    {
      body.push_back(std::any_cast<body_t>(s->accept(&b)));
    }
  }

  auto *node = b.make_node<foreach_statement<stenv, dft>>(line, column, decl, iterable, body);
  return as_statement<stenv, recurring_statement::FOREACH>(node);
}

template <block_type bt>
block_expression_variant build_block_expression(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx, const std::string &name,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> &dims)
{
  auto *var = b.make_node<block_variable<bt>>(
      line_of(ctx), col_of(ctx), name, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{});
  return block_expression_variant(
      b.make_node<system_variable_block_expression<bt>>(line_of(ctx), col_of(ctx), var, dims));
}

block_expression_variant make_block_expression(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx, const std::string &name,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> &dims)
{
  switch (b.lookup_block(name, ctx).first)
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

node_variable_expression *node_of(const block_expression_variant &block)
{
  if (auto *p = std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(&block))
    return *p;
  if (auto *o = std::get_if<system_variable_block_expression<block_type::OBJECT> *>(&block))
    return *o;
  return nullptr;
}

functional_block_variant functional_of(antlr4::ParserRuleContext *ctx, const block_expression_variant &block)
{
  if (auto *l = std::get_if<system_variable_block_expression<block_type::LOGICAL> *>(&block))
    return functional_block_variant(*l);
  if (auto *p = std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(&block))
    return functional_block_variant(*p);
  semantic_fail(ctx, "an object has neither parameters nor outputs");
}

template <block_type bt>
typename BlockTypeToBlockDef<bt>::type *definition_of(const chips_ast_builder &b, const std::string &name)
{
  if constexpr (bt == block_type::LOGICAL)
    return b.lookup_logical(name);
  else if constexpr (bt == block_type::PHYSICAL)
    return b.lookup_physical(name);
  else
    return b.lookup_object(name);
}

template <block_type bt>
system_statement_variant build_block_declaration(
    chips_ast_builder &b, ChipsParser::ObjectDeclarationContext *ctx,
    typename BlockTypeToBlockDef<bt>::type *definition,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> &dims)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER(1)->getText();

  block_variable<bt> variable(line, column, name, dims);
  auto *decl = b.make_node<block_declaration<bt>>(line, column, definition, variable);
  decl->m_variable.m_declaration = decl;
  b.declare_block(name, bt, ctx->IDENTIFIER(0)->getText());
  return system_statement_variant(static_cast<system_statement<recurring_statement::DECLARATION> *>(decl));
}

template <dataflow_kind dfk, dataflow_type dft, typename List>
feeder_variant build_output_feeder(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                   const functional_block_variant &block, List &outputs, const std::string &name)
{
  for (auto &candidate : outputs)
  {
    auto *typed = std::get_if<function_output<dfk, dft> *>(&candidate);
    if (typed != nullptr && (*typed)->get_name() == name)
    {
      auto *node = b.make_node<feeder_block_expression<dfk, dft>>(line_of(ctx), col_of(ctx), block, *typed);
      return feeder_variant(static_cast<feeder<dfk, dft> *>(node));
    }
  }
  semantic_fail(ctx, "output '" + name + "' not found");
}

s_expr_variant resolve_block_output(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                    ChipsParser::BlockContext *block_ctx, const std::string &output)
{
  auto block = std::any_cast<block_expression_variant>(block_ctx->accept(&b));
  std::string definition = b.lookup_block(block_ctx->IDENTIFIER()->getText(), block_ctx).second;

  if (auto *channel = b.lookup_channel(definition, output))
  {
    return s_expr_variant(b.make_node<channel_feeder>(line_of(ctx), col_of(ctx), node_of(block), channel));
  }

  functional_block_variant source = functional_of(ctx, block);
  if (auto type = b.lookup_actuator(definition, output))
  {
    auto *physical = b.lookup_physical(definition);
    return s_expr_variant(by_type(*type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_output_feeder<dataflow_kind::PHYSICAL, dft>(b, ctx, source, physical->m_actuators, output);
    }));
  }
  if (auto type = b.lookup_output(definition, output))
  {
    auto *function = b.lookup_function(definition);
    return s_expr_variant(by_type(*type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_output_feeder<dataflow_kind::LOGICAL, dft>(b, ctx, source, function->get_outputs(), output);
    }));
  }
  semantic_fail(ctx, "'" + output + "' is neither an output, an actuator nor a channel of '" + definition + "'");
}

template <dataflow_kind dfk, dataflow_type dft, typename List>
system_statement_variant feed_parameter(chips_ast_builder &b, ChipsParser::FeedingStatementContext *ctx,
                                        const functional_block_variant &block, List &parameters,
                                        const feeder_variant &source)
{
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
    semantic_fail(ctx, "parameter '" + name + "' cannot be fed by this expression");
  }
  auto *node = b.make_node<feeding_statement<dfk, dft>>(
      line, column, eater<dfk, dft>(line, column, block, parameter), *fed);
  return system_statement_variant(static_cast<system_statement<recurring_statement::FEEDING> *>(node));
}

template <dataflow_type dft>
feeder_variant as_feeder(rvalue<dft, expression_env::SYSTEM> *value)
{
  return feeder_variant(static_cast<feeder<dataflow_kind::LOGICAL, dft> *>(value));
}

template <dataflow_kind dfk, dataflow_type dft>
feeder_variant build_collective_cast(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                     collective_function_definition *collective, feeder<dfk, dft> *inner)
{
  auto *cast = b.make_node<collective_cast<dfk, dft>>(line_of(ctx), col_of(ctx), collective, *inner);
  return feeder_variant(static_cast<feeder<dfk, dft> *>(cast));
}

template <dataflow_type dft>
system_statement_variant build_system_declaration(
    chips_ast_builder &b, ChipsParser::StatementDeclarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> &dims)
{
  using decl_t = dataflow_declaration<dft, statement_env::SYSTEM>;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_system_variable<dft> variable(line, column, name, dims);
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);
  b.declare_variable<dft>(name);
  return system_statement_variant(static_cast<system_statement<recurring_statement::DECLARATION> *>(decl));
}

template <dataflow_type dft>
system_statement_variant build_system_assignment(
    chips_ast_builder &b, ChipsParser::StatementAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> &dims,
    const rvalue_variant<expression_env::SYSTEM> &rhs)
{
  using assign_t = dataflow_assignment<dft, statement_env::SYSTEM>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = b.make_node<dataflow_system_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{});
  auto *lhs = b.make_node<variable_expression<dft, expression_env::SYSTEM>>(line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, as_rvalue<dft>(rhs));
  return system_statement_variant(static_cast<system_statement<recurring_statement::ASSIGNMENT> *>(assign));
}

template <block_type bt>
system_statement_variant build_block_foreach(chips_ast_builder &b, ChipsParser::S_loop_statementContext *ctx,
                                             const std::string &name, system_variable_block_expression<bt> *iterable)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string definition = b.lookup_block(iterable->get_variable()->get_name(), ctx).second;

  block_variable<bt> variable(line, column, name, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{});
  auto *decl = b.make_node<block_declaration<bt>>(line, column, definition_of<bt>(b, definition), variable);
  decl->m_variable.m_declaration = decl;

  std::vector<system_statement_variant> body{};
  {
    chips_ast_builder::scope_guard guard(b);
    b.declare_block(name, bt, definition);
    for (ChipsParser::S_statementContext *stmt : ctx->s_statement())
    {
      body.push_back(std::any_cast<system_statement_variant>(stmt->accept(&b)));
    }
  }
  auto *node = b.make_node<block_foreach_statement<bt>>(line, column, decl, iterable, body);
  return system_statement_variant(static_cast<system_statement<recurring_statement::FOREACH> *>(node));
}

template <dataflow_type dft>
system_iterable_variant build_system_iterable_variable(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                                       const std::string &name)
{
  auto *var = b.make_node<dataflow_system_variable<dft>>(
      line_of(ctx), col_of(ctx), name, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{});
  auto *expr = b.make_node<variable_expression<dft, expression_env::SYSTEM>>(line_of(ctx), col_of(ctx), var);
  return system_iterable_variant(iterable_variant<expression_env::SYSTEM>(
      rvalue_variant<expression_env::SYSTEM>(static_cast<rvalue<dft, expression_env::SYSTEM> *>(expr))));
}


// Visit methods

std::any chips_ast_builder::visitProgram(ChipsParser::ProgramContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::vector<definition_variant> defs{};
  for (ChipsParser::PreambleContext *def : ctx->preamble())
  {
    definition_variant dv = std::any_cast<definition_variant>(def->accept(this));
    defs.push_back(dv);
  }

  system_section_node system = std::any_cast<system_section_node>(ctx->system()->accept(this));
  return program_node(
      line_of(ctx),
      col_of(ctx),
      std::string("ChipsModel"),
      preamble_section_node(0, 0, defs),
      system);
}

std::any chips_ast_builder::visitSystem(ChipsParser::SystemContext *ctx)
{
  VERBOSE_VISIT_ENTER
  m_system_reached = true;
  m_current_def_name.clear();
  m_support_name.clear();
  scope_guard system_scope(*this);

  std::vector<system_statement_variant> statements{};
  for (ChipsParser::S_statementContext *stmt : ctx->s_statement())
  {
    statements.push_back(std::any_cast<system_statement_variant>(stmt->accept(this)));
  }
  return system_section_node(line_of(ctx), col_of(ctx), statements);
}

std::any chips_ast_builder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->object_def()->accept(this);
}

std::any chips_ast_builder::visitObject_def(ChipsParser::Object_defContext *ctx)
{
  VERBOSE_VISIT_ENTER
  m_current_def_name = ctx->IDENTIFIER()->getText();
  with_section with = std::any_cast<with_section>(ctx->with_section()->accept(this));

  auto *object = make_node<object_definition>(line_of(ctx), col_of(ctx), m_current_def_name, with);
  declare_definition(m_current_def_name, object);
  return definition_variant(object);
}

std::any
chips_ast_builder::visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->function_def()->accept(this);
}

std::any chips_ast_builder::visitCollectiveOperationDefinition(
    ChipsParser::CollectiveOperationDefinitionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->collective_op_def()->accept(this);
}

std::any
chips_ast_builder::visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->l_function_def()->accept(this);
}

std::any
chips_ast_builder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->p_function_def()->accept(this);
}

std::any chips_ast_builder::visitC_keywords(ChipsParser::C_keywordsContext *ctx)
{
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
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_collective_variable<dft> variable(line, column, name, dims);
  auto *decl = self->make_node<dataflow_declaration<dft, statement_env::COLLECTIVE>>(line, column, variable);
  decl->m_variable.set_declaration(decl);

  std::optional<dataflow_type> t = self->infer_type(ctx->c_expr());
  if (t.has_value() && *t != dft)
  {
    self->type_fail(ctx->c_expr(), "accumulator '" + name + "' is declared " + type_name(dft) +
                                       " but its default value is " + type_name(*t));
  }
  auto *default_value = std::get<rvalue<dft, expression_env::COLLECTIVE> *>(
      std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(ctx->c_expr()->accept(self)));

  auto *param = self->make_node<collective_parameter<dft>>(line, column, name, decl, default_value);
  self->declare_variable<dft>(name);
  return collective_parameter_variant(param);
}

std::any chips_ast_builder::visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type dft = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
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

std::any chips_ast_builder::visitC_default_output(ChipsParser::C_default_outputContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    expressions.push_back(std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(e->accept(this)));
  }
  return default_output(line_of(ctx), col_of(ctx), expressions);
}

std::any chips_ast_builder::visitC_channeled_output(ChipsParser::C_channeled_outputContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  auto *channel = lookup_channel(m_support_name, name);
  if (channel == nullptr)
  {
    semantic_fail(ctx, "channel '" + name + "' is not declared in node '" + m_support_name + "'");
  }

  std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    expressions.push_back(std::any_cast<rvalue_variant<expression_env::COLLECTIVE>>(e->accept(this)));
  }
  return channeled_output(line_of(ctx), col_of(ctx), channel, expressions);
}

std::any chips_ast_builder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx)
{
  VERBOSE_VISIT_ENTER
  m_collective_inputs.clear();
  expected_type_for_input.reset();

  ChipsParser::C_signatureContext *signature = ctx->c_signature();
  std::string name = signature->IDENTIFIER(0)->getText();
  std::string support_name = signature->IDENTIFIER(1)->getText();
  int line = line_of(ctx);
  int column = col_of(ctx);

  node_definition *support = lookup_node(support_name);
  m_current_def_name = name;
  m_support_name = support_name;
  scope_guard function_scope(*this);

  collective_function_type type = std::any_cast<collective_function_type>(signature->c_keywords()->accept(this));

  std::vector<collective_parameter_variant> accumulators{};
  for (ChipsParser::Cdf_defaulted_declContext *decl : signature->cdf_defaulted_decl())
  {
    accumulators.push_back(std::any_cast<collective_parameter_variant>(decl->accept(this)));
  }
  accumulator_definition accumulator(line_of(signature), col_of(signature), accumulators);

  collectiveops_section operations(line, column);
  for (ChipsParser::C_statementContext *stmt : ctx->c_statement())
  {
    operations.add_statement(std::any_cast<collective_statement_variant>(stmt->accept(this)));
  }

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
    channeled.push_back(std::any_cast<channeled_output>(out->accept(this)));
    covered.insert(out->IDENTIFIER()->getText());
  }

  std::optional<default_output> default_out;
  if (ctx->c_default_output() != nullptr)
  {
    if (covered.size() == channel_count(support_name))
    {
      semantic_fail(ctx->c_default_output(),
                    "default output is unreachable: every channel of node '" + support_name + "' already has an output");
    }
    default_out = std::any_cast<default_output>(ctx->c_default_output()->accept(this));
  }

  std::optional<dataflow_type> input_type;
  for (input *used : m_collective_inputs)
  {
    if (!used->m_resolved.has_value())
      continue;
    if (input_type.has_value() && *input_type != *used->m_resolved)
    {
      throw std::runtime_error("line " + std::to_string(used->get_line()) + ": 'input' is used as " +
                               type_name(*input_type) + " and as " + type_name(*used->m_resolved) +
                               " in collective definition '" + name + "'");
    }
    input_type = used->m_resolved;
    used->m_resolved.reset();
  }

  auto *function = make_node<collective_function_definition>(
      line, column, name, type, accumulator, support, operations, target, default_out, channeled);
  declare_collective(name, function);
  m_support_name.clear();
  return definition_variant(function);
}

template <dataflow_type dft, dataflow_kind dfk, expression_env expenv, typename Ctx>
std::any interpret_param(Ctx *ctx, chips_ast_builder *self, std::vector<int_rvalue_expression_variant<expenv>> dims)
{
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_primitive_variable<dft> variable(line, column, name, dims);
  auto *decl = self->make_node<dataflow_declaration<dft, statement_env::DEFINITION>>(line, column, variable);
  decl->m_variable.set_declaration(decl);

  rvalue<dft, expression_env::PRIMITIVE> *default_value = nullptr;
  if (ctx->expr() != nullptr)
  {
    dataflow_type t = self->infer_type(ctx->expr());
    if (t != dft)
    {
      self->type_fail(ctx->expr(), "parameter '" + name + "' is declared " + type_name(dft) +
                                       " but its default value is " + type_name(t));
    }
    default_value = std::get<rvalue<dft, expression_env::PRIMITIVE> *>(
        std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(ctx->expr()->accept(self)));
  }

  auto *param = self->make_node<function_parameter<dfk, dft>>(line, column, name, decl, default_value);
  if constexpr (dfk == dataflow_kind::PHYSICAL)
  {
    self->declare_sensor(self->current_definition(), name, dft);
    return physical_parameter_variant(param);
  }
  else
  {
    return function_parameter_variant(param);
  }
}

std::any chips_ast_builder::visitL_function_def(ChipsParser::L_function_defContext *ctx)
{
  VERBOSE_VISIT_ENTER
  m_current_def_name = ctx->IDENTIFIER()->getText();
  scope_guard function_scope(*this);

  std::vector<function_parameter_variant> parameters{};
  for (ChipsParser::Df_parameter_declContext *param : ctx->df_parameter_decl())
  {
    parameters.push_back(std::any_cast<function_parameter_variant>(param->accept(this)));
    declare_parameter(m_current_def_name, param->IDENTIFIER()->getText(),
                      std::any_cast<dataflow_type>(param->df_type()->accept(this)));
  }

  init_section init = std::any_cast<init_section>(ctx->init_section()->accept(this));
  then_section then = std::any_cast<then_section>(ctx->then_section()->accept(this));

  std::vector<function_output_variant> outputs{};
  for (ChipsParser::Named_outputContext *out : ctx->named_output())
  {
    outputs.push_back(std::any_cast<function_output_variant>(out->accept(this)));
  }

  auto * logical = make_node<logical_definition>(
      line_of(ctx),
      col_of(ctx),
      ctx->IDENTIFIER()->getText(), parameters,
      init, then,
      outputs
    );
  declare_definition(m_current_def_name, logical);

  return definition_variant(logical);
}

std::any chips_ast_builder::visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type dft = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims{};
  if (ctx->suffixes() != nullptr)
  {
    dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
        ctx->suffixes()->accept(this));
  }

  switch (dft)
  {
  case dataflow_type::INT:
    return interpret_param<dataflow_type::INT, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::FLOAT:
    return interpret_param<dataflow_type::FLOAT, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::BOOL:
    return interpret_param<dataflow_type::BOOL, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  }
  throw std::runtime_error("Unknown dataflow type!");
}

std::any chips_ast_builder::visitP_function_def(ChipsParser::P_function_defContext *ctx)
{
  VERBOSE_VISIT_ENTER
  m_current_def_name = std::string(ctx->IDENTIFIER()->getText());
  scope_guard function_scope(*this);

  std::vector<function_parameter_variant> parameters{};
  std::vector<physical_parameter_variant> sensors{};
  for (ChipsParser::Pdf_parameter_declContext *param : ctx->pdf_parameter_decl())
  {
    std::string name = param->IDENTIFIER()->getText();
    ChipsParser::Pdf_parameter_typeContext *ptype = param->pdf_parameter_type();

    if (auto *sensor = dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptype))
    {
      sensors.push_back(std::any_cast<physical_parameter_variant>(param->accept(this)));
      declare_parameter(m_current_def_name, name, std::any_cast<dataflow_type>(sensor->df_type()->accept(this)));
    }
    else
    {
      auto *fn = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptype);
      parameters.push_back(std::any_cast<function_parameter_variant>(param->accept(this)));
      declare_parameter(m_current_def_name, name, std::any_cast<dataflow_type>(fn->df_type()->accept(this)));
    }
  }

  with_section with = std::any_cast<with_section>(ctx->with_section()->accept(this));
  init_section init = std::any_cast<init_section>(ctx->init_section()->accept(this));
  then_section then = std::any_cast<then_section>(ctx->then_section()->accept(this));
  std::vector<function_output_variant> outputs{};
  std::vector<physical_output_variant> actuators{};
  for (ChipsParser::P_named_outputContext *out : ctx->p_named_output())
  {
    if (dynamic_cast<ChipsParser::ActuatorOutputContext *>(out) != nullptr)
    {
      actuators.push_back(std::any_cast<physical_output_variant>(out->accept(this)));
    }
    else
    {
      outputs.push_back(std::any_cast<function_output_variant>(out->accept(this)));
    }
  }

  auto *physical = make_node<physical_definition>(
      line_of(ctx),
      col_of(ctx),
      ctx->IDENTIFIER()->getText(), parameters, sensors,
      with, init, then,
      outputs, actuators);
  
  declare_definition(m_current_def_name, physical);

  return definition_variant(physical);
}

std::any chips_ast_builder::visitC_signature(ChipsParser::C_signatureContext *ctx)
{
  VERBOSE_VISIT_ENTER
  UNIMPLEMENTED_METHOD;
}

std::any chips_ast_builder::visitWith_section(ChipsParser::With_sectionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  with_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::With_statementContext *stmt : ctx->with_statement())
  {
    section.add_statement(std::any_cast<node_statement_variant>(stmt->accept(this)));
  }
  return section;
}

std::any chips_ast_builder::visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto *decl = make_node<node_element_declaration<node_element::CHANNEL>>(
      line_of(ctx),
      col_of(ctx),
      ctx->IDENTIFIER(0)->getText(),
      ctx->IDENTIFIER(1)->getText());
  declare_channel(ctx->IDENTIFIER(1)->getText(), decl);
  return node_statement_variant(decl);
}

template <dataflow_type dft>
node_statement_variant build_contextual_declaration(
    chips_ast_builder &builder,
    ChipsParser::ContextualDeclarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> &dims)
{
  using decl_t = typename DfTypeToContextualDeclType<dft>::type;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  std::optional<rvalue_variant<expression_env::PRIMITIVE>> init;
  if (ctx->expr() != nullptr)
  {
    dataflow_type t = builder.infer_type(ctx->expr());
    if (t != dft)
    {
      builder.type_fail(ctx->expr(), "contextual variable '" + name + "' is declared " +
                                         type_name(dft) + " but initialized with " + type_name(t));
    }
    init = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(ctx->expr()->accept(&builder));
  }

  contextual_variable<dft> variable(line, column, name, dims);
  decl_t *decl = builder.make_node<decl_t>(line, column, variable, name);
  decl->m_variable_type.set_declaration(decl);
  if (init)
    decl->set_initializer(*init);

  builder.declare_contextual("ctx." + name, dft);
  return node_statement_variant(decl);
}

std::any chips_ast_builder::visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
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
  VERBOSE_VISIT_ENTER
  UNIMPLEMENTED_METHOD;
}

std::any chips_ast_builder::visitInit_section(ChipsParser::Init_sectionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  init_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext *stmt : ctx->statement())
  {
    section.add_statement(std::any_cast<primitive_statement_variant>(stmt->accept(this)));
  }
  return section;
}

std::any chips_ast_builder::visitThen_section(ChipsParser::Then_sectionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  then_section section(line_of(ctx), col_of(ctx));
  for (ChipsParser::StatementContext *stmt : ctx->statement())
  {
    section.add_statement(std::any_cast<primitive_statement_variant>(stmt->accept(this)));
  }
  return section;
}

template <expression_env expenv>
dataflow_type type_of(const rvalue_variant<expenv> &v)
{
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

template <template <dataflow_type, expression_env> class Node, dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_binary(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                    const rvalue_variant<expenv> &l, const rvalue_variant<expenv> &r)
{
  using node_t = Node<dft, expenv>;
  return rvalue_variant<expenv>(
      b.make_node<node_t>(line_of(ctx), col_of(ctx), as_rvalue<dft>(l), as_rvalue<dft>(r)));
}

template <template <dataflow_type, expression_env> class Node, expression_env expenv>
rvalue_variant<expenv> build_numeric(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                     const rvalue_variant<expenv> &l, const rvalue_variant<expenv> &r)
{
  dataflow_type type = is_free<expenv>(l) ? type_of<expenv>(r) : type_of<expenv>(l);
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

template <template <dataflow_type, expression_env> class Node, expression_env expenv>
rvalue_variant<expenv> build_any(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                 const rvalue_variant<expenv> &l, const rvalue_variant<expenv> &r)
{
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

template <template <dataflow_type dft, expression_env expenv> class Node, expression_env expenv>
rvalue_variant<expenv> build_unary_numeric(chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
                                           const rvalue_variant<expenv> &operand)
{
  switch (type_of<expenv>(operand))
  {
  case dataflow_type::INT:
    return rvalue_variant<expenv>(
        b.make_node<Node<dataflow_type::INT, expenv>>(
            line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(operand)));
  case dataflow_type::FLOAT:
    return rvalue_variant<expenv>(
        b.make_node<Node<dataflow_type::FLOAT, expenv>>(
            line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::FLOAT>(operand)));
  default:
    break;
  }
  throw std::runtime_error("numeric operand expected");
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_var(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const std::string &name,
    const std::vector<int_rvalue_expression_variant<expenv>> &dims)
{
  if constexpr (expenv == expression_env::PRIMITIVE)
  {
    auto *var = b.make_node<dataflow_primitive_variable<dft>>(
        line_of(ctx), col_of(ctx), name,
        std::vector<int_rvalue_expression_variant<expenv>>{});

    return rvalue_variant<expenv>(
        b.make_node<variable_expression<dft, expenv>>(
            line_of(ctx), col_of(ctx), var, dims));
  }
  else if constexpr (expenv == expression_env::COLLECTIVE)
  {
    auto *var = b.make_node<dataflow_collective_variable<dft>>(
        line_of(ctx), col_of(ctx), name,
        std::vector<int_rvalue_expression_variant<expenv>>{});

    return rvalue_variant<expenv>(
        b.make_node<variable_expression<dft, expenv>>(
            line_of(ctx), col_of(ctx), var, dims));
  }
  else
  {
    auto *var = b.make_node<dataflow_system_variable<dft>>(
        line_of(ctx), col_of(ctx), name,
        std::vector<int_rvalue_expression_variant<expenv>>{});

    return rvalue_variant<expenv>(
        b.make_node<variable_expression<dft, expenv>>(
            line_of(ctx), col_of(ctx), var, dims));
  }
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_ctx_var(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const std::string &name,
    const std::vector<int_rvalue_expression_variant<expenv>> &dims)
{
  auto *var = b.make_node<contextual_variable<dft>>(
      line_of(ctx), col_of(ctx), name,
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>{});

  return rvalue_variant<expenv>(
      b.make_node<variable_contextual_expression<dft, expenv>>(
          line_of(ctx), col_of(ctx), var, dims));
}

template <dataflow_type dft>
rvalue_variant<expression_env::COLLECTIVE> build_channeled_accu(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    node_element_declaration<node_element::CHANNEL> *channel,
    const std::string &accumulator,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims)
{
  auto *var = b.make_node<dataflow_collective_variable<dft>>(
      line_of(ctx), col_of(ctx), accumulator,
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>{});
  auto *expr = b.make_node<channeled_accumulator_expression<dft>>(
      line_of(ctx), col_of(ctx), channel, var, dims);
  return rvalue_variant<expression_env::COLLECTIVE>(
      static_cast<rvalue<dft, expression_env::COLLECTIVE> *>(expr));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_function(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const std::string &name,
    const std::vector<rvalue_variant<expenv>> &params)
{
  return rvalue_variant<expenv>(
      b.make_node<chips::function<dft, expenv>>(
          line_of(ctx), col_of(ctx), name, params));
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> build_cast(
    chips_ast_builder &b, antlr4::ParserRuleContext *ctx,
    const rvalue_variant<expenv> &operand)
{
  constexpr dataflow_type other =
      dft == dataflow_type::INT ? dataflow_type::FLOAT : dataflow_type::INT;

  if (type_of<expenv>(operand) == dft)
    return operand;

  return rvalue_variant<expenv>(
      b.make_node<cast_as<dft, expenv>>(
          line_of(ctx), col_of(ctx), as_rvalue<other>(operand)));
}

std::any chips_ast_builder::visitLT(ChipsParser::LTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<lt>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr()));
  });
}

std::any chips_ast_builder::visitGT(ChipsParser::GTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type dft = infer_type(ctx);
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<gt>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr()));
  });
}

std::any chips_ast_builder::visitLEQ(ChipsParser::LEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type dft = infer_type(ctx);
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<leq>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr()));
  });
}

std::any chips_ast_builder::visitGEQ(ChipsParser::GEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type dft = infer_type(ctx);
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    return build_numeric<geq>(*this, ctx, eval<e>(*this, ctx->expr0()), eval<e>(*this, ctx->expr()));
  });
}

std::any chips_ast_builder::visitNEQ(ChipsParser::NEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_any<chips::neq>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr0()), eval<expression_env::PRIMITIVE>(*this, ctx->expr()));
}

std::any chips_ast_builder::visitEQ(ChipsParser::EQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_any<chips::eq>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr0()), eval<expression_env::PRIMITIVE>(*this, ctx->expr()));
}

std::any chips_ast_builder::visitAND(ChipsParser::ANDContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::PRIMITIVE> l = eval<expression_env::PRIMITIVE>(*this, ctx->expr0());
  rvalue_variant<expression_env::PRIMITIVE> r = eval<expression_env::PRIMITIVE>(*this, ctx->expr());
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<and_operator<expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitOR(ChipsParser::ORContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::PRIMITIVE> l = eval<expression_env::PRIMITIVE>(*this, ctx->expr0());
  rvalue_variant<expression_env::PRIMITIVE> r = eval<expression_env::PRIMITIVE>(*this, ctx->expr());
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<or_operator<expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->expr0()->accept(this);
}

std::any chips_ast_builder::visitPLUS(ChipsParser::PLUSContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::plus>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr01()), eval<expression_env::PRIMITIVE>(*this, ctx->expr0()));
}

std::any chips_ast_builder::visitSUB(ChipsParser::SUBContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::minus>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr01()), eval<expression_env::PRIMITIVE>(*this, ctx->expr0()));
}

std::any chips_ast_builder::visitPassExpr01(ChipsParser::PassExpr01Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->expr01()->accept(this);
}

std::any chips_ast_builder::visitNegate(ChipsParser::NegateContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_unary_numeric<chips::uminus_operator>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr1()));
}

std::any chips_ast_builder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->expr1()->accept(this);
}

std::any chips_ast_builder::visitMULT(ChipsParser::MULTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::mult>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr2()), eval<expression_env::PRIMITIVE>(*this, ctx->expr1()));
}

std::any chips_ast_builder::visitDIV(ChipsParser::DIVContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::div>(*this, ctx, eval<expression_env::PRIMITIVE>(*this, ctx->expr2()), eval<expression_env::PRIMITIVE>(*this, ctx->expr1()));
}

std::any chips_ast_builder::visitMOD(ChipsParser::MODContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::PRIMITIVE> l = eval<expression_env::PRIMITIVE>(*this, ctx->expr2());
  rvalue_variant<expression_env::PRIMITIVE> r = eval<expression_env::PRIMITIVE>(*this, ctx->expr1());
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<mod<expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(l), as_rvalue<dataflow_type::INT>(r)));
}

std::any chips_ast_builder::visitNOT(ChipsParser::NOTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::PRIMITIVE> operand = eval<expression_env::PRIMITIVE>(*this, ctx->expr2());
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<not_operator<expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(operand)));
}

std::any chips_ast_builder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->expr2()->accept(this);
}

// std::any chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx)
// {
//   VERBOSE_VISIT_ENTER
//   return rvalue_variant<expression_env::PRIMITIVE>(make_node<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(
//       line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
// }

std::any chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    return rvalue_variant<e>(make_node<direct<dataflow_type::INT, e>>(
        line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
  });
}

std::any chips_ast_builder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), std::stod(ctx->FLOAT()->getText())));
}

std::any chips_ast_builder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::PRIMITIVE>(make_node<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(
      line_of(ctx), col_of(ctx), ctx->BOOL()->getText() == "true"));
}

// std::any chips_ast_builder::visitVar(ChipsParser::VarContext *ctx)
// {
//   VERBOSE_VISIT_ENTER
//   dataflow_type t = infer_type(ctx);
//   std::string name = ctx->IDENTIFIER()->getText();
//   std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims =
//       std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(ctx->suffixes()->accept(this));
//   switch (t)
//   {
//   case dataflow_type::INT:
//     return build_var<dataflow_type::INT, expression_env::PRIMITIVE>(*this, ctx, name, dims);
//   case dataflow_type::FLOAT:
//     return build_var<dataflow_type::FLOAT, expression_env::PRIMITIVE>(*this, ctx, name, dims);
//   case dataflow_type::BOOL:
//     return build_var<dataflow_type::BOOL, expression_env::PRIMITIVE>(*this, ctx, name, dims);
//   }
//   throw std::runtime_error("unknown dataflow_type in visitVar");
// }

std::any chips_ast_builder::visitVar(ChipsParser::VarContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type type = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<e>>>(ctx->suffixes()->accept(this));
    return by_type(type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_var<dft, e>(*this, ctx, name, dims);
    });
  });
}

std::any chips_ast_builder::visitParens(ChipsParser::ParensContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->expr()->accept(this);
}

std::any chips_ast_builder::visitVarContext(ChipsParser::VarContextContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type t = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims =
      std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(ctx->suffixes()->accept(this));
  switch (t)
  {
  case dataflow_type::INT:
    return build_ctx_var<dataflow_type::INT, expression_env::PRIMITIVE>(*this, ctx, name, dims);
  case dataflow_type::FLOAT:
    return build_ctx_var<dataflow_type::FLOAT, expression_env::PRIMITIVE>(*this, ctx, name, dims);
  case dataflow_type::BOOL:
    return build_ctx_var<dataflow_type::BOOL, expression_env::PRIMITIVE>(*this, ctx, name, dims);
  }
  throw std::runtime_error("unknown dataflow_type in visitVarContext");
}

std::any chips_ast_builder::visitFunction(ChipsParser::FunctionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type t = infer_type(ctx);
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_variant<expression_env::PRIMITIVE>> params{};
  for (ChipsParser::ExprContext *e : ctx->expr())
  {
    params.push_back(eval<expression_env::PRIMITIVE>(*this, e));
  }
  switch (t)
  {
  case dataflow_type::INT:
    return build_function<dataflow_type::INT, expression_env::PRIMITIVE>(*this, ctx, name, params);
  case dataflow_type::FLOAT:
    return build_function<dataflow_type::FLOAT, expression_env::PRIMITIVE>(*this, ctx, name, params);
  case dataflow_type::BOOL:
    return build_function<dataflow_type::BOOL, expression_env::PRIMITIVE>(*this, ctx, name, params);
  }
  throw std::runtime_error("unknown dataflow_type in visitFunction");
}

std::any chips_ast_builder::visitCastAs(ChipsParser::CastAsContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return ctx->cast()->accept(this);
}

std::any chips_ast_builder::visitCast(ChipsParser::CastContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type target = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  rvalue_variant<expression_env::PRIMITIVE> operand = eval<expression_env::PRIMITIVE>(*this, ctx->expr());
  switch (target)
  {
  case dataflow_type::INT:
    return build_cast<dataflow_type::INT, expression_env::PRIMITIVE>(*this, ctx, operand);
  case dataflow_type::FLOAT:
    return build_cast<dataflow_type::FLOAT, expression_env::PRIMITIVE>(*this, ctx, operand);
  default:
    break;
  }
  throw std::runtime_error("cast to bool is not allowed");
}

std::any chips_ast_builder::visitSuffixes(ChipsParser::SuffixesContext *ctx)
{
  VERBOSE_VISIT_ENTER
  check_suffixes(ctx);
  return by_env(*this, [&](auto env) {
    constexpr expression_env e = decltype(env)::value;
    std::vector<int_rvalue_expression_variant<e>> dims{};
    for (ChipsParser::ExprContext *expr : ctx->expr())
    {
      dims.push_back(narrow<int_rvalue_expression_variant<e>>(as_rvalue<dataflow_type::INT>(eval<e>(*this, expr))));
    }
    return dims;
  });
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

std::any chips_ast_builder::visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr()->accept(this);
}

std::any chips_ast_builder::visitStop(ChipsParser::StopContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto *node = make_node<stop>(line_of(ctx), col_of(ctx));
  return rvalue_variant<expression_env::COLLECTIVE>(
      static_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE> *>(node));
}

std::any chips_ast_builder::visitINPUT(ChipsParser::INPUTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto *node = make_node<input>(line_of(ctx), col_of(ctx));
  m_collective_inputs.push_back(node);
  return rvalue_variant<expression_env::COLLECTIVE>(
      static_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE> *>(node));
}

std::any chips_ast_builder::visitCLT(ChipsParser::CLTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<lt>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCGT(ChipsParser::CGTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<gt>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCLEQ(ChipsParser::CLEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<leq>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCGEQ(ChipsParser::CGEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<geq>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCNEQ(ChipsParser::CNEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_any<chips::neq>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCEQ(ChipsParser::CEQContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_any<chips::eq>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr()));
}

std::any chips_ast_builder::visitCAND(ChipsParser::CANDContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0());
  rvalue_variant<expression_env::COLLECTIVE> r = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<and_operator<expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitCOR(ChipsParser::CORContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0());
  rvalue_variant<expression_env::COLLECTIVE> r = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<or_operator<expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(l), as_rvalue<dataflow_type::BOOL>(r)));
}

std::any chips_ast_builder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr0()->accept(this);
}

std::any chips_ast_builder::visitCPLUS(ChipsParser::CPLUSContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::plus>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr01()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()));
}

std::any chips_ast_builder::visitCSUB(ChipsParser::CSUBContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::minus>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr01()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr0()));
}

std::any chips_ast_builder::visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr01()->accept(this);
}

std::any chips_ast_builder::visitCNegate(ChipsParser::CNegateContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_unary_numeric<chips::uminus_operator>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any chips_ast_builder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr1()->accept(this);
}

std::any chips_ast_builder::visitCMULT(ChipsParser::CMULTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::mult>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any chips_ast_builder::visitCDIV(ChipsParser::CDIVContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return build_numeric<chips::div>(*this, ctx, eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2()), eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1()));
}

std::any chips_ast_builder::visitCMOD(ChipsParser::CMODContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> l = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2());
  rvalue_variant<expression_env::COLLECTIVE> r = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr1());
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<mod<expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::INT>(l), as_rvalue<dataflow_type::INT>(r)));
}

std::any chips_ast_builder::visitCNOT(ChipsParser::CNOTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  rvalue_variant<expression_env::COLLECTIVE> operand = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr2());
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<not_operator<expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), as_rvalue<dataflow_type::BOOL>(operand)));
}

std::any chips_ast_builder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr2()->accept(this);
}

std::any chips_ast_builder::visitCINT(ChipsParser::CINTContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<direct<dataflow_type::INT, expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), std::stoi(ctx->INT()->getText())));
}

std::any chips_ast_builder::visitCFLOAT(ChipsParser::CFLOATContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), std::stod(ctx->FLOAT()->getText())));
}

std::any chips_ast_builder::visitCBOOL(ChipsParser::CBOOLContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return rvalue_variant<expression_env::COLLECTIVE>(make_node<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>>(
      line_of(ctx), col_of(ctx), ctx->BOOL()->getText() == "true"));
}

std::any chips_ast_builder::visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims =
      std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(ctx->c_suffixes()->accept(this));
  if (auto type = infer_type(ctx))
  {
    switch (*type)
    {
    case dataflow_type::INT:
      return build_var<dataflow_type::INT, expression_env::COLLECTIVE>(*this, ctx, name, dims);
    case dataflow_type::FLOAT:
      return build_var<dataflow_type::FLOAT, expression_env::COLLECTIVE>(*this, ctx, name, dims);
    case dataflow_type::BOOL:
      return build_var<dataflow_type::BOOL, expression_env::COLLECTIVE>(*this, ctx, name, dims);
    }
  }
  throw std::runtime_error("unknown dataflow_type in visitVar");
}

std::any chips_ast_builder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_stopless_expr()->accept(this);
}

std::any chips_ast_builder::visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER

  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims =
      std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(ctx->c_suffixes()->accept(this));
  if (auto t = infer_type(ctx))
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
  throw std::runtime_error("unknown dataflow_type in visitVarContext");
}

std::any chips_ast_builder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_variant<expression_env::COLLECTIVE>> params{};
  for (ChipsParser::C_exprContext *e : ctx->c_expr())
  {
    params.push_back(eval<expression_env::COLLECTIVE>(*this, e));
  }
  if (auto t = infer_type(ctx))
  {
    switch (*t)
    {
    case dataflow_type::INT:
      return build_function<dataflow_type::INT, expression_env::COLLECTIVE>(*this, ctx, name, params);
    case dataflow_type::FLOAT:
      return build_function<dataflow_type::FLOAT, expression_env::COLLECTIVE>(*this, ctx, name, params);
    case dataflow_type::BOOL:
      return build_function<dataflow_type::BOOL, expression_env::COLLECTIVE>(*this, ctx, name, params);
    }
  }
  throw std::runtime_error("unknown dataflow_type in visitFunction");
}

std::any chips_ast_builder::visitCCastAs(ChipsParser::CCastAsContext *ctx)
{
  VERBOSE_VISIT_ENTER
  infer_type(ctx);
  return ctx->c_cast()->accept(this);
}

std::any chips_ast_builder::visitC_cast(ChipsParser::C_castContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type target = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  rvalue_variant<expression_env::COLLECTIVE> operand = eval<expression_env::COLLECTIVE>(*this, ctx->c_stopless_expr());
  switch (target)
  {
  case dataflow_type::INT:
    return build_cast<dataflow_type::INT, expression_env::COLLECTIVE>(*this, ctx, operand);
  case dataflow_type::FLOAT:
    return build_cast<dataflow_type::FLOAT, expression_env::COLLECTIVE>(*this, ctx, operand);
  default:
    break;
  }
  throw std::runtime_error("cast to bool is not allowed");
}

std::any chips_ast_builder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx)
{
  VERBOSE_VISIT_ENTER
  check_suffixes(ctx);
  std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims{};
  for (ChipsParser::C_stopless_exprContext *e : ctx->c_stopless_expr())
  {
    dims.push_back(narrow<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(as_rvalue<dataflow_type::INT>(eval<expression_env::COLLECTIVE>(*this, e))));
  }
  return dims;
}

std::any chips_ast_builder::visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::optional<dataflow_type> type = infer_type(ctx);
  std::string accumulator = ctx->IDENTIFIER(1)->getText();
  auto *channel = lookup_channel(m_support_name, ctx->IDENTIFIER(0)->getText());
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));

  if (type.has_value())
  {
    switch (*type)
    {
    case dataflow_type::INT:
      return build_channeled_accu<dataflow_type::INT>(*this, ctx, channel, accumulator, dims);
    case dataflow_type::FLOAT:
      return build_channeled_accu<dataflow_type::FLOAT>(*this, ctx, channel, accumulator, dims);
    case dataflow_type::BOOL:
      return build_channeled_accu<dataflow_type::BOOL>(*this, ctx, channel, accumulator, dims);
    }
  }
  throw std::runtime_error("unknown dataflow_type in visitChanneledAccuExpression");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

std::any chips_ast_builder::visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  if (is_block(name))
  {
    return system_iterable_variant(make_block_expression(
        *this, ctx, name, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>{}));
  }
  return by_type(lookup_variable(name, ctx), [&](auto t) {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_system_iterable_variable<dft>(*this, ctx, name);
  });
}


std::any chips_ast_builder::visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx)
{
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
  if (params.size() != 1 || !std::holds_alternative<rvalue<dataflow_type::INT, expression_env::SYSTEM> *>(params[0]))
  {
    semantic_fail(ctx, "'" + name + "' takes exactly one int parameter");
  }
  return system_iterable_variant(iterable_variant<expression_env::SYSTEM>(
      make_node<chips::function<dataflow_type::INT, expression_env::SYSTEM>>(
          line_of(ctx), col_of(ctx), name, params)));
}


std::any chips_ast_builder::visitSSuffixableBlockOutputExpression(
    ChipsParser::SSuffixableBlockOutputExpressionContext *ctx)
{
  UNIMPLEMENTED_METHOD;
}

std::any chips_ast_builder::visitBlock(ChipsParser::BlockContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
      ctx->suffixes()->accept(this));
  return make_block_expression(*this, ctx, ctx->IDENTIFIER()->getText(), dims);
}


std::any chips_ast_builder::visitLoop_in(ChipsParser::Loop_inContext *ctx)
{
  return build_iterable<expression_env::PRIMITIVE>(*this, ctx);
}

std::any chips_ast_builder::visitLoop_statement(ChipsParser::Loop_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::DEFINITION;
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type dft = iterator_type(ctx->loop_in());
  auto iterable = std::any_cast<iterable_variant<expression_env::PRIMITIVE>>(ctx->loop_in()->accept(this));
  switch (dft)
  {
  case dataflow_type::INT:
    return build_foreach<env, dataflow_type::INT>(*this, ctx, name, iterable, ctx->statement());
  case dataflow_type::FLOAT:
    return build_foreach<env, dataflow_type::FLOAT>(*this, ctx, name, iterable, ctx->statement());
  case dataflow_type::BOOL:
    return build_foreach<env, dataflow_type::BOOL>(*this, ctx, name, iterable, ctx->statement());
  }
  throw std::runtime_error("unknown dataflow_type in visitLoop_statement");
}

std::any chips_ast_builder::visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::COLLECTIVE;
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type dft = iterator_type(ctx->c_loop_in());
  std::cout<<"plop!"<<std::endl;
  auto iterable = build_iterable<expression_env::COLLECTIVE>(*this, ctx->c_loop_in());
  std::cout<<"plop!"<<std::endl;
  switch (dft)
  {
  case dataflow_type::INT:
    return build_foreach<env, dataflow_type::INT>(*this, ctx, name, iterable, ctx->c_statement());
  case dataflow_type::FLOAT:
    return build_foreach<env, dataflow_type::FLOAT>(*this, ctx, name, iterable, ctx->c_statement());
  case dataflow_type::BOOL:
    return build_foreach<env, dataflow_type::BOOL>(*this, ctx, name, iterable, ctx->c_statement());
  }
  throw std::runtime_error("unknown dataflow_type in visitC_loop_statement");
}

std::any chips_ast_builder::visitC_loop_in(ChipsParser::C_loop_inContext *ctx)
{
  return build_iterable<expression_env::COLLECTIVE>(*this, ctx);
}

std::any chips_ast_builder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  auto iterable = std::any_cast<system_iterable_variant>(ctx->s_suffixable_expr()->accept(this));

  if (auto *block = std::get_if<block_expression_variant>(&iterable))
  {
    return std::visit([&](auto *expression) { return build_block_foreach(*this, ctx, name, expression); }, *block);
  }

  auto dataflow = std::get<iterable_variant<expression_env::SYSTEM>>(iterable);
  return by_type(iterable_type<expression_env::SYSTEM>(dataflow), [&](auto t) {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_foreach<statement_env::SYSTEM, dft>(*this, ctx, name, dataflow, ctx->s_statement());
  });
}

std::any chips_ast_builder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return build_if_else<statement_env::DEFINITION>(*this, ctx, ctx->if_statement(), ctx->statement());
}

std::any chips_ast_builder::visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  constexpr statement_env env = statement_env::SYSTEM;
  return build_if_else<env>(*this, ctx, ctx->s_if_statement(), ctx->s_statement());
}

std::any chips_ast_builder::visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return build_if_else<statement_env::COLLECTIVE>(*this, ctx, ctx->c_if_statement(), ctx->c_statement());
}

std::any chips_ast_builder::visitIf_statement(ChipsParser::If_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return as_statement<statement_env::DEFINITION, recurring_statement::IF>(build_if<statement_env::DEFINITION>(*this, ctx, ctx->expr(), ctx->statement()));
}

std::any chips_ast_builder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return as_statement<statement_env::SYSTEM, recurring_statement::IF>(build_if<statement_env::SYSTEM>(*this, ctx, ctx->expr(), ctx->s_statement()));
}

std::any chips_ast_builder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return as_statement<statement_env::COLLECTIVE, recurring_statement::IF>(build_if<statement_env::COLLECTIVE>(*this, ctx, ctx->c_expr(), ctx->c_statement()));
}

template <dataflow_type dft>
primitive_statement_variant build_primitive_declaration(
    chips_ast_builder &builder,
    ChipsParser::StatementDeclarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> &dims)
{
  using decl_t = dataflow_declaration<dft, statement_env::DEFINITION>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  dataflow_primitive_variable<dft> variable(line, column, ctx->IDENTIFIER()->getText(), dims);
  decl_t *decl = builder.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);

  builder.declare_variable<dft>(ctx->IDENTIFIER()->getText());

  return primitive_statement_variant(static_cast<primitive_statement<recurring_statement::DECLARATION> *>(decl));
}

std::any chips_ast_builder::visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
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

template <dataflow_type dft, expression_env expenv, statement_env sttenv>
std::any build_variable_assignment(chips_ast_builder &builder,
                                   ChipsParser::StatementAssignmentContext *ctx,
                                   const std::vector<int_rvalue_expression_variant<expenv>> &dims,
                                   const rvalue_variant<expression_env::PRIMITIVE> &rhs)
{
  using assign_t = dataflow_assignment<dft, sttenv>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = builder.make_node<contextual_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>{});
  auto *lhs = builder.make_node<variable_expression<dft, expenv>>(line_of(ctx), col_of(ctx), var);
  auto *assign = builder.make_node<assign_t>(line, column, lhs, std::get<rvalue<dft, expenv> *>(rhs));
  return primitive_statement_variant(static_cast<primitive_statement<recurring_statement::ASSIGNMENT> *>(assign));
}

std::any chips_ast_builder::visitStatementAssignment(
    ChipsParser::StatementAssignmentContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::optional<dataflow_type> type = lookup_variable(name, ctx);
  if (!type)
  {
    throw std::runtime_error("undeclared variable '" + name + "' at line " + std::to_string(line_of(ctx)));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  auto rhs = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(ctx->expr()->accept(this));

  switch (*type)
  {
  case dataflow_type::INT:
    return build_variable_assignment<dataflow_type::INT, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  case dataflow_type::FLOAT:
    return build_variable_assignment<dataflow_type::FLOAT, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  case dataflow_type::BOOL:
    return build_variable_assignment<dataflow_type::BOOL, expression_env::PRIMITIVE, statement_env::DEFINITION>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error("unknown dataflow_type in visitStatementContextualAssignment");
}

template <dataflow_type dft>
primitive_statement_variant build_contextual_assignment(
    chips_ast_builder &builder,
    ChipsParser::StatementContextualAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> &dims,
    const rvalue_variant<expression_env::PRIMITIVE> &rhs)
{
  using assign_t = dataflow_assignment<dft, statement_env::DEFINITION>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = builder.make_node<contextual_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>{});
  auto *lhs = builder.make_node<variable_contextual_expression<dft, expression_env::PRIMITIVE>>(line_of(ctx), col_of(ctx), var);
  auto *assign = builder.make_node<assign_t>(line, column, lhs, std::get<rvalue<dft, expression_env::PRIMITIVE> *>(rhs));
  return primitive_statement_variant(static_cast<primitive_statement<recurring_statement::ASSIGNMENT> *>(assign));
}

std::any chips_ast_builder::visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::optional<dataflow_type> type = lookup_contextual("ctx." + name);
  if (!type)
  {
    throw std::runtime_error("undeclared contextual variable '" + name + "' at line " + std::to_string(line_of(ctx)));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
      ctx->suffixes()->accept(this));
  auto rhs = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(ctx->expr()->accept(this));

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
  VERBOSE_VISIT_ENTER
  return ctx->loop_statement()->accept(this);
}

std::any
chips_ast_builder::visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->if_else_statement()->accept(this);
}

std::any chips_ast_builder::visitStatementIf(ChipsParser::StatementIfContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->if_statement()->accept(this);
}

std::any chips_ast_builder::visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string definition = ctx->IDENTIFIER(0)->getText();
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
      ctx->suffixes()->accept(this));

  if (auto *logical = lookup_logical(definition))
    return build_block_declaration<block_type::LOGICAL>(*this, ctx, logical, dims);
  if (auto *physical = lookup_physical(definition))
    return build_block_declaration<block_type::PHYSICAL>(*this, ctx, physical, dims);
  if (auto *object = lookup_object(definition))
    return build_block_declaration<block_type::OBJECT>(*this, ctx, object, dims);
  semantic_fail(ctx, "definition '" + definition + "' is not defined");
}


std::any chips_ast_builder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string target = ctx->IDENTIFIER()->getText();
  auto block = std::any_cast<block_expression_variant>(ctx->block()->accept(this));
  std::string definition = lookup_block(ctx->block()->IDENTIFIER()->getText(), ctx->block()).second;
  auto source = std::any_cast<s_expr_variant>(ctx->s_expr()->accept(this));

  if (auto *channel = lookup_channel(definition, target))
  {
    auto *fed = std::get_if<channel_feeder *>(&source);
    if (fed == nullptr)
    {
      semantic_fail(ctx->s_expr(), "channel '" + target + "' must be plugged to a channel");
    }
    if (channel->get_variable() != (*fed)->get_feeding_channel()->get_variable())
    {
      semantic_fail(ctx->s_expr(), "incompatible channel types: '" + channel->get_variable() + "' and '" +
                                       (*fed)->get_feeding_channel()->get_variable() + "'");
    }
    auto *eating = make_node<channel_eater>(line, column, node_of(block), channel);
    auto *plugging = make_node<channel_plugging>(line, column, eating, *fed);
    return system_statement_variant(static_cast<system_statement<recurring_statement::PLUGGING> *>(plugging));
  }

  std::optional<dataflow_type> type = lookup_parameter(definition, target);
  if (!type.has_value())
  {
    semantic_fail(ctx, "'" + target + "' is neither a parameter nor a channel of '" + definition + "'");
  }
  auto *dataflow = std::get_if<feeder_variant>(&source);
  if (dataflow == nullptr)
  {
    semantic_fail(ctx->s_expr(), "parameter '" + target + "' must be fed by a dataflow");
  }
  functional_block_variant eating = functional_of(ctx, block);

  if (lookup_sensor(definition, target).has_value())
  {
    auto *physical = lookup_physical(definition);
    return by_type(*type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return feed_parameter<dataflow_kind::PHYSICAL, dft>(*this, ctx, eating, physical->m_sensors, *dataflow);
    });
  }
  auto *function = lookup_function(definition);
  return by_type(*type, [&](auto t) {
    constexpr dataflow_type dft = decltype(t)::value;
    return feed_parameter<dataflow_kind::LOGICAL, dft>(*this, ctx, eating, function->get_parameters(), *dataflow);
  });
}


std::any chips_ast_builder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  using system_dims_t = std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>;
  auto linked = make_block_expression(*this, ctx, ctx->IDENTIFIER(0)->getText(),
                                      std::any_cast<system_dims_t>(ctx->suffixes(0)->accept(this)));
  auto supporting = make_block_expression(*this, ctx, ctx->IDENTIFIER(1)->getText(),
                                          std::any_cast<system_dims_t>(ctx->suffixes(1)->accept(this)));

  linkable *linked_component = std::visit([](auto *e) -> linkable * { return e; }, linked);
  support *support_node = nullptr;
  if (auto *p = std::get_if<system_variable_block_expression<block_type::PHYSICAL> *>(&supporting))
    support_node = *p;
  else if (auto *o = std::get_if<system_variable_block_expression<block_type::OBJECT> *>(&supporting))
    support_node = *o;
  else
    semantic_fail(ctx, "a logical block cannot support another component");

  auto *node = make_node<linking_statement>(line_of(ctx), col_of(ctx), linked_component, support_node);
  return system_statement_variant(static_cast<system_statement<recurring_statement::LINKING> *>(node));
}


std::any chips_ast_builder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->s_loop_statement()->accept(this);
}

std::any chips_ast_builder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->s_if_else_statement()->accept(this);
}

std::any chips_ast_builder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->s_if_statement()->accept(this);
}

std::any chips_ast_builder::visitRegularStatement(ChipsParser::RegularStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  ChipsParser::StatementContext *statement = ctx->statement();

  if (auto *decl = dynamic_cast<ChipsParser::StatementDeclarationContext *>(statement))
  {
    dataflow_type type = std::any_cast<dataflow_type>(decl->df_type()->accept(this));
    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
        decl->suffixes()->accept(this));
    return by_type(type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_system_declaration<dft>(*this, decl, dims);
    });
  }

  if (auto *assign = dynamic_cast<ChipsParser::StatementAssignmentContext *>(statement))
  {
    std::string name = assign->IDENTIFIER()->getText();
    dataflow_type type = lookup_variable(name, assign);
    dataflow_type rhs_type = infer_type(assign->expr());
    if (rhs_type != type)
    {
      type_fail(assign->expr(), "cannot assign " + type_name(rhs_type) + " to '" + name + "' of type " + type_name(type));
    }
    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(
        assign->suffixes()->accept(this));
    auto rhs = eval<expression_env::SYSTEM>(*this, assign->expr());
    return by_type(type, [&](auto t) {
      constexpr dataflow_type dft = decltype(t)::value;
      return build_system_assignment<dft>(*this, assign, dims, rhs);
    });
  }

  semantic_fail(statement, "this statement is not allowed in the system section");
}


std::any chips_ast_builder::visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return resolve_block_output(*this, ctx, ctx->block(), ctx->IDENTIFIER()->getText());
}


std::any chips_ast_builder::visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto *collective = std::any_cast<collective_function_definition *>(ctx->collective_operation()->accept(this));
  s_expr_variant inner = resolve_block_output(*this, ctx, ctx->block(), ctx->IDENTIFIER()->getText());
  auto *dataflow = std::get_if<feeder_variant>(&inner);
  if (dataflow == nullptr)
  {
    semantic_fail(ctx, "a collective operation cannot be applied to a channel");
  }
  return s_expr_variant(std::visit(
      [&](auto *source) { return build_collective_cast(*this, ctx, collective, source); }, *dataflow));
}


std::any chips_ast_builder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx)
{
  VERBOSE_VISIT_ENTER
  auto value = eval<expression_env::SYSTEM>(*this, ctx->expr());
  return s_expr_variant(std::visit([](auto *v) { return as_feeder(v); }, value));
}


void chips_ast_builder::declare_collective(const std::string &name, collective_function_definition *function)
{
  if (m_collectives.find(name) != m_collectives.end())
  {
    throw std::runtime_error("duplicate collective function definition '" + name + "'");
  }
  m_collectives[name] = function;
}

collective_function_definition *chips_ast_builder::lookup_collective(const std::string &name, antlr4::ParserRuleContext *ctx) const
{
  auto it = m_collectives.find(name);
  if (it == m_collectives.end())
  {
    semantic_fail(ctx, "collective function '" + name + "' is not defined");
  }
  return it->second;
}

std::any chips_ast_builder::visitCollective_operation(ChipsParser::Collective_operationContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return lookup_collective(ctx->IDENTIFIER()->getText(), ctx);
}

template <dataflow_type dft>
collective_statement_variant build_collective_declaration(
    chips_ast_builder &b, ChipsParser::Cdf_full_declarationContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims)
{
  using decl_t = dataflow_declaration<dft, statement_env::COLLECTIVE>;
  int line = line_of(ctx);
  int column = col_of(ctx);
  std::string name = ctx->IDENTIFIER()->getText();

  dataflow_collective_variable<dft> variable(line, column, name, dims);
  decl_t *decl = b.make_node<decl_t>(line, column, variable);
  decl->m_variable.set_declaration(decl);
  b.declare_variable<dft>(name);
  return collective_statement_variant(static_cast<collective_statement<recurring_statement::DECLARATION> *>(decl));
}

std::any chips_ast_builder::visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->cdf_full_declaration()->accept(this);
}

std::any chips_ast_builder::visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx)
{
  VERBOSE_VISIT_ENTER
  dataflow_type type = std::any_cast<dataflow_type>(ctx->df_type()->accept(this));
  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  return by_type(type, [&](auto t) {
    constexpr dataflow_type dft = decltype(t)::value;
    return build_collective_declaration<dft>(*this, ctx, dims);
  });
}



template <dataflow_type dft>
collective_statement_variant build_collective_assignment(
    chips_ast_builder &b, ChipsParser::CollectiveAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims,
    const rvalue_collective_variant &rhs)
{
  using assign_t = dataflow_assignment<dft, statement_env::COLLECTIVE>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = b.make_node<dataflow_collective_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>{});
  auto *lhs = b.make_node<variable_expression<dft, expression_env::COLLECTIVE>>(line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, std::get<rvalue<dft, expression_env::COLLECTIVE> *>(rhs));
  return collective_statement_variant(static_cast<collective_statement<recurring_statement::ASSIGNMENT> *>(assign));
}

std::any chips_ast_builder::visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  dataflow_type type = lookup_variable(name, ctx);
  std::optional<dataflow_type> rhs_type = infer_type(ctx->c_expr());
  if (rhs_type.has_value() && *rhs_type != type)
  {
    type_fail(ctx->c_expr(), "cannot assign " + type_name(*rhs_type) + " to '" + name + "' of type " + type_name(type));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  auto rhs = eval<expression_env::COLLECTIVE>(*this, ctx->c_expr());

  switch (type)
  {
  case dataflow_type::INT:
    return build_collective_assignment<dataflow_type::INT>(*this, ctx, dims, rhs);
  case dataflow_type::FLOAT:
    return build_collective_assignment<dataflow_type::FLOAT>(*this, ctx, dims, rhs);
  case dataflow_type::BOOL:
    return build_collective_assignment<dataflow_type::BOOL>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error("unknown dataflow_type in visitCollectiveAssignment");
}

template <dataflow_type dft>
collective_statement_variant build_collective_contextual_assignment(
    chips_ast_builder &b, ChipsParser::ContextualAssignmentContext *ctx,
    const std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> &dims,
    const rvalue_collective_variant &rhs)
{
  using assign_t = dataflow_assignment<dft, statement_env::COLLECTIVE>;
  int line = line_of(ctx);
  int column = col_of(ctx);

  auto *var = b.make_node<contextual_variable<dft>>(
      line, column, ctx->IDENTIFIER()->getText(),
      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>{});
  auto *lhs = b.make_node<variable_contextual_expression<dft, expression_env::COLLECTIVE>>(line, column, var, dims);
  auto *assign = b.make_node<assign_t>(line, column, lhs, std::get<rvalue<dft, expression_env::COLLECTIVE> *>(rhs));
  return collective_statement_variant(static_cast<collective_statement<recurring_statement::ASSIGNMENT> *>(assign));
}

std::any chips_ast_builder::visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx)
{
  VERBOSE_VISIT_ENTER
  std::string name = ctx->IDENTIFIER()->getText();
  std::optional<dataflow_type> type = lookup_contextual("ctx." + name);
  if (!type.has_value())
  {
    semantic_fail(ctx, "undeclared contextual variable '" + name + "'");
  }
  std::optional<dataflow_type> rhs_type = infer_type(ctx->c_expr());
  if (rhs_type.has_value() && *rhs_type != *type)
  {
    type_fail(ctx->c_expr(), "cannot assign " + type_name(*rhs_type) + " to 'ctx." + name + "' of type " + type_name(*type));
  }

  auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(
      ctx->c_suffixes()->accept(this));
  auto rhs = eval<expression_env::COLLECTIVE>(*this, ctx->c_expr());

  switch (*type)
  {
  case dataflow_type::INT:
    return build_collective_contextual_assignment<dataflow_type::INT>(*this, ctx, dims, rhs);
  case dataflow_type::FLOAT:
    return build_collective_contextual_assignment<dataflow_type::FLOAT>(*this, ctx, dims, rhs);
  case dataflow_type::BOOL:
    return build_collective_contextual_assignment<dataflow_type::BOOL>(*this, ctx, dims, rhs);
  }
  throw std::runtime_error("unknown dataflow_type in visitContextualAssignment");
}

std::any chips_ast_builder::visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_loop_statement()->accept(this);
}

std::any chips_ast_builder::visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_if_else_statement()->accept(this);
}

std::any chips_ast_builder::visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->c_if_statement()->accept(this);
}

template <dataflow_type dft, dataflow_kind dfk, typename Ctx>
std::any interpret_output(Ctx *ctx, chips_ast_builder *self)
{
  std::string name = ctx->IDENTIFIER()->getText();
  std::vector<rvalue_variant<expression_env::PRIMITIVE>> expressions{};
  for (ChipsParser::ExprContext *e : ctx->expr())
  {
    dataflow_type t = self->infer_type(e);
    if (t != dft)
    {
      self->type_fail(e, "output '" + name + "' mixes " + type_name(dft) + " and " + type_name(t) + " expressions");
    }
    expressions.push_back(std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(e->accept(self)));
  }

  auto *output = self->make_node<function_output<dfk, dft>>(line_of(ctx), col_of(ctx), name, expressions);
  if constexpr (dfk == dataflow_kind::PHYSICAL)
  {
    self->declare_actuator(self->current_definition(), name, dft);
    return physical_output_variant(output);
  }
  else
  {
    self->declare_output(self->current_definition(), name, dft);
    return function_output_variant(output);
  }
}

template <dataflow_kind dfk, typename Ctx>
std::any dispatch_output(Ctx *ctx, chips_ast_builder *self)
{
  switch (self->infer_type(ctx->expr(0)))
  {
  case dataflow_type::INT:
    return interpret_output<dataflow_type::INT, dfk>(ctx, self);
  case dataflow_type::FLOAT:
    return interpret_output<dataflow_type::FLOAT, dfk>(ctx, self);
  case dataflow_type::BOOL:
    return interpret_output<dataflow_type::BOOL, dfk>(ctx, self);
  }
  throw std::runtime_error("unknown dataflow_type in dispatch_output");
}

std::any chips_ast_builder::visitNamed_output(ChipsParser::Named_outputContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return dispatch_output<dataflow_kind::LOGICAL>(ctx, this);
}

std::any chips_ast_builder::visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return dispatch_output<dataflow_kind::PHYSICAL>(ctx, this);
}

std::any chips_ast_builder::visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->named_output()->accept(this);
}

std::any chips_ast_builder::visitIntType(ChipsParser::IntTypeContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return dataflow_type::INT;
}

std::any chips_ast_builder::visitFloatType(ChipsParser::FloatTypeContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return dataflow_type::FLOAT;
}

std::any chips_ast_builder::visitBoolType(ChipsParser::BoolTypeContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return dataflow_type::BOOL;
}

std::any chips_ast_builder::visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->df_type()->accept(this);
}

std::any chips_ast_builder::visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx)
{
  VERBOSE_VISIT_ENTER
  return ctx->df_type()->accept(this);
}

std::any
chips_ast_builder::visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx)
{
  VERBOSE_VISIT_ENTER
  ChipsParser::Pdf_parameter_typeContext *ptcontext = ctx->pdf_parameter_type();
  dataflow_type dft;
  std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims{};

  if (ChipsParser::SensorParameterTypeContext *sensorp = dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptcontext); sensorp != nullptr)
  {
    dft = std::any_cast<dataflow_type>(sensorp->df_type()->accept(this));
    if (sensorp->suffixes() != nullptr)
    {
      dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
          sensorp->suffixes()->accept(this));
    }

    switch (dft)
    {
    case dataflow_type::INT:
      return interpret_param<dataflow_type::INT, dataflow_kind::PHYSICAL, expression_env::PRIMITIVE>(ctx, this, dims);
    case dataflow_type::FLOAT:
      return interpret_param<dataflow_type::FLOAT, dataflow_kind::PHYSICAL, expression_env::PRIMITIVE>(ctx, this, dims);
    case dataflow_type::BOOL:
      return interpret_param<dataflow_type::BOOL, dataflow_kind::PHYSICAL, expression_env::PRIMITIVE>(ctx, this, dims);
    }
    throw std::runtime_error("Unknown dataflow type!");
  }

  ChipsParser::FunctionParameterTypeContext *fparamp = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptcontext);
  dft = std::any_cast<dataflow_type>(fparamp->df_type()->accept(this));
  if (fparamp->suffixes() != nullptr)
  {
    dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(
        fparamp->suffixes()->accept(this));
  }

  switch (dft)
  {
  case dataflow_type::INT:
    return interpret_param<dataflow_type::INT, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::FLOAT:
    return interpret_param<dataflow_type::FLOAT, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  case dataflow_type::BOOL:
    return interpret_param<dataflow_type::BOOL, dataflow_kind::LOGICAL, expression_env::PRIMITIVE>(ctx, this, dims);
  }
  throw std::runtime_error("Unknown dataflow type!");
}


#undef UNIMPLEMENTED_METHOD
