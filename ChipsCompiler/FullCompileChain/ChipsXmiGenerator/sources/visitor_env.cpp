#include "visitor_env.hpp"
#include "ast_node_definitions.hpp"
#include "type_utils.hpp"


using namespace chips;



std::optional<dataflow_type> visitor_env::lookup_variable(const std::string &name) const {
  for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
    auto found = it->find(name);
    if (found != it->end())
      return found->second;
  }
  return std::nullopt;
}

void visitor_env::declare_variable_node(const std::string &name, ast_node *node) {
  if (m_node_scopes.empty()) {
    throw std::runtime_error("variable '" + name + "' declared outside of any scope");
  }
  m_node_scopes.back()[name] = node;
}

void visitor_env::declare_contextual(const std::string &var, dataflow_type type, ast_node *node) {
  if (m_contextuals.find(m_current_def_name) == m_contextuals.end()) {
    m_contextual_owners.push_back(m_current_def_name);
  }
  m_contextuals[m_current_def_name][var] = type;
  if (node != nullptr) {
    m_contextual_nodes[m_current_def_name][var] = node;
  }
}

std::string visitor_env::unique_contextual_owner(const std::string &var) const {
  std::vector<std::string> owners;
  for (const std::string &name : m_contextual_owners) {
    if (m_contextuals.at(name).count(var) > 0)
      owners.push_back(name);
  }
  if (owners.size() > 1) {
    std::string list;
    for (std::size_t i = 0; i < owners.size(); ++i)
      list += (i == 0 ? "'" : ", '") + owners[i] + "'";
    throw std::runtime_error("in '" + m_current_def_name + "': contextual variable '" + var +
                             "' is ambiguous, it is declared in nodes " + list);
  }
  return owners.empty() ? std::string() : owners.front();
}

std::optional<dataflow_type> visitor_env::lookup_contextual(const std::string &var) const {
  const std::string &owner =
      m_support_name.empty() ? m_current_def_name : m_support_name;
  auto node = m_contextuals.find(owner);
  if (node != m_contextuals.end()) {
    auto it = node->second.find(var);
    if (it != node->second.end())
      return it->second;
  }
  if (!m_in_logical)
    return std::nullopt;
  std::string unique = unique_contextual_owner(var);
  if (unique.empty())
    return std::nullopt;
  return m_contextuals.at(unique).at(var);
}

void visitor_env::declare_parameter(const std::string &function, const std::string &var,
                       dataflow_type type) {
  auto &params = m_parameters[function];
  if (params.find(var) != params.end()) {
    throw std::runtime_error("duplicate parameter '" + var + "' in function '" +
                             function + "'");
  }
  params[var] = type;
}

std::optional<dataflow_type> visitor_env::lookup_parameter(const std::string &function,
                                              const std::string &var) const {
  auto fn = m_parameters.find(function);
  if (fn == m_parameters.end())
    return std::nullopt;
  auto it = fn->second.find(var);
  if (it == fn->second.end())
    return std::nullopt;
  return it->second;
}

void visitor_env::declare_sensor(const std::string &function, const std::string &sensor,
                    dataflow_type type) {
  auto &sensors = m_sensors[function];
  if (sensors.find(sensor) != sensors.end()) {
    throw std::runtime_error("duplicate sensor '" + sensor + "' in physical '" +
                             function + "'");
  }
  sensors[sensor] = type;
}

std::optional<dataflow_type> visitor_env::lookup_sensor(const std::string &function,
                                           const std::string &sensor) const {
  auto fn = m_sensors.find(function);
  if (fn == m_sensors.end())
    return std::nullopt;
  auto it = fn->second.find(sensor);
  return it == fn->second.end() ? std::nullopt
                                : std::optional<dataflow_type>(it->second);
}


void visitor_env::declare_output(const std::string &function, const std::string &name, dataflow_type type)
{
  auto &outs = m_outputs[function];
  if (outs.find(name) != outs.end())
  {
    throw std::runtime_error("duplicate output '" + name + "' in function '" + function + "'");
  }
  outs[name] = type;
}

std::optional<dataflow_type> visitor_env::lookup_output(const std::string &function, const std::string &name) const
{
  auto fn = m_outputs.find(function);
  if (fn == m_outputs.end())
    return std::nullopt;
  auto it = fn->second.find(name);
  if (it == fn->second.end())
    return std::nullopt;
  return it->second;
}


void visitor_env::declare_actuator(const std::string &function, const std::string &actuator, dataflow_type type)
{
  auto &actuators = m_actuators[function];
  if (actuators.find(actuator) != actuators.end())
  {
    throw std::runtime_error("duplicate actuator '" + actuator + "' in physical '" + function + "'");
  }
  actuators[actuator] = type;
}


