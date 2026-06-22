#include "chips_semantic_analyzer.hpp"
#include <iomanip>

// Ce fichier contient les implémentations des templates de SemanticAnalyzer
// Les templates DOIVENT être définis dans un header ou dans le même fichier
// que leur déclaration pour que le compilateur puisse les instancier

void SymbolTable::addSymbol(const Symbol& sym) {
    if(!scopes.empty()){
        scopes.back()[sym.name] = sym;
    }else{
        symbols[sym.name] = sym;
    }
}

SymbolTable::Symbol* SymbolTable::lookupSymbol(const std::string& name) {
    for(auto it = scopes.rbegin(); it != scopes.rend(); ++it){
        auto found = it->find(name);
        if(found != it->end()){
            return &found->second;
        }
    }

    auto it = symbols.find(name);
    if(it != symbols.end()){
        return &it->second;
    }

    return nullptr;
}

bool SymbolTable::symbolExists(const std::string& name) {
    return lookupSymbol(name) != nullptr;
}

void SymbolTable::printSymbols() const {
    std::cout << "\n Table des symboles:\n";
    std::cout << std::string(60, '-') << "\n";

    for(const auto& [name, sym] : symbols){
        std::cout << " " << std::setw(20) << name
                  << " | Type: " << std::setw(10) << (sym.isFunction ? "Function" : "Variable")
                  << " | Ligne: " << sym.line << "\n";
    }
    std::cout << std::string(60, '-') << "\n";
}

// // Template pour vérifier les déclarations de variables
// template <typename StatementsType>
// void SemanticAnalyzer::checkVariableDeclarations(StatementsType* statements) {
//     if (!statements) return;
    
//     auto& stmts = statements->get_statements();
//     for (auto& stmt : stmts) {
//         if (!stmt) continue;
        
//         // Vérifier si c'est une déclaration de dataflow
//         auto dfDecl = dynamic_cast<dataflow_full_declaration_node*>(stmt.get());
//         if (dfDecl) {
//             std::string varName = dfDecl->get_identifier();
//             SymbolTable::Symbol sym;
//             sym.name = varName;
//             sym.type = getDataflowType(dfDecl->get_df_type());
//             sym.isFunction = false;
//             symbolTable.addSymbol(sym);
//         }
//     }
// }

// // Template pour vérifier les déclarations de variables (version c_statements)
// template <>
// void SemanticAnalyzer::checkVariableDeclarations<c_statements_node>(c_statements_node* statements) {
//     if (!statements) return;
    
//     auto& stmts = statements->get_statements();
//     for (auto& stmt : stmts) {
//         if (!stmt) continue;
        
//         // Vérifier si c'est une déclaration de dataflow collective
//         auto cdfDecl = dynamic_cast<collective_dataflow_full_declaration_node*>(stmt.get());
//         if (cdfDecl) {
//             std::string varName = cdfDecl->get_identifier();
//             SymbolTable::Symbol sym;
//             sym.name = varName;
//             sym.type = getDataflowType(cdfDecl->get_df_type());
//             sym.isFunction = false;
//             symbolTable.addSymbol(sym);
//         }
//     }
// }

// // Template pour vérifier les boucles
// template <typename LoopType>
// void SemanticAnalyzer::checkLoopStatement(LoopType* loop) {
//     if (!loop) return;
    
//     std::string loopVar = loop->get_ident1();
    
//     // Vérifier que la variable de boucle existe (ou la créer)
//     SymbolTable::Symbol loopSym;
//     loopSym.name = loopVar;
//     loopSym.type = INT_DF;  // Les variables de boucle sont des entiers
//     loopSym.isFunction = false;
//     symbolTable.addSymbol(loopSym);
    
//     // Vérifier le corps de la boucle
//     auto stmts = loop->get_statements();
//     if (stmts) {
//         checkVariableDeclarations(stmts);
//         checkStatements(stmts);
//     }
// }

// // Template pour vérifier les if
// template <typename IfType>
// void SemanticAnalyzer::checkIfStatement(IfType* ifStmt) {
//     if (!ifStmt) return;
    
//     // Vérifier la condition
//     auto cond = ifStmt->get_condition();
//     if (cond) {
//         int condType = getExpressionType(cond);
//         if (!isTypeCompatible(condType, BOOL_DF)) {
//             addWarning(0, 0, "La condition du 'if' n'est pas de type booléen");
//         }
//     }
    
