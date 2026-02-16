#ifndef SEMANTIC_ANALYZER_HPP
#define SEMANTIC_ANALYZER_HPP

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <set>
#include "ChipsAST.hpp"


// Forward declaration
class ChipsToXmiVisitor;

enum class SemanticErrorType {
    //FUNCTIONS
    FUNCTION_WITHOUT_SIGNATURE,
    UNDEFINED_FUNCTION,             
    DUPLICATE_FUNCTION_DECLARATION,

    WRONG_COUNT_OF_ARGUMENT,
    NO_SAME_TYPE_ARGUMENT,

    NO_PLUGGING_WITH_INPUT,
    NO_PLUGGING_WITH_OUTPUT,

    //VARIABLES
    UNDEFINED_VARIABLE,
    DUPLICATE_VARIABLE_DECLARATION,
    DUPLICATE_VARIABLE_IN_PARAMETER,

    IMPLICIT_CAST_ASSIGNMENT,

    TYPE_MISMATCH,
    IMPLICIT_CAST,

    //LINK
    SAME_LINK,
    NOT_FUNCTION_FOR_LINK_SOURCE,
    NOT_FUNCTION_FOR_LINK_TARGET,
    FUNCTION_PHYSICAL_CANT_BE_SOURCE,

    // SUFFIXES
    TYPE_SUFFIXES_NOT_NUMERIC,

    // DEPENDENCY GRAPH
    HAS_CYCLE,
};

class SemanticError {
    public:
        int line;
        int column;
        std::string message;
        std::string severity;
        
        SemanticError(int l, int c, const std::string& msg, const std::string& sev = "error")
            : line(l), column(c), message(msg), severity(sev) {}
};

class SymbolTable {
    public:
        struct Symbol {
            std::string name;
            DATAFLOW_TYPE type;  // INT_DF, FLOAT_DF, BOOL_DF
            int line;
            bool isFunction;
            FUNCTION_TYPE functionType;
            int paramCount;
            std::vector<DATAFLOW_TYPE> paramTypes;

            bool operator<(const Symbol& other) const {
                return name < other.name;
            }

            bool operator==(const Symbol& other) const {
                return name == other.name && isFunction == other.isFunction && type == other.type &&
                       functionType == other.functionType && paramCount == other.paramCount && paramTypes == other.paramTypes;
            }
        };
        
    private:
        std::map<std::string, Symbol> symbols;
        std::vector<std::map<std::string, Symbol>> scopes;
        
    public:
        void enterScope() { scopes.push_back({}); }
        void exitScope() { if (!scopes.empty()) scopes.pop_back(); }
        
        void addSymbol(const Symbol& sym);
        Symbol* lookupSymbol(const std::string& name);
        bool symbolExists(const std::string& name);
        void printSymbols() const;
};

class ChipsGraph {
    public:
        using NodeId = SymbolTable::Symbol;

    private:
        std::map<NodeId, std::set<NodeId>> adjacencyList;

    public:
        ChipsGraph() = default;

        void addNode(NodeId sym){
            if(adjacencyList.find(sym) == adjacencyList.end()){
                adjacencyList[sym] = std::set<NodeId>();
            }
        }

        /**
         * @brief if node from or to didn't exist, we insert them
         */
        void addEdge(NodeId from, NodeId to){
            addNode(from);
            addNode(to);
            adjacencyList[from].insert(to);
        }
        
        bool hasCycle(){
            std::set<NodeId> visitors;

            for(const auto& [node, _] : adjacencyList){
                if(visitors.find(node) == visitors.end()){
                    if(hasCycleDFS(node, visitors)){
                        return true;
                    }
                }
            }
            return false;
        }

        // std::vector<NodeId> getCyclePath(){

        // }

