#include "ChipsAstBuilder.hpp"

program_node* ChipsAstBuilder::build(ChipsParser::ProgramContext* ctx) {
        visitProgram(ctx);
        return &m_program;
    }

void ChipsAstBuilder::resetLocalScope() {
        m_locals.clear();
        m_contextuals.clear();
        m_channels.clear();
    }

dataflow_type ChipsAstBuilder::builtinFunctionType(const std::string& name) {
        if (name == "random") return dataflow_type::FLOAT;
        if (name == "is_fresh") return dataflow_type::BOOL;
        return dataflow_type::INT;
    }

dataflow_type ChipsAstBuilder::lookupVarType(const std::string& name) {
        auto it = m_locals.find(name);
        if (it != m_locals.end()) return it->second.dft;
        auto bit = m_blocks.find(name);
        if (bit != m_blocks.end()) return dataflow_type::INT;
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::lookupContextualType(const std::string& name) {
        auto it = m_contextuals.find(name);
        if (it != m_contextuals.end()) return it->second.dft;
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferDfTypeCtx(ChipsParser::Df_typeContext* ctx) {
        if (dynamic_cast<ChipsParser::IntTypeContext*>(ctx)) return dataflow_type::INT;
        if (dynamic_cast<ChipsParser::FloatTypeContext*>(ctx)) return dataflow_type::FLOAT;
        return dataflow_type::BOOL;
    }

dataflow_type ChipsAstBuilder::inferExpr2Type(ChipsParser::Expr2Context* ctx) {
        if (dynamic_cast<ChipsParser::IntLiteralContext*>(ctx)) return dataflow_type::INT;
        if (dynamic_cast<ChipsParser::FloatLiteralContext*>(ctx)) return dataflow_type::FLOAT;
        if (dynamic_cast<ChipsParser::BoolLiteralContext*>(ctx)) return dataflow_type::BOOL;
        if (auto* c = dynamic_cast<ChipsParser::VarContext*>(ctx)) return lookupVarType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::ParensContext*>(ctx)) return inferExprType(c->expr());
        if (auto* c = dynamic_cast<ChipsParser::VarContextContext*>(ctx)) return lookupContextualType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::FunctionContext*>(ctx)) return builtinFunctionType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::CastAsContext*>(ctx)) return inferDfTypeCtx(c->cast()->df_type());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferExpr1Type(ChipsParser::Expr1Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr2Context*>(ctx)) return inferExpr2Type(c->expr2());
        if (auto* c = dynamic_cast<ChipsParser::MULTContext*>(ctx)) return inferExpr2Type(c->expr2());
        if (auto* c = dynamic_cast<ChipsParser::DIVContext*>(ctx)) return inferExpr2Type(c->expr2());
        if (dynamic_cast<ChipsParser::MODContext*>(ctx)) return dataflow_type::INT;
        if (dynamic_cast<ChipsParser::NOTContext*>(ctx)) return dataflow_type::BOOL;
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferExpr01Type(ChipsParser::Expr01Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr1Context*>(ctx)) return inferExpr1Type(c->expr1());
        if (auto* c = dynamic_cast<ChipsParser::NegateContext*>(ctx)) return inferExpr1Type(c->expr1());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferExpr0Type(ChipsParser::Expr0Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr01Context*>(ctx)) return inferExpr01Type(c->expr01());
        if (auto* c = dynamic_cast<ChipsParser::PLUSContext*>(ctx)) return inferExpr01Type(c->expr01());
        if (auto* c = dynamic_cast<ChipsParser::SUBContext*>(ctx)) return inferExpr01Type(c->expr01());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferExprType(ChipsParser::ExprContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr0Context*>(ctx)) return inferExpr0Type(c->expr0());
        return dataflow_type::BOOL;
    }