//     // Vérifier le corps du if
//     auto stmts = ifStmt->get_statements();
//     if (stmts) {
//         checkVariableDeclarations(stmts);
//         checkStatements(stmts);
//     }
// }

// // Template pour vérifier les if-else
// template <typename IfElseType>
// void SemanticAnalyzer::checkIfElseStatement(IfElseType* ifElseStmt) {
//     if (!ifElseStmt) return;
    
//     // Vérifier la partie if
//     auto ifNode = ifElseStmt->get_if_node();
//     if (ifNode) {
//         checkIfStatement(ifNode);
//     }
    
//     // Vérifier la partie else
//     auto elseStmts = ifElseStmt->get_else_node();
//     if (elseStmts) {
//         checkVariableDeclarations(elseStmts);
//         checkStatements(elseStmts);
//     }
// }

// // Template pour vérifier les assignments
// template <typename AssignNode>
// void SemanticAnalyzer::checkAssignment(AssignNode* assign) {
//     if (!assign) return;
    
//     // Vérifier que la variable de gauche existe
//     auto lhs = assign->get_lhs();
//     if (lhs) {
//         std::string varName = lhs->get_identifier();
//         if (!symbolTable.symbolExists(varName)) {
//             addWarning(0, 0, "La variable '" + varName + "' n'a pas été déclarée");
//         }
//     }
    
//     // Vérifier la compatibilité de type de l'expression de droite
//     auto rhs = assign->get_rhs();
//     if (rhs && lhs) {
//         int rhsType = getExpressionType(rhs->get_expression());
//         int lhsType = getExpressionType(lhs);
        
//         if (!isTypeCompatible(rhsType, lhsType)) {
//             addWarning(0, 0, "Incompatibilité de types dans l'assignation");
//         }
//     }
// }

// // Template générique pour vérifier les déclarations
// template <typename StatementsType>
// void SemanticAnalyzer::checkStatements(StatementsType* statements) {
//     if (!statements) return;
    
//     auto& stmts = statements->get_statements();
//     for (auto& stmt : stmts) {
//         if (stmt) {
//             checkStatement(stmt.get());
//         }
//     }
// }

// // Template générique pour vérifier un statement
// template <typename StatementType>
// void SemanticAnalyzer::checkStatement(StatementType* stmt) {
//     if (!stmt) return;
    
//     // Vérifier si c'est une boucle
//     auto loopStmt = dynamic_cast<loop_node*>(stmt);
//     if (loopStmt) {
//         checkLoopStatement(loopStmt);
//         return;
//     }
    
//     // Vérifier si c'est un if
//     auto ifStmt = dynamic_cast<if_node*>(stmt);
//     if (ifStmt) {
//         checkIfStatement(ifStmt);
//         return;
//     }
    
//     // Vérifier si c'est un if-else
//     auto ifElseStmt = dynamic_cast<if_else_node*>(stmt);
//     if (ifElseStmt) {
//         checkIfElseStatement(ifElseStmt);
//         return;
//     }
    
//     // Ajouter d'autres vérifications selon les besoins
// }

DATAFLOW_TYPE SemanticAnalyzer::getDataflowType(dataflow_type_node* dfType){
    if(!dfType) return DATAFLOW_TYPE::UNKNOWN_DF;

    return dfType->get_type();
}

bool SemanticAnalyzer::isTypeCompatible(DATAFLOW_TYPE type1, EXPRESSION_TYPE type2){
    if(type1 == INT_DF){
        if(type2 == INT_EXP || type2 == CAST_TO_INT_EXP) return true;
    }else if(type1 == FLOAT_DF){
        if(type2 == FLOAT_EXP || type2 == CAST_TO_FLOAT_EXP) return true;
    }else if(type1 == BOOL_DF){
        if(type2 == BOOL_EXP || type2 == CAST_TO_BOOL_EXP) return true;
    }
    return false;
}

bool SemanticAnalyzer::isNumericType(int type){
    return type == INT_DF || type == FLOAT_DF || type == INT_EXP || type == FLOAT_EXP || type == CAST_TO_INT_EXP || type == CAST_TO_FLOAT_EXP;
}

void SemanticAnalyzer::addError(SemanticErrorType t, int line, int column, std::string msg){
    addErrorImpl(t, line, column, {msg});
}