        /**
         * @brief Afficher le graphe
         */
        void print() const {
            std::cout << "\n=== Graphe ===\n";
            for (const auto& [from, toSet] : adjacencyList) {
                std::cout << from.name << " -> ";
                
                if (toSet.empty()) {
                    std::cout << "(aucune dépendance)";
                } else {
                    for (NodeId to : toSet) {
                        std::cout << to.name;
                    }
                }
                std::cout << "\n";
            }
            std::cout << "==============\n\n";
        }

    private:
        bool hasCycleDFS(NodeId node, std::set<NodeId> visitors){
            visitors.insert(node);
            for(NodeId neighbor : adjacencyList[node]){
                if(visitors.find(neighbor) != visitors.end()){
                    return true;
                }
                if(hasCycleDFS(neighbor, visitors)){
                    return true;
                }
            }

            return false;
        }
};

class SemanticAnalyzer {
    private:
        std::vector<SemanticError> errors;
        std::vector<SemanticError> warnings;
        SymbolTable symbolTable;
        std::set<std::string> definedFunctions;
        std::set<std::string> calledFunctions;

        ChipsGraph dependencyGraph;
        
        // Permettre à ChipsToXmiVisitor d'accéder aux membres privés
        friend class ChipsToXmiVisitor;
        
    public:
        SemanticAnalyzer() = default;
        virtual ~SemanticAnalyzer() = default;
        
        void printErrors() const;
        void printWarnings() const;
        void printSummary() const;
        
        bool hasErrors() const { return !errors.empty(); }
        bool hasWarnings() const { return !warnings.empty(); }
        int getErrorCount() const { return errors.size(); }
        int getWarningCount() const { return warnings.size(); }

        
    private:

        void analyze(logical_function_definition_node& node);
        void analyze(physical_function_definition_node& node);

        void analyze(dataflow_full_declaration_node& node);
        void analyze(variable_assignment_node& node);

        void analyze(suffixes_node& node);

        // void analyze(function_call_node& node);

        void analyze(link_node& node);

        void checkFunctionDefinitions(chips_node* ast);

        void checkFunctionParameters(physical_function_definition_node* funcDef);
        void checkFunctionParameters(logical_function_definition_node* funcDef);

        // void checkSystemDefinition(system_node* system);

        // template <typename StatementsType>
        // void checkVariableDeclarations(StatementsType* statements);

        // template <typename StatementsType>
        // void checkStatements(StatementsType* statements);

        // template <typename StatementType>
        // void checkStatement(StatementType* stmt);

        // template <typename AssignNode>
        // void checkAssignment(AssignNode* assign);
        // void checkFunctionCall(function_call_node* call);

        // template <typename LoopType>
        // void checkLoopStatement(LoopType* loop);

        // template <typename IfType>
        // void checkIfStatement(IfType* ifStmt);

        // template <typename IfElseType>
        // void checkIfElseStatement(IfElseType* ifElseStmt);
        
        EXPRESSION_TYPE getExpressionType(expression_node* expr);

        EXPRESSION_TYPE getExpressionTypeWithArithmetic(EXPRESSION_TYPE left, EXPRESSION_TYPE right);
        EXPRESSION_TYPE getExpressionTypeWithBoolean(EXPRESSION_TYPE left, EXPRESSION_TYPE right);

        DATAFLOW_TYPE getDataflowType(dataflow_type_node* dfType);
        bool isTypeCompatible(DATAFLOW_TYPE type1, EXPRESSION_TYPE type2);
        bool isNumericType(int type);

        void verifyGraphCycle();
        
        void addError(SemanticErrorType t, int line, int column, std::string msg);

        template<typename... Args>
        void addError(SemanticErrorType t, int line, int column, Args... msgs){
            std::vector<std::string> messages = {std::string(msgs)...};
            addErrorImpl(t, line, column, messages);
        }

        void addErrorImpl(SemanticErrorType t, int line, int column, const std::vector<std::string>& messages);

        void addWarning(int line, int column, const std::string& msg);
        std::string typeToString(int type);
};

#endif