dataflow_type ChipsAstBuilder::inferCExpr2Type(ChipsParser::C_stopless_expr2Context* ctx) {
        if (dynamic_cast<ChipsParser::CINTContext*>(ctx)) return dataflow_type::INT;
        if (dynamic_cast<ChipsParser::CFLOATContext*>(ctx)) return dataflow_type::FLOAT;
        if (dynamic_cast<ChipsParser::CBOOLContext*>(ctx)) return dataflow_type::BOOL;
        if (dynamic_cast<ChipsParser::INPUTContext*>(ctx)) return m_expectedType;
        if (auto* c = dynamic_cast<ChipsParser::CVariableExpressionContext*>(ctx)) return lookupVarType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::CtxVariableExpressionContext*>(ctx)) return lookupContextualType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::ChanneledAccuExpressionContext*>(ctx)) return lookupVarType(c->IDENTIFIER(1)->getText());
        if (auto* c = dynamic_cast<ChipsParser::FunctionCallContext*>(ctx)) return builtinFunctionType(c->IDENTIFIER()->getText());
        if (auto* c = dynamic_cast<ChipsParser::CParenthesisContext*>(ctx)) return inferCExprType(c->c_stopless_expr());
        if (auto* c = dynamic_cast<ChipsParser::CCastAsContext*>(ctx)) return inferDfTypeCtx(c->c_cast()->df_type());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferCExpr1Type(ChipsParser::C_stopless_expr1Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr2Context*>(ctx)) return inferCExpr2Type(c->c_stopless_expr2());
        if (auto* c = dynamic_cast<ChipsParser::CMULTContext*>(ctx)) return inferCExpr2Type(c->c_stopless_expr2());
        if (auto* c = dynamic_cast<ChipsParser::CDIVContext*>(ctx)) return inferCExpr2Type(c->c_stopless_expr2());
        if (dynamic_cast<ChipsParser::CMODContext*>(ctx)) return dataflow_type::INT;
        if (dynamic_cast<ChipsParser::CNOTContext*>(ctx)) return dataflow_type::BOOL;
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferCExpr01Type(ChipsParser::C_stopless_expr01Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr1Context*>(ctx)) return inferCExpr1Type(c->c_stopless_expr1());
        if (auto* c = dynamic_cast<ChipsParser::CNegateContext*>(ctx)) return inferCExpr1Type(c->c_stopless_expr1());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferCExpr0Type(ChipsParser::C_stopless_expr0Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr01Context*>(ctx)) return inferCExpr01Type(c->c_stopless_expr01());
        if (auto* c = dynamic_cast<ChipsParser::CPLUSContext*>(ctx)) return inferCExpr01Type(c->c_stopless_expr01());
        if (auto* c = dynamic_cast<ChipsParser::CSUBContext*>(ctx)) return inferCExpr01Type(c->c_stopless_expr01());
        return m_expectedType;
    }

dataflow_type ChipsAstBuilder::inferCExprType(ChipsParser::C_stopless_exprContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr0Context*>(ctx)) return inferCExpr0Type(c->c_stopless_expr0());
        return dataflow_type::BOOL;
    }

std::any ChipsAstBuilder::visitProgram(ChipsParser::ProgramContext *ctx) {
        if (ctx->system()) visitSystem(ctx->system());
        for (auto* p : ctx->preamble()) {
            resetLocalScope();
            m_stmtEnv = statement_env::DEFINITION;
            m_exprEnv = expression_env::PRIMITIVE;
            visit(p);
        }
        return {};
    }

std::any ChipsAstBuilder::visitSystem(ChipsParser::SystemContext *ctx) {
        m_stmtEnv = statement_env::SYSTEM;
        m_exprEnv = expression_env::SYSTEM;
        for (auto* s : ctx->s_statement()) {
            m_program.get_system().add_statement(buildSStatement(s));
        }
        return {};
    }

std::any ChipsAstBuilder::visitObject_def(ChipsParser::Object_defContext *ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        with_section with;
        for (auto* ws : ctx->with_section()->with_statement()) {
            auto v = buildWithStatement(ws);
            with.add_statement(v);
        }
        auto* def = new object_definition(name, with);
        m_definitions[name] = def;
        m_program.get_preamble().add_definition(definition_variant{ def });
        return {};
    }

std::any ChipsAstBuilder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) { return visitObject_def(ctx->object_def()); }

std::any ChipsAstBuilder::visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) { return visitChildren(ctx); }

std::any ChipsAstBuilder::visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx) { return visitCollective_op_def(ctx->collective_op_def()); }

std::any ChipsAstBuilder::visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx) { return visitImplementation_def(ctx->implementation_def()); }

std::any ChipsAstBuilder::visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) { return visitL_function_def(ctx->l_function_def()); }

std::any ChipsAstBuilder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) { return visitP_function_def(ctx->p_function_def()); }

std::any ChipsAstBuilder::visitImplementation_def(ChipsParser::Implementation_defContext *ctx) {
        auto* stub = new implementation_defintion();
        stub->m_name = ctx->IDENTIFIER(0)->getText();
        m_definitions[stub->m_name] = stub;
        m_program.get_preamble().add_definition(definition_variant{ stub });
        return {};
    }

std::any ChipsAstBuilder::visitNode_mapping(ChipsParser::Node_mappingContext *ctx) { return {}; }