void SemanticAnalyzer::addErrorImpl(SemanticErrorType t, int line, int column, const std::vector<std::string>& msgs) {

    size_t size = msgs.size();
    std::string message;

    switch(t){
        case SemanticErrorType::UNDEFINED_FUNCTION: message = "Function "+msgs[0]+" never defined"; break;
        case SemanticErrorType::DUPLICATE_FUNCTION_DECLARATION: message = "Function "+msgs[0]+" already defined"; break;

        case SemanticErrorType::WRONG_COUNT_OF_ARGUMENT: message = "Function '"+msgs[0]+"' need "+msgs[1]+" argument(s) but received "+msgs[2]+" arguments"; break;
        case SemanticErrorType::NO_SAME_TYPE_ARGUMENT: message = "Function '"+msgs[0]+"' waited "+msgs[1]+" for an argument but received "+msgs[2]; break;

        case SemanticErrorType::NO_PLUGGING_WITH_INPUT: message = "Function "+msgs[0]+" didn't link with his input"; break;
        case SemanticErrorType::NO_PLUGGING_WITH_OUTPUT: message = "Function "+msgs[0]+" didn't link with his output"; break;

        case SemanticErrorType::UNDEFINED_VARIABLE: message = "Variable "+msgs[0]+" never defined"; break;
        case SemanticErrorType::DUPLICATE_VARIABLE_DECLARATION: message = "Variable "+msgs[0]+" already defined"; break;
        case SemanticErrorType::DUPLICATE_VARIABLE_IN_PARAMETER: message = "Parameter '"+msgs[0]+"' duplicate in '"+msgs[1]+"'"; break;

        case SemanticErrorType::TYPE_MISMATCH: 
            message = "Incompatible type in the declaration of '"+msgs[0]+"' :" +
            " expected "+msgs[1]+", but received "+msgs[2];
            break;

        case SemanticErrorType::IMPLICIT_CAST_ASSIGNMENT: message = "Implicit cast doesn't exist for assignment of '"+msgs[0]+"'"; break;
        case SemanticErrorType::IMPLICIT_CAST: message = "Implicit cast doesn't exist in chips between "+msgs[0]+" and "+msgs[1]; break;

        case SemanticErrorType::SAME_LINK: message = "Can't link function at himself"; break;
        case SemanticErrorType::NOT_FUNCTION_FOR_LINK_SOURCE: message = "Can't link '"+msgs[0]+"' for the source because this is not a function"; break;
        case SemanticErrorType::NOT_FUNCTION_FOR_LINK_TARGET: message = "Can't link '"+msgs[0]+"' for the target because this is not a function"; break;
        case SemanticErrorType::FUNCTION_PHYSICAL_CANT_BE_SOURCE: message = "Physical function '"+msgs[0]+"' can't be the source of a link"; break;
        
        case SemanticErrorType::TYPE_SUFFIXES_NOT_NUMERIC: message = "The type in suffixes isn't numeric"; break;

        case SemanticErrorType::HAS_CYCLE: message = "TODO"; break;
    }
    errors.emplace_back(line, column, message, "error");
}

void SemanticAnalyzer::addWarning(int line, int column, const std::string& msg){
    warnings.emplace_back(line, column, msg, "warning");
}

std::string SemanticAnalyzer::typeToString(int type){
    if(DATAFLOW_TYPE::INT_DF == type || EXPRESSION_TYPE::INT_EXP == type || EXPRESSION_TYPE::CAST_TO_INT_EXP) return "int";
    if(DATAFLOW_TYPE::FLOAT_DF == type || EXPRESSION_TYPE::FLOAT_EXP == type || EXPRESSION_TYPE::CAST_TO_FLOAT_EXP) return "float";
    if(DATAFLOW_TYPE::BOOL_DF == type || EXPRESSION_TYPE::BOOL_EXP == type || EXPRESSION_TYPE::CAST_TO_BOOL_EXP) return "bool";
    return "unknown";
}

void SemanticAnalyzer::printErrors() const {
    if(errors.empty()) return;

    std::cerr << "\n\033[1;31mSEMANTICS ERRORS (" << errors.size() << ")\033[0m\n";
    std::cerr << std::string(70, '=') << "\n";
    
    for (const auto& err : errors) {
        std::cerr << "  Line " << err.line << ", column " << err.column << "\n"
                << "     " << err.message << "\n\n";
    }
    
    std::cerr << std::string(70, '=') << "\n";
}

void SemanticAnalyzer::printWarnings() const {
    if (warnings.empty()) return;
    
    std::cout << "\n\033[1;33mSEMANTICS WARNINGS (" << warnings.size() << ")\033[0m\n";
    std::cout << std::string(70, '-') << "\n";
    
    for (const auto& warn : warnings) {
        std::cout << "  Line " << warn.line << ", column " << warn.column << "\n"
                << "     " << warn.message << "\n\n";
    }
    
    std::cout << std::string(70, '-') << "\n";
}