std::optional<dataflow_type> visitor_env::lookup_actuator(const std::string &function, const std::string &actuator) const
{
  auto fn = m_actuators.find(function);
  if (fn == m_actuators.end())
    return std::nullopt;
  auto it = fn->second.find(actuator);
  return it == fn->second.end() ? std::nullopt : std::optional<dataflow_type>(it->second);
}



void visitor_env::declare_channel(const std::string &channel, node_element_declaration<node_element::CHANNEL> *decl)
{
  auto &channels = m_channels[m_current_def_name];
  if (channels.find(channel) != channels.end())
  {
    throw std::runtime_error("duplicate channel '" + channel + "' in node '" + m_current_def_name + "'");
  }
  channels[channel] = decl;
}


node_element_declaration<node_element::CHANNEL> *visitor_env::lookup_channel(const std::string &node, const std::string &channel) const
{
  auto n = m_channels.find(node);
  if (n == m_channels.end())
    return nullptr;
  auto it = n->second.find(channel);
  return it == n->second.end() ? nullptr : it->second;
}
std::size_t visitor_env::channel_count(const std::string &node) const
{
  auto n = m_channels.find(node);
  return n == m_channels.end() ? 0 : n->second.size();
}


void visitor_env::declare_collective(const std::string &name, collective_function_definition *function)
{
  if (m_collectives.find(name) != m_collectives.end())
  {
    throw std::runtime_error("duplicate collective function definition '" + name + "'");
  }
  m_collectives[name] = function;
}

collective_function_definition *visitor_env::lookup_collective(const std::string &name, antlr4::ParserRuleContext *ctx) const
{
  auto it = m_collectives.find(name);
  if (it == m_collectives.end())
  {
    semantic_fail(ctx, "collective function '" + name + "' is not defined");
  }
  return it->second;
}


void visitor_env::push_scope()
{
  m_scopes.emplace_back();
  m_node_scopes.emplace_back();
  m_block_scopes.emplace_back();
  m_block_node_scopes.emplace_back();
}

void visitor_env::pop_scope()
{
  m_scopes.pop_back();
  m_node_scopes.pop_back();
  m_block_scopes.pop_back();
  m_block_node_scopes.pop_back();
}

bool visitor_env::definition_exists(const std::string &name) const
{
  return m_logicals.count(name) > 0 || m_physicals.count(name) > 0 || m_objects.count(name) > 0;
}

void visitor_env::declare_definition(const std::string &name, logical_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_logicals[name] = definition;
}

void visitor_env::declare_definition(const std::string &name, physical_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_physicals[name] = definition;
}

void visitor_env::declare_definition(const std::string &name, object_definition *definition)
{
  if (definition_exists(name))
  {
    throw std::runtime_error("duplicate definition '" + name + "'");
  }
  m_objects[name] = definition;
}

logical_definition *visitor_env::lookup_logical(const std::string &name) const
{
  auto it = m_logicals.find(name);
  return it == m_logicals.end() ? nullptr : it->second;
}

physical_definition *visitor_env::lookup_physical(const std::string &name) const
{
  auto it = m_physicals.find(name);
  return it == m_physicals.end() ? nullptr : it->second;
}

object_definition *visitor_env::lookup_object(const std::string &name) const
{
  auto it = m_objects.find(name);
  return it == m_objects.end() ? nullptr : it->second;
}

node_definition *visitor_env::lookup_node(const std::string &name) const
{
  if (auto *object = lookup_object(name))
  {
    return dynamic_cast<node_definition*>(object) ;
  }
  return dynamic_cast<node_definition*>(lookup_physical(name));
}

function_definition *visitor_env::lookup_function(const std::string &name) const
{
  if (auto *logical = lookup_logical(name))
  {
    return dynamic_cast<function_definition*>(logical);
  }
  return dynamic_cast<function_definition*>(lookup_physical(name));
}

void visitor_env::declare_block(const std::string &name, block_type type, const std::string &definition, ast_node *node)
{
  auto &scope = m_block_scopes.back();
  if (scope.find(name) != scope.end())
  {
    throw std::runtime_error("duplicate block '" + name + "'");
  }
  scope[name] = {type, definition};
  if (node != nullptr)
  {
    m_block_node_scopes.back()[name] = node;
  }
}

std::pair<block_type, std::string> visitor_env::lookup_block(const std::string &name, antlr4::ParserRuleContext *ctx) const
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

bool visitor_env::is_block(const std::string &name) const
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