node_element_declaration<node_element::CHANNEL>* ChipsAstBuilder::buildChannelDeclaration(ChipsParser::ChannelDeclarationContext* ctx) {
        std::string typeId = ctx->IDENTIFIER(0)->getText();
        std::string name = ctx->IDENTIFIER(1)->getText();
        auto* decl = new node_element_declaration<node_element::CHANNEL>(typeId, name);
        m_channels[name] = decl;
        return decl;
    }

node_statement_variant ChipsAstBuilder::buildWithStatement(ChipsParser::With_statementContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::ChannelDeclarationContext*>(ctx)) return node_statement_variant{ buildChannelDeclaration(c) };
        if (auto* c = dynamic_cast<ChipsParser::ContextualDeclarationContext*>(ctx)) {
            dataflow_type dft = inferDfTypeCtx(c->df_type());
            static with_section dummy;
            return dispatchStmtByDft<statement_env::NODE>(dft, [&](auto tag) -> node_statement_variant {
                constexpr dataflow_type DFT = decltype(tag)::value;
                auto* decl = buildContextualDeclTyped<DFT>(c, dummy);
                return node_statement_variant{ decl };
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::WithRegularStatementContext*>(ctx)) {
            m_stmtEnv = statement_env::NODE;
            return buildStatement<statement_env::NODE>(c->statement());
        }
        return node_statement_variant{};
    }

std::any ChipsAstBuilder::visitWith_section(ChipsParser::With_sectionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx) { return {}; }

init_section ChipsAstBuilder::buildInitSection(ChipsParser::Init_sectionContext* ctx) {
        init_section sec;
        m_stmtEnv = statement_env::DEFINITION;
        for (auto* s : ctx->statement()) sec.add_statement(buildStatement<statement_env::DEFINITION>(s));
        return sec;
    }

then_section ChipsAstBuilder::buildThenSection(ChipsParser::Then_sectionContext* ctx) {
        then_section sec;
        m_stmtEnv = statement_env::DEFINITION;
        for (auto* s : ctx->statement()) sec.add_statement(buildStatement<statement_env::DEFINITION>(s));
        return sec;
    }

std::any ChipsAstBuilder::visitInit_section(ChipsParser::Init_sectionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitThen_section(ChipsParser::Then_sectionContext *ctx) { return {}; }

function_parameter_variant ChipsAstBuilder::buildDfParameterDecl(ChipsParser::Df_parameter_declContext* ctx) {
        dataflow_type dft = inferDfTypeCtx(ctx->df_type());
        return dispatchStmtByDft<statement_env::DEFINITION>(dft, [&](auto tag) -> function_parameter_variant {
            constexpr dataflow_type DFT = decltype(tag)::value;
            return function_parameter_variant{ buildLogicalParam<DFT>(ctx) };
        });
    }

void ChipsAstBuilder::buildPdfParameterDecl(ChipsParser::Pdf_parameter_declContext* ctx, std::vector<physical_parameter_variant>& params, std::vector<physical_parameter_variant>& sensors) {
        std::string name = ctx->IDENTIFIER()->getText();
        auto* pt = ctx->pdf_parameter_type();
        if (auto* sc = dynamic_cast<ChipsParser::SensorParameterTypeContext*>(pt)) {
            dataflow_type dft = inferDfTypeCtx(sc->df_type());
            dispatchStmtByDft<statement_env::DEFINITION>(dft, [&](auto tag) -> int {
                constexpr dataflow_type DFT = decltype(tag)::value;
                sensors.push_back(physical_parameter_variant{ buildPhysicalRegularParam<DFT>(name, sc->suffixes(), ctx->expr()) });
                return 0;
            });
            return;
        }
        if (auto* fc = dynamic_cast<ChipsParser::FunctionParameterTypeContext*>(pt)) {
            dataflow_type dft = inferDfTypeCtx(fc->df_type());
            dispatchStmtByDft<statement_env::DEFINITION>(dft, [&](auto tag) -> int {
                constexpr dataflow_type DFT = decltype(tag)::value;
                params.push_back(physical_parameter_variant{ buildPhysicalRegularParam<DFT>(name, fc->suffixes(), ctx->expr()) });
                return 0;
            });
        }
    }

std::any ChipsAstBuilder::visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitIntType(ChipsParser::IntTypeContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFloatType(ChipsParser::FloatTypeContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitBoolType(ChipsParser::BoolTypeContext *ctx) { return {}; }

function_output_variant ChipsAstBuilder::buildNamedOutput(ChipsParser::Named_outputContext* ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        dataflow_type dft = inferExprType(ctx->expr(0));
        std::vector<ChipsParser::ExprContext*> exprs(ctx->expr().begin(), ctx->expr().end());
        return dispatchStmtByDft<statement_env::DEFINITION>(dft, [&](auto tag) -> function_output_variant {
            constexpr dataflow_type DFT = decltype(tag)::value;
            return function_output_variant{ buildLogicalOutputTyped<DFT>(name, exprs) };
        });
    }

std::any ChipsAstBuilder::visitNamed_output(ChipsParser::Named_outputContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitL_function_def(ChipsParser::L_function_defContext *ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        resetLocalScope();
        std::vector<function_parameter_variant> params;
        for (auto* p : ctx->df_parameter_decl()) params.push_back(buildDfParameterDecl(p));
        auto init = buildInitSection(ctx->init_section());
        auto then = buildThenSection(ctx->then_section());
        std::vector<function_output_variant> outputs;
        for (auto* o : ctx->named_output()) outputs.push_back(buildNamedOutput(o));
        auto* def = new logical_definition(name, params, init, then, outputs);
        m_definitions[name] = def;
        m_program.get_preamble().add_definition(definition_variant{ def });
        return {};
    }

std::any ChipsAstBuilder::visitP_function_def(ChipsParser::P_function_defContext *ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        resetLocalScope();
        std::vector<function_parameter_variant> params;
        std::vector<physical_parameter_variant> sensors;
        for (auto* p : ctx->pdf_parameter_decl()) {
            auto* pt = p->pdf_parameter_type();
            if (dynamic_cast<ChipsParser::SensorParameterTypeContext*>(pt)) {
                std::vector<physical_parameter_variant> dummyParams;
                buildPdfParameterDecl(p, dummyParams, sensors);
            } else {
                std::vector<physical_parameter_variant> physParams;
                std::vector<physical_parameter_variant> dummySensors;
                buildPdfParameterDecl(p, physParams, dummySensors);
                for (auto& pv : physParams) {
                    std::visit([&](auto* fp) {
                        using T = std::decay_t<decltype(*fp)>;
                        constexpr dataflow_type DFT = T::declaration_t::declaration_t == dataflow_type::INT ? dataflow_type::INT : dataflow_type::INT;
                        (void)DFT;
                    }, pv);
                    params.push_back(function_parameter_variant{});
                }
            }
        }
        with_section with;
        for (auto* ws : ctx->with_section()->with_statement()) with.add_statement(buildWithStatement(ws));
        auto init = buildInitSection(ctx->init_section());
        auto then = buildThenSection(ctx->then_section());
        std::vector<function_output_variant> outputs;
        std::vector<physical_output_variant> actuators;
        for (auto* o : ctx->p_named_output()) {
            if (auto* ac = dynamic_cast<ChipsParser::ActuatorOutputContext*>(o)) {
                std::string aname = ac->IDENTIFIER()->getText();
                dataflow_type dft = inferExprType(ac->expr(0));
                std::vector<ChipsParser::ExprContext*> exprs(ac->expr().begin(), ac->expr().end());
                dispatchStmtByDft<statement_env::DEFINITION>(dft, [&](auto tag) -> int {
                    constexpr dataflow_type DFT = decltype(tag)::value;
                    actuators.push_back(physical_output_variant{ buildActuatorOutputTyped<DFT>(aname, exprs) });
                    return 0;
                });
            } else if (auto* fo = dynamic_cast<ChipsParser::FunctionOutputContext*>(o)) {
                outputs.push_back(buildNamedOutput(fo->named_output()));
            }
        }
        auto* def = new physical_definition(name, params, init, then, outputs, with, sensors, actuators);
        m_definitions[name] = def;
        m_program.get_preamble().add_definition(definition_variant{ def });
        return {};
    }

std::any ChipsAstBuilder::visitC_signature(ChipsParser::C_signatureContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_keywords(ChipsParser::C_keywordsContext *ctx) { return {}; }

collective_parameter_variant ChipsAstBuilder::buildCdfDefaultedDecl(ChipsParser::Cdf_defaulted_declContext* ctx) {
        dataflow_type dft = inferDfTypeCtx(ctx->df_type());
        return dispatchStmtByDft<statement_env::COLLECTIVE>(dft, [&](auto tag) -> collective_parameter_variant {
            constexpr dataflow_type DFT = decltype(tag)::value;
            return collective_parameter_variant{ buildCollectiveParamTyped<DFT>(ctx->IDENTIFIER()->getText(), ctx->suffixes(), ctx->c_expr()) };
        });
    }

std::any ChipsAstBuilder::visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx) { return {}; }

typename SttEnvToSttVariant<statement_env::COLLECTIVE>::type ChipsAstBuilder::buildCStatement(ChipsParser::C_statementContext* ctx) {
        m_stmtEnv = statement_env::COLLECTIVE;
        if (auto* c = dynamic_cast<ChipsParser::CollectiveVariableDeclarationContext*>(ctx)) return buildCollectiveDeclStatement<statement_env::COLLECTIVE>(c->cdf_full_declaration());
        if (auto* c = dynamic_cast<ChipsParser::CollectiveAssignmentContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_locals.find(name);
            dataflow_type dft = it != m_locals.end() ? it->second.dft : dataflow_type::INT;
            return dispatchStmtByDft<statement_env::COLLECTIVE>(dft, [&](auto tag) -> collective_statement_variant {
                constexpr dataflow_type DFT = decltype(tag)::value;
                m_expectedType = DFT;
                auto idx = buildSuffixIndices<expression_env::COLLECTIVE>(c->c_suffixes());
                auto* typedVar = reinterpret_cast<dataflow_collective_variable<DFT>*>(it != m_locals.end() ? it->second.ptr : nullptr);
                auto* lv = new variable_expression<DFT,expression_env::COLLECTIVE>(typedVar, idx);
                auto rhs = buildCExpr<expression_env::COLLECTIVE>(c->c_expr());
                auto* asg = new dataflow_assignment<DFT,statement_env::COLLECTIVE>(lv, asType<DFT>(rhs));
                return collective_statement_variant{ static_cast<statement<statement_env::COLLECTIVE,recurring_statement::ASSIGNMENT>*>(asg) };
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::ContextualAssignmentContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_contextuals.find(name);
            dataflow_type dft = it != m_contextuals.end() ? it->second.dft : dataflow_type::INT;
            return dispatchStmtByDft<statement_env::COLLECTIVE>(dft, [&](auto tag) -> collective_statement_variant {
                constexpr dataflow_type DFT = decltype(tag)::value;
                m_expectedType = DFT;
                auto idx = buildSuffixIndices<expression_env::COLLECTIVE>(c->c_suffixes());
                auto* typedVar = reinterpret_cast<contextual_variable<DFT>*>(it != m_contextuals.end() ? it->second.ptr : nullptr);
                auto* lv = new variable_contextual_expression<DFT,expression_env::COLLECTIVE>(typedVar, idx);
                auto rhs = buildCExpr<expression_env::COLLECTIVE>(c->c_expr());
                auto* asg = new dataflow_assignment<DFT,statement_env::COLLECTIVE>(lv, asType<DFT>(rhs));
                return collective_statement_variant{ static_cast<statement<statement_env::COLLECTIVE,recurring_statement::ASSIGNMENT>*>(asg) };
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::CollectiveIfStatementContext*>(ctx)) return buildCIfStatement(c->c_if_statement());
        if (auto* c = dynamic_cast<ChipsParser::CollectiveIfElseStatementContext*>(ctx)) return buildCIfElseStatement(c->c_if_else_statement());
        if (auto* c = dynamic_cast<ChipsParser::CollectiveLoopStatementContext*>(ctx)) return buildCLoopStatement(c->c_loop_statement());
        return collective_statement_variant{};
    }

collective_statement_variant ChipsAstBuilder::buildCIfStatement(ChipsParser::C_if_statementContext* ctx) {
        auto* node = new if_statement<statement_env::COLLECTIVE>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildCExpr<expression_env::COLLECTIVE>(ctx->c_expr()));
        for (auto* s : ctx->c_statement()) node->get_if_section().add_statement(buildCStatement(s));
        return collective_statement_variant{ static_cast<statement<statement_env::COLLECTIVE,recurring_statement::IF>*>(node) };
    }

collective_statement_variant ChipsAstBuilder::buildCIfElseStatement(ChipsParser::C_if_else_statementContext* ctx) {
        auto* node = new if_else_statement<statement_env::COLLECTIVE>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildCExpr<expression_env::COLLECTIVE>(ctx->c_if_statement()->c_expr()));
        for (auto* s : ctx->c_if_statement()->c_statement()) node->get_if_section().add_statement(buildCStatement(s));
        for (auto* s : ctx->c_statement()) node->get_else_section().add_statement(buildCStatement(s));
        return collective_statement_variant{ static_cast<statement<statement_env::COLLECTIVE,recurring_statement::IF>*>(node) };
    }

collective_statement_variant ChipsAstBuilder::buildCLoopStatement(ChipsParser::C_loop_statementContext* ctx) {
        std::string iterName = ctx->IDENTIFIER()->getText();
        auto* iterDecl = declareVar<dataflow_type::INT,statement_env::COLLECTIVE>(iterName);
        m_locals[iterName] = VarSymbol{ dataflow_type::INT, &iterDecl->m_variable };
        auto* node = new foreach_statement<statement_env::COLLECTIVE,dataflow_type::INT>();
        node->get_iterator() = *iterDecl;
        std::string fname = ctx->loop_in()->IDENTIFIER()->getText();
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> params;
        for (auto* e : ctx->loop_in()->expr()) params.push_back(buildExpr<expression_env::COLLECTIVE>(e));
        auto* fn = new function<dataflow_type::INT,expression_env::COLLECTIVE>(fname, params);
        node->get_iterable() = fn;
        for (auto* s : ctx->c_statement()) node->add_statement(buildCStatement(s));
        return collective_statement_variant{ static_cast<statement<statement_env::COLLECTIVE,recurring_statement::FOREACH>*>(node) };
    }

std::any ChipsAstBuilder::visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) {
        resetLocalScope();
        auto* sig = ctx->c_signature();
        collective_function_type type = dynamic_cast<ChipsParser::C_signatureContext*>(sig)->c_keywords()->getText().find("spread") != std::string::npos
            ? collective_function_type::SPREAD : collective_function_type::COLLECT;

        std::vector<collective_parameter_variant> accuParams;
        for (auto* p : sig->cdf_defaulted_decl()) accuParams.push_back(buildCdfDefaultedDecl(p));
        accumulator_definition accu(accuParams);

        std::string name = sig->IDENTIFIER(0)->getText();
        std::string supportName = sig->IDENTIFIER(1)->getText();
        node_definition* support = nullptr;
        auto dit = m_definitions.find(supportName);
        if (dit != m_definitions.end()) support = dit->second->get_node_definition();

        collectiveops_section ops;
        m_stmtEnv = statement_env::COLLECTIVE;
        for (auto* s : ctx->c_statement()) ops.add_statement(buildCStatement(s));

        std::vector<rvalue_variant<expression_env::COLLECTIVE>> targetExprs;
        for (auto* e : ctx->c_expr()) targetExprs.push_back(buildCExpr<expression_env::COLLECTIVE>(e));
        target_output target(targetExprs);

        default_output* defOut = nullptr;
        std::vector<channeled_output> channeledOuts;
        for (auto* o : ctx->c_output()) {
            if (auto* d = dynamic_cast<ChipsParser::DefaultOutputContext*>(o)) {
                std::vector<rvalue_variant<expression_env::COLLECTIVE>> exprs;
                for (auto* e : d->c_expr()) exprs.push_back(buildCExpr<expression_env::COLLECTIVE>(e));
                defOut = new default_output(exprs);
            } else if (auto* ch = dynamic_cast<ChipsParser::ChanneledOutputContext*>(o)) {
                std::string chanName = ch->IDENTIFIER()->getText();
                auto cit = m_channels.find(chanName);
                std::vector<rvalue_variant<expression_env::COLLECTIVE>> exprs;
                for (auto* e : ch->c_expr()) exprs.push_back(buildCExpr<expression_env::COLLECTIVE>(e));
                channeled_output co(cit != m_channels.end() ? cit->second : nullptr, exprs);
                channeledOuts.push_back(co);
            }
        }

        auto* def = new collective_function_definition(name, type, accu, support, ops, target, defOut ? *defOut : default_output({}), channeledOuts);
        m_collectiveDefs[name] = def;
        m_definitions[name] = def;
        m_program.get_preamble().add_definition(definition_variant{ def });
        return {};
    }

std::any ChipsAstBuilder::visitLT(ChipsParser::LTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitGT(ChipsParser::GTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitLEQ(ChipsParser::LEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitGEQ(ChipsParser::GEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitNEQ(ChipsParser::NEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitEQ(ChipsParser::EQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitAND(ChipsParser::ANDContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitOR(ChipsParser::ORContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx) { return {}; }

std::any ChipsAstBuilder::visitPLUS(ChipsParser::PLUSContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSUB(ChipsParser::SUBContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitPassExpr01(ChipsParser::PassExpr01Context *ctx) { return {}; }

std::any ChipsAstBuilder::visitNegate(ChipsParser::NegateContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx) { return {}; }

std::any ChipsAstBuilder::visitMULT(ChipsParser::MULTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitDIV(ChipsParser::DIVContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitMOD(ChipsParser::MODContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitNOT(ChipsParser::NOTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx) { return {}; }

std::any ChipsAstBuilder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitVar(ChipsParser::VarContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitParens(ChipsParser::ParensContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitVarContext(ChipsParser::VarContextContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFunction(ChipsParser::FunctionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCastAs(ChipsParser::CastAsContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCast(ChipsParser::CastContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStop(ChipsParser::StopContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCLT(ChipsParser::CLTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCGT(ChipsParser::CGTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCLEQ(ChipsParser::CLEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCGEQ(ChipsParser::CGEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCNEQ(ChipsParser::CNEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCEQ(ChipsParser::CEQContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCAND(ChipsParser::CANDContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCINT(ChipsParser::CINTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCFLOAT(ChipsParser::CFLOATContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCBOOL(ChipsParser::CBOOLContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitINPUT(ChipsParser::INPUTContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCCastAs(ChipsParser::CCastAsContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_cast(ChipsParser::C_castContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSuffixes(ChipsParser::SuffixesContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitLoop_in(ChipsParser::Loop_inContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitLoop_statement(ChipsParser::Loop_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitIf_statement(ChipsParser::If_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementLoop(ChipsParser::StatementLoopContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitStatementIf(ChipsParser::StatementIfContext *ctx) { return {}; }

block_type ChipsAstBuilder::blockTypeOfDefinition(const std::string& typeName) {
        auto it = m_definitions.find(typeName);
        if (it == m_definitions.end()) return block_type::OBJECT;
        if (dynamic_cast<physical_definition*>(it->second)) return block_type::PHYSICAL;
        if (dynamic_cast<logical_definition*>(it->second)) return block_type::LOGICAL;
        return block_type::OBJECT;
    }

system_statement_variant ChipsAstBuilder::buildObjectDeclaration(ChipsParser::ObjectDeclarationContext* ctx) {
        std::string typeName = ctx->IDENTIFIER(0)->getText();
        std::string varName = ctx->IDENTIFIER(1)->getText();
        block_type bt = blockTypeOfDefinition(typeName);
        if (bt == block_type::PHYSICAL) return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::DECLARATION>*>(buildBlockDeclTyped<block_type::PHYSICAL>(typeName, varName)) };
        if (bt == block_type::LOGICAL) return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::DECLARATION>*>(buildBlockDeclTyped<block_type::LOGICAL>(typeName, varName)) };
        return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::DECLARATION>*>(buildBlockDeclTyped<block_type::OBJECT>(typeName, varName)) };
    }

std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> ChipsAstBuilder::buildBlockIndices(ChipsParser::SuffixesContext* suf) {
        return buildSuffixIndices<expression_env::SYSTEM>(suf);
    }

system_statement_variant ChipsAstBuilder::buildFeedingStatement(ChipsParser::FeedingStatementContext* ctx) {
        std::string blockName = ctx->block()->IDENTIFIER()->getText();
        std::string paramName = ctx->IDENTIFIER()->getText();
        auto bit = m_blocks.find(blockName);
        block_type bt = bit != m_blocks.end() ? bit->second.bt : block_type::OBJECT;
        auto idx = buildBlockIndices(ctx->block()->suffixes());

        if (bt == block_type::LOGICAL) {
            auto* def = bit != m_blocks.end() ? static_cast<logical_definition*>(bit->second.def) : nullptr;
            dataflow_type dft = dataflow_type::INT;
            for (auto& pv : def ? def->get_parameters() : std::vector<function_parameter_variant>{}) {
                std::visit([&](auto* p) { if (p->get_name() == paramName) dft = dataflow_type::INT; }, pv);
            }
            return dispatchStmtByDft<statement_env::SYSTEM>(dft, [&](auto tag) -> system_statement_variant {
                constexpr dataflow_type DFT = decltype(tag)::value;
                function_parameter<dataflow_kind::LOGICAL,DFT>* paramPtr = nullptr;
                auto lve = new system_variable_block_expression<block_type::LOGICAL>(reinterpret_cast<block_variable<block_type::LOGICAL>*>(bit->second.ptr), idx);
                functional_block_variant fbv{ reinterpret_cast<block_variable<block_type::LOGICAL>*>(bit->second.ptr) };
                eater<dataflow_kind::LOGICAL,DFT> eat(fbv, paramPtr);
                m_expectedType = DFT;
                auto se = buildSExpr<dataflow_kind::LOGICAL,DFT>(ctx->s_expr());
                auto* feeding = new feeding_statement<dataflow_kind::LOGICAL,DFT>(eat, se);
                (void)lve;
                return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::FEEDING>*>(feeding) };
            });
        }
        return system_statement_variant{};
    }

system_statement_variant ChipsAstBuilder::buildLinkingStatement(ChipsParser::LinkingStatementContext* ctx) {
        std::string linkedName = ctx->IDENTIFIER(0)->getText();
        std::string supportName = ctx->IDENTIFIER(1)->getText();
        auto lit = m_blocks.find(linkedName);
        auto sit = m_blocks.find(supportName);
        linkable* linked = nullptr;
        support* sup = nullptr;
        if (lit != m_blocks.end()) {
            if (lit->second.bt == block_type::OBJECT) linked = new system_variable_block_expression<block_type::OBJECT>(reinterpret_cast<block_variable<block_type::OBJECT>*>(lit->second.ptr), {});
            else if (lit->second.bt == block_type::PHYSICAL) linked = new system_variable_block_expression<block_type::PHYSICAL>(reinterpret_cast<block_variable<block_type::PHYSICAL>*>(lit->second.ptr), {});
        }
        if (sit != m_blocks.end()) {
            if (sit->second.bt == block_type::OBJECT) sup = new system_variable_block_expression<block_type::OBJECT>(reinterpret_cast<block_variable<block_type::OBJECT>*>(sit->second.ptr), {});
            else if (sit->second.bt == block_type::PHYSICAL) sup = new system_variable_block_expression<block_type::PHYSICAL>(reinterpret_cast<block_variable<block_type::PHYSICAL>*>(sit->second.ptr), {});
        }
        auto* stmt = new linking_statement(linked, sup);
        return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::LINKING>*>(stmt) };
    }

system_statement_variant ChipsAstBuilder::buildSStatement(ChipsParser::S_statementContext* ctx) {
        m_stmtEnv = statement_env::SYSTEM;
        if (auto* c = dynamic_cast<ChipsParser::ObjectDeclarationContext*>(ctx)) return buildObjectDeclaration(c);
        if (auto* c = dynamic_cast<ChipsParser::FeedingStatementContext*>(ctx)) return buildFeedingStatement(c);
        if (auto* c = dynamic_cast<ChipsParser::LinkingStatementContext*>(ctx)) return buildLinkingStatement(c);
        if (auto* c = dynamic_cast<ChipsParser::RegularStatementContext*>(ctx)) return buildStatement<statement_env::SYSTEM>(c->statement());
        if (auto* c = dynamic_cast<ChipsParser::SIfStatementContext*>(ctx)) return buildSIfStatement(c->s_if_statement());
        if (auto* c = dynamic_cast<ChipsParser::SIfElseStatementContext*>(ctx)) return buildSIfElseStatement(c->s_if_else_statement());
        if (auto* c = dynamic_cast<ChipsParser::SLoopStatementContext*>(ctx)) return buildSLoopStatement(c->s_loop_statement());
        return system_statement_variant{};
    }

system_statement_variant ChipsAstBuilder::buildSIfStatement(ChipsParser::S_if_statementContext* ctx) {
        auto* node = new if_statement<statement_env::SYSTEM>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildExpr<expression_env::SYSTEM>(ctx->expr()));
        for (auto* s : ctx->s_statement()) node->get_if_section().add_statement(buildSStatement(s));
        return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::IF>*>(node) };
    }

system_statement_variant ChipsAstBuilder::buildSIfElseStatement(ChipsParser::S_if_else_statementContext* ctx) {
        auto* node = new if_else_statement<statement_env::SYSTEM>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildExpr<expression_env::SYSTEM>(ctx->s_if_statement()->expr()));
        for (auto* s : ctx->s_if_statement()->s_statement()) node->get_if_section().add_statement(buildSStatement(s));
        for (auto* s : ctx->s_statement()) node->get_else_section().add_statement(buildSStatement(s));
        return system_statement_variant{ static_cast<statement<statement_env::SYSTEM,recurring_statement::IF>*>(node) };
    }

system_statement_variant ChipsAstBuilder::buildSLoopStatement(ChipsParser::S_loop_statementContext* ctx) {
        std::string iterName = ctx->IDENTIFIER()->getText();
        std::string iterableName = ctx->s_suffixable_expr()->getText();
        block_type bt = block_type::OBJECT;
        auto bit = m_blocks.find(iterableName);
        if (bit != m_blocks.end()) bt = bit->second.bt;
        m_blocks[iterName] = BlockSymbol{ bt, nullptr, nullptr };
        for (auto* s : ctx->s_statement()) buildSStatement(s);
        return system_statement_variant{};
    }

std::any ChipsAstBuilder::visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitRegularStatement(ChipsParser::RegularStatementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitCollective_operation(ChipsParser::Collective_operationContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitBlock(ChipsParser::BlockContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) { return {}; }

std::any ChipsAstBuilder::visitImplementationStatementFallback(ChipsParser::ImplementationStatementContext *ctx) { return {}; }