void SemanticAnalyzer::printSummary() const {
    std::cout << "\nSummary of analyze:\n";
    std::cout << "  Errors:      " << errors.size() << "\n";
    std::cout << "  Warnings: " << warnings.size() << "\n";
    std::cout << "\n";
}

void SemanticAnalyzer::analyze(logical_function_definition_node& node){
    int line = node.get_line();
    int column = node.get_column();

    std::string funcName = node.get_identifier();
    int type = node.get_type();

    if(definedFunctions.find(funcName) != definedFunctions.end()){
        addError(SemanticErrorType::DUPLICATE_FUNCTION_DECLARATION,
                                  line, column, funcName);
    }

    definedFunctions.insert(funcName);

    const auto& vectorDecls = node.get_df_parameter_list()->get_df_param_decls();

    SymbolTable::Symbol sym;
    sym.name = funcName;
    sym.isFunction = true;
    sym.functionType = FUNCTION_TYPE::LOGICAL;
    sym.line = line;
    sym.paramCount = vectorDecls.size();
    for(int i = 0; i < sym.paramCount; i++){
        sym.paramTypes.push_back(vectorDecls.at(i)->get_df_type()->get_type());
    }
    symbolTable.addSymbol(sym);

    checkFunctionParameters(&node);
}

void SemanticAnalyzer::analyze(physical_function_definition_node& node){
    int line = node.get_line();
    int column = node.get_column();

    std::string funcName = node.get_identifier();
    int type = node.get_type();

    if(definedFunctions.find(funcName) != definedFunctions.end()){
        addError(SemanticErrorType::DUPLICATE_FUNCTION_DECLARATION,
                                  line, column, funcName);
    }

    definedFunctions.insert(funcName);
    
    const auto& vectorDecls = node.get_pdf_parameter_list()->get_pdf_param_decls();

    SymbolTable::Symbol sym;
    sym.name = funcName;
    sym.isFunction = true;
    sym.functionType = FUNCTION_TYPE::PHYSICAL;
    sym.line = line;
    sym.paramCount = vectorDecls.size();
    for(int i = 0; i < sym.paramCount; i++){
        sym.paramTypes.push_back(vectorDecls.at(i)->get_df_type()->get_df_type()->get_type());
    }
    symbolTable.addSymbol(sym);

    checkFunctionParameters(&node);
}

void SemanticAnalyzer::analyze(dataflow_full_declaration_node& node){
    int line = node.get_line();
    int column = node.get_column();
    std::string varName = node.get_identifier();

    DATAFLOW_TYPE declaredType = getDataflowType(node.get_df_type());

    SymbolTable::Symbol sym;
    sym.name = varName;
    sym.type = declaredType;
    sym.line = line;
    sym.isFunction = false;
    symbolTable.addSymbol(sym);

    if(!node.get_rhs()){
        return;
    }

    EXPRESSION_TYPE rhsType = getExpressionType(node.get_rhs()->get_rhs());

    if(rhsType != EXPRESSION_TYPE::UNKNOWN_EXP && !isTypeCompatible(declaredType, rhsType)){
        addError(SemanticErrorType::TYPE_MISMATCH,
                line, column, varName, typeToString(declaredType), typeToString(rhsType));
    }
}

void SemanticAnalyzer::analyze(variable_assignment_node& node) {
    int line = node.get_line();
    int column = node.get_column();
    std::string varName = node.get_identifier();

    if(!symbolTable.symbolExists(varName)){
        addError(SemanticErrorType::UNDEFINED_VARIABLE,
                line, column, varName);
        return;
    }

    auto varSymbol = symbolTable.lookupSymbol(varName);
    DATAFLOW_TYPE varType = varSymbol->type;

    EXPRESSION_TYPE exprType = getExpressionType(node.get_expression());

    if(exprType == EXPRESSION_TYPE::UNKNOWN_EXP){
        addError(SemanticErrorType::IMPLICIT_CAST_ASSIGNMENT,
                line, column, varName);
    }

    if(exprType != EXPRESSION_TYPE::UNKNOWN_EXP && !isTypeCompatible(varType, exprType)){
        addError(SemanticErrorType::TYPE_MISMATCH,
                line, column, varName, typeToString(varType), typeToString(exprType));
    }
}

void SemanticAnalyzer::analyze(suffixes_node& node){
    int line = node.get_line();
    int column = node.get_column();

    const auto& suffixes = node.get_suffixes();

    for(const auto& expr : suffixes){
        int lineExpr = expr->get_line();
        int columnExpr = expr->get_column();

        EXPRESSION_TYPE typeExpr = getExpressionType(expr.get());
 
        if(!isNumericType(typeExpr)){
            addError(SemanticErrorType::TYPE_SUFFIXES_NOT_NUMERIC,
                    lineExpr, columnExpr);
        }

        //TODO vérifier si possible si l'expression comprise entre 0 et length
    }
}

// void SemanticAnalyzer::analyze(function_call_node& node){
//     int line = node.get_line();
//     int column = node.get_column();
//     std::string funcName = node.get_identifier();

//     calledFunctions.insert(funcName);

//     if(!symbolTable.symbolExists(funcName)){
//         addError(SemanticErrorType::UNDEFINED_FUNCTION,
//                 line, column, funcName);
//         return;
//     }

//     auto funcSymbol = symbolTable.lookupSymbol(funcName);

//     const auto& vectorArgument = node.get_expressions()->get_expressions();
//     int argCount = node.get_expressions()->get_expressions().size();

//     if(argCount != funcSymbol->paramCount){
//         addError(SemanticErrorType::WRONG_COUNT_OF_ARGUMENT,
//                 line, column, funcSymbol->name, std::to_string(funcSymbol->paramCount), std::to_string(argCount));
//         return;
//     }

//     for(int i = 0; i < argCount; i++){
//         EXPRESSION_TYPE typeArg = getExpressionType(vectorArgument.at(i).get());

//         if(!isTypeCompatible(funcSymbol->paramTypes.at(i), typeArg)){
//             addError(SemanticErrorType::NO_SAME_TYPE_ARGUMENT,
//                     line, column, funcSymbol->name, typeToString(funcSymbol->paramTypes.at(i)), typeToString(typeArg));
//         }
//     }
// }

void SemanticAnalyzer::analyze(link_node& node){
    int line = node.get_line();
    int column = node.get_column();

    std::string source = node.get_source();
    std::string target = node.get_target();

    // if(source == target){
    //     addError(SemanticErrorType::SAME_LINK,
    //             line, column);
    // }

    if(!symbolTable.symbolExists(source)){
        addError(SemanticErrorType::UNDEFINED_VARIABLE,
                line, column, source);
    }

    if(!symbolTable.symbolExists(target)){
        addError(SemanticErrorType::UNDEFINED_VARIABLE,
                line, column, target);
    }

    if(!symbolTable.symbolExists(source) || !symbolTable.symbolExists(target)) return;

    auto symSource = symbolTable.lookupSymbol(source);
    auto symTarget = symbolTable.lookupSymbol(target);

    if(!symSource->isFunction){
        addError(SemanticErrorType::NOT_FUNCTION_FOR_LINK_SOURCE,
                line, column, symSource->name);
    }

    if(!symTarget->isFunction){
        addError(SemanticErrorType::NOT_FUNCTION_FOR_LINK_TARGET,
                line, column, symTarget->name);
    }

    if(symSource->isFunction && symSource->functionType == FUNCTION_TYPE::PHYSICAL){
        addError(SemanticErrorType::FUNCTION_PHYSICAL_CANT_BE_SOURCE,
                line, column, symSource->name);
    }

    dependencyGraph.addEdge(*symSource, *symTarget);
}

void SemanticAnalyzer::checkFunctionParameters(logical_function_definition_node* funcDef){
    if(funcDef->get_df_parameter_list()->get_df_param_decls().empty()) return;

    std::string funcName = funcDef->get_identifier();
    int line = funcDef->get_line();
    std::set<std::string> paramNames;

    for(auto& param : funcDef->get_df_parameter_list()->get_df_param_decls()) {

        std::string paramName = param->get_identifier();

        if(paramNames.find(paramName) != paramNames.end()){
            addError(SemanticErrorType::DUPLICATE_VARIABLE_IN_PARAMETER,
                     line, 0, paramName, funcName);
        }

        paramNames.insert(paramName);
    }
}

void SemanticAnalyzer::checkFunctionParameters(physical_function_definition_node* funcDef) {
    if(funcDef->get_pdf_parameter_list()->get_pdf_param_decls().empty()) return;

    std::string funcName = funcDef->get_identifier();
    int line = funcDef->get_line();
    std::set<std::string> paramNames;

    for(auto& param : funcDef->get_pdf_parameter_list()->get_pdf_param_decls()) {

        std::string paramName = param->get_identifier();

        if(paramNames.find(paramName) != paramNames.end()){
            addError(SemanticErrorType::DUPLICATE_VARIABLE_IN_PARAMETER,
                     line, 0, paramName, funcName);
        }

        paramNames.insert(paramName);
    }
}

EXPRESSION_TYPE SemanticAnalyzer::getExpressionType(expression_node* expr){
    if(!expr) return EXPRESSION_TYPE::UNKNOWN_EXP;

    int line = expr->get_line();
    int column = expr->get_column();
    if(auto numLit = dynamic_cast<number_literal_node*>(expr)){
        return numLit->get_type();
    }

    if(auto var = dynamic_cast<variable_node*>(expr)){
        std::string varName = var->get_identifier();
        if(symbolTable.lookupSymbol(varName)) {
            switch(symbolTable.lookupSymbol(varName)->type){
                case INT_DF: return INT_EXP;
                case FLOAT_DF: return FLOAT_EXP;
                case BOOL_DF: return BOOL_EXP;
                default: return UNKNOWN_EXP;
            }
        }

        addError(SemanticErrorType::UNDEFINED_VARIABLE, 
                line, column, varName);
        return EXPRESSION_TYPE::UNKNOWN_EXP;
    }

    if(auto binOp = dynamic_cast<binary_expression_node*>(expr)){
        EXPRESSION_TYPE leftType = getExpressionType(binOp->get_lhs());
        EXPRESSION_TYPE rightType = getExpressionType(binOp->get_rhs());

        EXPRESSION_TYPE type = binOp->get_type();

        switch(type){
            case PLUS_EXP: return getExpressionTypeWithArithmetic(leftType, rightType);
            case MINUS_EXP: return getExpressionTypeWithArithmetic(leftType, rightType);
            case TIMES_EXP: return getExpressionTypeWithArithmetic(leftType, rightType);
            case DIV_EXP: return getExpressionTypeWithArithmetic(leftType, rightType);
            case MOD_EXP: if(leftType == INT_EXP && rightType == INT_EXP) return leftType; return UNKNOWN_EXP;
            case AND_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case OR_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case EQ_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case NEQ_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case GT_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case LT_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case GEQ_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
            case LEQ_EXP: return getExpressionTypeWithBoolean(leftType, rightType);
        }

    }

    if(auto unary = dynamic_cast<unary_expression_node*>(expr)){
        EXPRESSION_TYPE type = unary->get_type();
        EXPRESSION_TYPE rightType = getExpressionType(unary->get_rhs());

        if(type == U_MINUS_EXP && isNumericType(rightType)) return rightType;
        if(type == NOT_EXP && rightType == BOOL_EXP) return rightType;
    }

    if(auto cast = dynamic_cast<cast_node*>(expr)){
        EXPRESSION_TYPE type = cast->get_type();
        EXPRESSION_TYPE rightType = getExpressionType(cast->get_expr());
        
        // std::cout << "type cast: " << typeToString(type) << " for type: " << typeToString(rightType) << std::endl;
        if(isNumericType(type) && isNumericType(rightType)) return type;
    }

    if(auto cast = dynamic_cast<c_cast_node*>(expr)){
        EXPRESSION_TYPE type = cast->get_type();
        EXPRESSION_TYPE rightType = getExpressionType(cast->get_expr());

        if(isNumericType(type) && isNumericType(rightType)) return type;
    }

    return EXPRESSION_TYPE::UNKNOWN_EXP;
}

EXPRESSION_TYPE SemanticAnalyzer::getExpressionTypeWithArithmetic(EXPRESSION_TYPE left, EXPRESSION_TYPE right){
    if(left == BOOL_EXP || right == BOOL_EXP) return UNKNOWN_EXP;
    if(left == right) return left;
    return UNKNOWN_EXP;
}

EXPRESSION_TYPE SemanticAnalyzer::getExpressionTypeWithBoolean(EXPRESSION_TYPE left, EXPRESSION_TYPE right){
    if(left == right) return BOOL_EXP;
    return UNKNOWN_EXP;
}

void SemanticAnalyzer::verifyGraphCycle(){
    dependencyGraph.print();
    if(dependencyGraph.hasCycle()){
        // std::vector<SymbolTable::Symbol> cyclePath = dependencyGraph.getCyclePath();
        addError(SemanticErrorType::HAS_CYCLE,
                0, 0);
    }
}