
#include "ast_node_definitions.hpp"
#include "ChipsToXmiWriter.hpp"
#include "chips_ast2xmi_utils.hpp"

#include<vector>
#include <algorithm>
#include <unordered_map>

namespace chips{

	struct chips_ast2xmi_visitor {

		// Structure pour stocker les informations de symbole
		struct SymbolInfo {
			std::string path;        // Chemin XMI
			std::string type;        // Type: "channel", "contextual", "variable", "block"
									//       "object", "physical", "logical", "sensor",
									//       "iterator", "physical_parameter:"+dft, "logical_parameter:"+dft 
									//       "collective_parameter:"+dft, "actuator_output:"+dft,
									//       "output:"+dft
			SymbolInfo() = default;
			SymbolInfo(const std::string& p, const std::string& t = "unknown") 
				: path(p), type(t) {}
		};

		// Structure pour stocker les informations de définition
        struct DefinitionInfo {
            std::string name;           // Nom de la définition
            std::string type;           // Type: "physical", "object", "logical", etc.
            std::string path;           // Chemin XMI complet: //@preamble/@definitions.X
            int index;                  // Index dans la liste des définitions
            std::map<std::string, SymbolInfo> variables;  // Nom -> info des variables/canaux déclarés dans le with
            
            DefinitionInfo() = default;
            DefinitionInfo(const std::string& n, const std::string& t, const std::string& p, int i) 
                : name(n), type(t), path(p), index(i) {}
        };

		enum class StatementFamily {
            Auto,
            Primitive,
            System,
            Node,
            Collective,
            Implementation
        };

		// Members
		ChipsToXmiWriter &m_writer;
        std::ostream &m_out;
        std::string m_current_ast_path;

        std::vector<std::unordered_map<std::string, SymbolInfo>> scopes = {};
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> function_outputs = {};
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> function_parameters = {};
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> function_channels = {};
        std::unordered_map<std::string, std::string> declarated_block_system = {};


        std::map<std::string, SymbolInfo> m_symbol_table;  // nom -> (chemin AST, type)
        std::map<std::string, DefinitionInfo> m_definitions_table;  // nom -> info définition
        std::string m_current_definition;  // Nom de la définition actuellement visitée
        std::string m_impl_def_implementing_node;  // Nom du nœud implémentant (défini lors de visit(implementation_definition_node))
        std::string m_impl_def_implemented_object;  // Nom de l'objet implémenté (défini lors de visit(implementation_definition_node))
        std::string m_statement_tag = "statements";  // Tag name override for if/else sections
        std::vector<std::string> m_semantic_errors;
        int m_extra_statements_generated = 0;  // Compteur de statements supplémentaires générés

        expression_env current_env;
        std::string current_fname;
        int def_index = 0;
        int param_index = 0;
        int sensor_index = 0;
        int nbTab = 1;


        // Helpers
        std::ostream &out() { return m_out; }
        std::string get_ast_path() const { return m_current_ast_path; }
        std::string get_ast_path_by_name(const std::string &name);
        SymbolInfo get_symbol_info(const std::string &name);

		
        void enterScopes(){
            scopes.emplace_back();
        }

        void exitScope(){
            if(scopes.empty()){
                throw std::runtime_error("No scope to exit");
            }
            scopes.pop_back();
        }

        void register_output(const std::string& fname, const std::string& output, const std::string& path){
            for(const auto& [k1, v1] : function_outputs){
                for(const auto& [k2, v2] : v1){
                    if(fname == k1 && output == k2){
                        report_semantic_error("Duplicate function output declaration: " + output);
                    }
                }
            }
            function_outputs[fname][output] = path;
        }

        void register_channel(const std::string& fname, const std::string& channel, const std::string& path){
            for(const auto& [k1, v1] : function_channels){
                for(const auto& [k2, v2] : v1){
                    if(fname == k1 && channel == k2){
                        report_semantic_error("Duplicate function output declaration: " + channel);
                    }
                }
            }
            function_channels[fname][channel] = path;
        }

        void register_parameter(const std::string& fname, const std::string& parameter, const std::string& path){
            for(const auto& [k1, v1] : function_parameters){
                for(const auto& [k2, v2] : v1){
                    if(fname == k1 && parameter == k2){
                        report_semantic_error("Duplicate paramter declaration: " + parameter);
                    }
                }
            }
            function_parameters[fname][parameter] = path;
        }

        std::string get_ast_path_by_name_output(const std::string& fname, const std::string& output){
            for(auto it = function_outputs.cbegin(); it != function_outputs.cend(); it++){
                if(it->first == fname){
                    auto second = it->second;
                    for(auto it2 = second.cbegin(); it2 != second.cend(); it2++){
                        if(it2->first == output){
                            return it2->second;
                        }
                    }
                }
            }
            // std::cerr << ">>>>>>>>>[WARNING] output '" << output << "' in " << fname << " NON trouvée dans la table des symboles" << std::endl;
            report_semantic_error("Undefined output: " + output);
            return output;
        }

        std::string get_ast_path_by_name_channel(const std::string& fname, const std::string& channel){
            for(auto it = function_channels.cbegin(); it != function_channels.cend(); it++){
                if(it->first == fname){
                    auto second = it->second;
                    for(auto it2 = second.cbegin(); it2 != second.cend(); it2++){
                        if(it2->first == channel){
                            return it2->second;
                        }
                    }
                }
            }
            // std::cerr << ">>>>>>>>>[WARNING] channel '" << channel << "' in " << fname << " NON trouvée dans la table des symboles" << std::endl;
            report_semantic_error("Undefined channel: " + channel);
            return channel;
        }

        std::string get_type_of_declarated_block(const std::string& variable){
            // std::cerr << "type of " << variable << " " << declarated_block_system[variable] << std::endl;
            return declarated_block_system[variable];
        }

        std::string get_ast_path_by_name_parameter(const std::string& fname, const std::string& parameter){
            for(auto it = function_parameters.cbegin(); it != function_parameters.cend(); it++){
                if(it->first == fname){
                    auto second = it->second;
                    for(auto it2 = second.cbegin(); it2 != second.cend(); it2++){
                        if(it2->first == parameter){
                            return it2->second.substr(0, it2->second.length() - 23);
                        }
                    }
                }
            }
            // std::cerr << ">>>>>>>>>[WARNING] Paramètre '" << parameter << "' in " << fname << " NON trouvée dans la table des symboles" << std::endl;
            report_semantic_error("Undefined parameter: " + parameter);
            return parameter;
        }

        void register_variable(const std::string &name, const std::string &path, const std::string &type = "variable") {
            auto existing = m_symbol_table.find(name);
            if (existing != m_symbol_table.end()) {
                report_semantic_error("Duplicate variable declaration: " + name);
            }
            m_symbol_table[name] = SymbolInfo(path, type);
        }

        void register_block(const std::string& type, const std::string& variable){
            auto existing = declarated_block_system.find(variable);
            if (existing != declarated_block_system.end()) {
                report_semantic_error("Duplicate block declaration: " + variable);
            }
            declarated_block_system[variable] = type;
        }
        
        // Track a definition (called when visiting definition nodes)
        void register_definition(const std::string &name, const std::string &type, const std::string &path, int index) {
            m_definitions_table[name] = DefinitionInfo(name, type, path, index);
            // std::cerr << "[DEBUG] Definition '" << name << "' enregistrée avec le chemin: " << path << std::endl;
        }
        
        // Register a variable within a definition (called when visiting with/init/then statements)
        void register_definition_variable(const std::string &def_name, const std::string &var_name, const std::string &var_path, const std::string &var_type) {
            auto it = m_definitions_table.find(def_name);
            if (it != m_definitions_table.end()) {
                it->second.variables[var_name] = SymbolInfo(var_path, var_type);
                // std::cerr << "[DEBUG] Variable '" << var_name << "' registered in definition '" << def_name << "' with path: " << var_path << std::endl;
            }
        }
        
        // Find the path of a variable within a definition
        SymbolInfo find_variable_in_definition(const std::string &def_name, const std::string &var_name) {
            auto it = m_definitions_table.find(def_name);
            if (it != m_definitions_table.end()) {
                auto var_it = it->second.variables.find(var_name);
                if (var_it != it->second.variables.end()) {
                    return var_it->second;
                }
            }
            return SymbolInfo("", "unknown");
        }
        
        void push_ast_path(const std::string &segment) { m_current_ast_path += segment; }
        void pop_ast_path(const std::string &segment) { 
            size_t pos = m_current_ast_path.rfind(segment);
            if (pos != std::string::npos) {
                m_current_ast_path.erase(pos);
            }
        }
        void set_ast_path(const std::string &path) { m_current_ast_path = path; }
        void writeAttribute(const std::string &name, const std::string &value);
        void endEmptyElement();
        void visit_generic(ast_node &node); // squelette commun
        void report_semantic_error(const std::string &message);
        void ensure_namespace_for_prefix(const std::string &ns_prefix);
        void ensure_namespace_for_type(const std::string &type_value);
        StatementFamily detect_statement_family() const;
        std::string statement_prefix(StatementFamily family = StatementFamily::Auto) const;
        std::string statement_type(const std::string &suffix, StatementFamily family = StatementFamily::Auto) const;
        
        // Get xsi:type for variable expression based on symbol type (physical, logical, object)
        std::string get_xsi_type_for_symbol(const SymbolInfo &info);
        
        // Get xsi:type for system declaration based on definition type (physical->physical_declaration, etc.)
        std::string get_declaration_type_from_definition(const std::string &definition_type);

        template<dataflow_type dft, expression_env expenv>
        void arithmetic_visit(rvalue<dft, expenv>& node){
            if(auto* dir = dynamic_cast<direct<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is direct" << std::endl;
                visit(*dir);
            }else if(auto* pl = dynamic_cast<plus<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is plus" << std::endl;
                visit(*pl); 
            }else if(auto* min = dynamic_cast<minus<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is minus" << std::endl;
                visit(*min);
            }else if(auto* min = dynamic_cast<uminus_operator<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is uminus" << std::endl;
                visit(*min);
            }else if(auto* mu = dynamic_cast<mult<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is mult" << std::endl;
                visit(*mu); 
            }else if(auto* di = dynamic_cast<chips::div<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is div" << std::endl;
                visit(*di); 
            }else if(auto* mo = dynamic_cast<mod<expenv>*>(&node)){
                // std::cerr << "rvalue is mod" << std::endl;
                visit(*mo); 
            }else if(auto* cast = dynamic_cast<cast_as<dft, expenv>*>(&node)){
                // std::cerr << "rvalue is cast" << std::endl;
                visit(*cast);
            }else if(auto* var = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is var" << std::endl;
                visit(*var);
            }else if(auto* func = dynamic_cast<function<dft,expenv>*>(&node)){
                // std::cerr << "rvalue is func" << std::endl;
                visit(*func);
            }else if(auto* in = dynamic_cast<input*>(&node)){
                // std::cerr << "rvalue is input" << std::endl;
                visit(*in);
            }else if(auto* st = dynamic_cast<stop*>(&node)){
                // std::cerr << "rvalue is stop" << std::endl;
                visit(*st);
            }else{
                // std::cerr << "ERROR RVALUE IS NOTHING UP THERE: " << typeid(node).name() << std::endl;
            }
        }

        template<dataflow_type dft, expression_env expenv>
        void binary_boolean_visit(rvalue<dft,expenv>& node){
            // std::cout << "binary" << std::endl;
            if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<eq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<neq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<direct<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<plus<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<plus<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<minus<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<minus<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<uminus_operator<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<uminus_operator<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<mult<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<mult<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<mod<expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<chips::div<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<chips::div<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<cast_as<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<cast_as<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<and_operator<expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<or_operator<expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<not_operator<expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                visit(*p);
            }
            else if(auto* func = dynamic_cast<function<dft,expenv>*>(&node)){   // <-- add this
                visit(*func);
            }
            else if(auto* p = dynamic_cast<input*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<stop*>(&node)){
                visit(*p);
            } else {
                std::cerr << "unhandled binary boolean visit case!" << std::endl;
            }
        }

        std::string repeat(const std::string&  s, int n){

            // commented because it is bugged and I'd rather have no indentation than too much of a bad one

            // std::string out;
            // // Protection: éviter les allocations massives si n est négatif
            // if(n < 0) {
            //     // std::cerr << "[WARNING] repeat() called with negative count: " << n << std::endl;
            //     n = 0;
            // }
            // std::size_t count = static_cast<std::size_t>(n);
            // out.reserve(s.size() * count);
            // for(std::size_t i = 0; i < count; i++){
            //     out += s;
            // }
            // return out;
            return s;
        }

        std::string toLower(const std::string& str) {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(),
                        [](unsigned char c){ return std::tolower(c); });
            return result;
        }

        
        template<block_type bt>
        void handle_statement_declaration(block_declaration<bt>& node){
            auto definition = node.get_definition();
            auto variable = node.get_variable();

            std::string definition_name = definition->get_name();
            std::string variable_name = variable.get_name();
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dimensions = variable.get_dimensions();

            std::string path_definition = get_ast_path_by_name(definition_name);

            out() << repeat("\t", ++nbTab);
            writeAttribute("xsi:type","chips.statements.system:"+bt_to_string<bt>()+"_declaration");
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("def", path_definition);
            out() << ">\n";
            nbTab--;

            std::string segment = "/@variable";
            push_ast_path(segment);
            std::string declarated_var_path = get_ast_path();
            register_variable(variable_name, declarated_var_path);
            register_block(definition_name, variable_name);

            out() << repeat("\t", nbTab++) << "<variable\n" << repeat("\t", nbTab);
            writeAttribute("name", variable_name);
            nbTab--;
            if(!dimensions.empty()){
                for(auto dimension : dimensions){
                    out() << ">\n" << repeat("\t", nbTab) << "<dimensions\n";
                    nbTab++; nbTab++;
                    out() << repeat("\t", nbTab);

                    std::visit([&](auto dim){
                        // Null pointer safety check
                        if(dim == nullptr){
                            // std::cerr << "[WARNING] Null pointer in dimensions variant at line " << __LINE__ << std::endl;
                            return;
                        }
                        
                        using dim_t = std::remove_pointer_t<std::decay_t<decltype(dim)>>;

                        if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                            (*dim).accept(*this);
                        }else{
                            arithmetic_visit(*dim);
                        }
                    }, dimension);

                }
                out() << "</variable>\n";
            }else{
                out() << "/>\n";
            }

            pop_ast_path(segment);
        }

        
        template<dataflow_type dft, statement_env stenv>
        void handle_statement_declaration(dataflow_declaration<dft, stenv>& node){
            std::string type = dft_to_string(dft);
            std::string name = node.get_variable().get_name();
            out() << repeat("\t", ++nbTab);
            writeAttribute("xsi:type", statement_type(type+"_declaration"));
            out() << ">\n";
            nbTab--;

            std::string segment = "/@variable";
            push_ast_path(segment);
            std::string declarated_var_path = get_ast_path();
            register_variable(name, declarated_var_path, type);
            auto dims = node.get_variable().get_dimensions();  // Now returns a copy, safe to use
            
            // std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << declarated_var_path << std::endl;

            out() << repeat("\t", nbTab++) << "<variable\n" << repeat("\t", nbTab);
            writeAttribute("name", name);
            nbTab--;
            if(!dims.empty()){

                for(auto dimension : dims){
                    out() << ">\n" << repeat("\t", nbTab) << "<dimensions\n";
                    nbTab++; nbTab++;
                    out() << repeat("\t", nbTab);

                    std::visit([&](auto dim){
                        // Null pointer safety check
                        if(dim == nullptr){
                            // std::cerr << "[WARNING] Null pointer in dimensions variant at line " << __LINE__ << std::endl;
                            return;
                        }
                        
                        using dim_t = std::remove_pointer_t<std::decay_t<decltype(dim)>>;

                        if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                            (*dim).accept(*this);
                        }else{
                            arithmetic_visit(*dim);
                        }
                    }, dimension);

                }
                out() << "</variable>\n";
            }else{
                out() << "/>\n";
            }
            
            pop_ast_path(segment);
            
        }

        
        template<dataflow_type dft, statement_env stenv>
        void handle_statement_assignment(dataflow_assignment<dft, stenv>& node){

            constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;

            std::string xvalue_prefix;
            
            if(!is_system_context(current_env)){
                if(current_env == expression_env::COLLECTIVE){
                    xvalue_prefix = "chips.xvalues.collective";
                }else{
                    xvalue_prefix = "chips.xvalues.primitive";
                }
            }else{
                xvalue_prefix = "chips.xvalues.system";
            }


            std::string type = dft_to_string(dft);
            std::string name = "";
            std::string value = "";
            std::vector<int_rvalue_expression_variant<expenv>>* lindex = nullptr;

            if(auto* lvalue = dynamic_cast<variable_expression<dft, expenv>*>(node.get_lhs())){
                if(auto* clvalue = dynamic_cast<variable_contextual_expression<dft, expenv>*>(lvalue)){
                    value = "contextual_"+type+"_expression";
                }else{
                    value = type+"_variable_expression";
                }
                name = lvalue->get_variable()->get_name();
                lindex = &lvalue->get_index();
            }

            std::string path = get_ast_path_by_name(name);

            out() << repeat("\t", ++nbTab);
            writeAttribute("xsi:type", statement_type(type+"_assignment"));
            out() << ">\n";
            nbTab--;

            out() << repeat("\t", nbTab++) << "<lvalue\n" << repeat("\t", ++nbTab);
            writeAttribute("xsi:type", xvalue_prefix+":"+value);
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("variable", path);

            if(!lindex || lindex->empty()){
                out() << "/>\n";
                nbTab--;
                nbTab--;
            }else{
                out() << ">\n" << repeat("\t", nbTab);

                for(auto index : *lindex){
                    out() << "<index\n" << repeat("\t", nbTab);
                    std::visit([&](auto ind){
                        using dim_t = std::remove_pointer_t<std::decay_t<decltype(ind)>>;

                        // if(!ind){
                        //     out() << "<!-- TODO DIMENSION -->\n";
                        //     return;
                        // }

                        if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                            (*ind).accept(*this);
                        }else{
                            arithmetic_visit(*ind);

                            if(!only_one_child(*ind)){
                                // out() << "ONE CHILD\n";
                                out() << "</index>\n";
                            }
                            
                        }
                        out() << "</lvalue>\n";
                    }, index);
                }
            }
            node.get_rhs()->accept(*this);
        }

        template<node_element ne>
        void handle_node_element_declaration(node_element_declaration<ne>& node){
            if constexpr(ne != node_element::CHANNEL){
                std::string identifier = node.get_name();
                std::string segment = "/@variable";
                push_ast_path(segment);

                // Enregistrer le ctx dans la table des symboles
                // Le chemin du ctx est juste get_ast_path() car on est déjà dans /@with/@statements.X
                register_variable(identifier, get_ast_path(), "ctx");
                std::string type = statement_type("contextual_"+dft_to_string(ne_to_dft(ne))+"_declaration", StatementFamily::Node);

                // Also register in the current definition if we're in one
                if (!m_current_definition.empty()) {
                    register_definition_variable(m_current_definition, identifier, get_ast_path(), "ctx");
                }

                nbTab++;
                out() << repeat("\t", nbTab);
                writeAttribute("xsi:type", type);
                out() << "\n" << repeat("\t", nbTab);
                writeAttribute("identifier", identifier);
                out() << ">\n";

                out() << repeat("\t", nbTab) << "<variable\n";
                nbTab++;
                out() << repeat("\t", nbTab);
                writeAttribute("name", identifier);
                out() << "/>\n"; 
                nbTab--;
                nbTab--;
                pop_ast_path(segment);
            }
        }

        template<expression_env expenv>
        void handle_condition(bool_rvalue_expression_variant<expenv>& node){
            out() << ">\n" << repeat("\t", nbTab) << "<condition\n" << repeat("\t", nbTab);

            std::visit([&](auto* value){
                if(auto* v = dynamic_cast<stop*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<input*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<gt<expenv,dataflow_type::INT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<gt<expenv,dataflow_type::FLOAT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<lt<expenv,dataflow_type::INT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<lt<expenv,dataflow_type::FLOAT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<geq<expenv,dataflow_type::INT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<geq<expenv,dataflow_type::FLOAT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<leq<expenv,dataflow_type::INT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<leq<expenv,dataflow_type::FLOAT>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<eq<dataflow_type::INT,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<eq<dataflow_type::FLOAT,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<eq<dataflow_type::BOOL,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<neq<dataflow_type::INT,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<neq<dataflow_type::FLOAT,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<neq<dataflow_type::BOOL,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<or_operator<expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<and_operator<expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<not_operator<expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(value)){
                    visit(*v);
                }else if(auto* v = dynamic_cast<variable_expression<dataflow_type::BOOL,expenv>*>(value)){
                    visit(*v);
                }else{
                    out() << "<-- ERROR CONDITION -->\n";
                }

                using cond_t = std::remove_pointer_t<std::decay_t<decltype(value)>>;
                if constexpr(std::is_same_v<cond_t, input> || std::is_same_v<cond_t, stop>){
                    // out() << "</condition>\n";
                }else{
                    auto& bool_node = static_cast<rvalue<dataflow_type::BOOL, expenv>&>(*value);
                    if(!only_one_child<dataflow_type::BOOL, expenv>(bool_node)){
                        out() << "</condition>\n";
                    }
                }

            }, node);
        }
        
        
        template<statement_env stenv>
        void handle_statement(typename SttEnvToSttVariant<stenv>::type& stt){
            std::visit([&](auto* ptr) {
                if (auto* if_else = dynamic_cast<if_else_statement<stenv>*>(ptr)) {
                    handle_statement_if_else(*if_else);
                } else if (auto* if_simple = dynamic_cast<if_statement<stenv>*>(ptr)) {
                    handle_statement_if(*if_simple);
                } else if (auto* decl_int = dynamic_cast<dataflow_declaration<dataflow_type::INT, stenv>*>(ptr)) {
                    handle_statement_declaration(*decl_int);
                } else if (auto* decl_float = dynamic_cast<dataflow_declaration<dataflow_type::FLOAT, stenv>*>(ptr)) {
                    handle_statement_declaration(*decl_float);
                } else if (auto* decl_bool = dynamic_cast<dataflow_declaration<dataflow_type::BOOL, stenv>*>(ptr)) {
                    handle_statement_declaration(*decl_bool);
                } else if (auto* assign_int = dynamic_cast<dataflow_assignment<dataflow_type::INT, stenv>*>(ptr)) {
                    handle_statement_assignment(*assign_int);
                } else if (auto* assign_float = dynamic_cast<dataflow_assignment<dataflow_type::FLOAT, stenv>*>(ptr)) {
                    handle_statement_assignment(*assign_float);
                } else if (auto* assign_bool = dynamic_cast<dataflow_assignment<dataflow_type::BOOL, stenv>*>(ptr)) {
                    handle_statement_assignment(*assign_bool);
                }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::INT>*>(ptr)){
                    handle_foreach(*foreach);
                }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::FLOAT>*>(ptr)){
                    handle_foreach(*foreach);
                }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::BOOL>*>(ptr)){
                    handle_foreach(*foreach);
                }else if constexpr(stenv == statement_env::SYSTEM){
                    if(auto* link = dynamic_cast<linking_statement*>(ptr)){
                        (*link).accept(*this);
                    }else if(auto* feeding_int_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT>*>(ptr)){
                        handle_feeding_statement(*feeding_int_l);
                    }else if(auto* feeding_float_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*>(ptr)){
                        handle_feeding_statement(*feeding_float_l);
                    }else if(auto* feeding_bool_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>(ptr)){
                        handle_feeding_statement(*feeding_bool_l);
                    }else if(auto* feeding_int_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT>*>(ptr)){
                        handle_feeding_statement(*feeding_int_p);
                    }else if(auto* feeding_float_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*>(ptr)){
                        handle_feeding_statement(*feeding_float_p);
                    }else if(auto* feeding_bool_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>(ptr)){
                        handle_feeding_statement(*feeding_bool_p);
                    }else if(auto* plugging = dynamic_cast<channel_plugging*>(ptr)){
                        (*plugging).accept(*this);
                    } else {
                        out() << "[WARNING] system statement type not handled\n";
                    }
                } else {
                    out() << "[WARNING] statement type not handled\n";
                }
            }, stt);
        }

        
        template<statement_env stenv>
        void handle_section_if(if_section<stenv>& node){
            out() << "<if_section>\n";
            std::string segment = "/@if_section";
            push_ast_path(segment);

            int if_index = 0;

            for(auto stt : node.get_statements()){
                out() << repeat("\t", nbTab) << "<if_statements\n";

                std::string if_segment = "/@if_statements." + std::to_string(if_index++);
                push_ast_path(if_segment);

                handle_statement<stenv>(stt);

                pop_ast_path(if_segment);

                out() << repeat("\t", nbTab) << "</if_statements>\n";
            }

            pop_ast_path(segment);
            out() << "</if_section>\n";
        }

        template<statement_env stenv>
        void handle_section_else(else_section<stenv>& node){
            out() << repeat("\t", nbTab) << "<else_section>\n";

            std::string segment = "/@else_section";
            push_ast_path(segment);

            int else_index = 0;

            for(auto stt : node.get_statements()){
                out() << repeat("\t", nbTab) << "<else_statements\n";

                std::string else_segment = "/@else_statements." + std::to_string(else_index++);
                push_ast_path(else_segment);

                handle_statement<stenv>(stt);

                pop_ast_path(else_segment);

                out() << repeat("\t", nbTab) << "</else_statements>\n";
            }

            pop_ast_path(segment);

            out() << repeat("\t", nbTab) << "</else_section>\n";
        }

        template<statement_env stenv>
        void handle_statement_if(if_statement<stenv>& node){
            writeAttribute("xsi:type",statement_type("if"));

            auto if_condition = node.get_condition();
            auto if_sect = node.get_if_section();

            handle_condition(if_condition);
            handle_section_if(if_sect);
        }

        template<statement_env stenv>
        void handle_statement_if_else(if_else_statement<stenv>& node){
            writeAttribute("xsi:type",statement_type("if_else"));
            
            auto if_condition = node.get_condition();
            auto if_sect = node.get_if_section();
            auto else_sect = node.get_else_section();

            handle_condition(if_condition);
            handle_section_if(if_sect);
            handle_section_else(else_sect);
        }

        
		template<statement_env stenv, dataflow_type dft>
		void handle_foreach(foreach_statement<stenv, dft>& node){
			constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;

			if constexpr(expenv == expression_env::SYSTEM){
				writeAttribute("xsi:type",statement_type("foreach", StatementFamily::System));
			}else{
				writeAttribute("xsi:type",statement_type("foreach"));
			}

			

			out() << ">\n" << repeat("\t", nbTab) << "<iterator\n" << repeat("\t", nbTab);

			auto iterator  = node.get_iterator();
			std::string iterator_name = iterator.get_variable().get_name();
			auto iterable = node.get_iterable();
			auto statements = node.get_statements();

			std::string iterator_path = get_ast_path() + "/@iterator/@variable";
			register_variable(iterator_name, iterator_path, "iterator");

			if constexpr(expenv == expression_env::SYSTEM){
				writeAttribute("xsi:type", statement_type(dft_to_string(dft)+"_declaration", StatementFamily::System));
			}else{
				writeAttribute("xsi:type", statement_type(dft_to_string(dft)+"_declaration"));
			}

			
			out() << ">\n" << repeat("\t", nbTab) << "<variable\n" << repeat("\t", nbTab);
			writeAttribute("name", iterator_name);
			out() << "/>\n" << repeat("\t", nbTab) << "</iterator>\n";

			out() << repeat("\t", nbTab) << "<iterable_expr\n" << repeat("\t", nbTab);

			std::visit([&](auto* itera){
				if(!itera){
					out() << "<!-- TODO ITERABLE -->\n";
					return;
				}

				using iterable_t = std::remove_pointer_t<decltype(itera)>;

				if constexpr(
					std::is_same_v<iterable_t, function<dataflow_type::INT, expenv>> ||
					std::is_same_v<iterable_t, function<dataflow_type::FLOAT, expenv>> ||
					std::is_same_v<iterable_t, function<dataflow_type::BOOL, expenv>>){
					visit(*itera);
				}else if constexpr(std::is_same_v<iterable_t, rvalue_variant<expenv>>){
					std::visit([&](auto* value){
						if(value){
							visit(*value);
						}else{
							out() << "<!-- TODO ITERABLE -->\n";
						}
					}, *itera);
				}else{
					out() << "<!-- TODO ITERABLE -->\n";
				}

			}, iterable);

			out() << repeat("\t", nbTab) << "</iterable_expr>\n";

			for(auto stt : statements){
				out() << repeat("\t", nbTab) << "<statements\n";
				handle_statement<stenv>(stt);
				out() << repeat("\t", nbTab) << "</statements>\n";
			}
		}

                
        void handle_outputs(std::vector<function_output_variant>& outputs, bool is_actuator = false){
            int output_index = 0;
            std::string name_balise = (is_actuator ? "actuator" : "outputs");

            std::vector<std::vector<std::string>> outputs_to_register;

            for(auto& output : outputs){
                std::visit([&](auto* outp){
                    out() << repeat("\t", nbTab) << "<" << name_balise <<"\n";

                    nbTab++;

                    std::string output_name = outp->get_name();
                    dataflow_type output_type = get_dataflow_type(outp);
                    std::string dft = dft_to_string(output_type);

                    std::string output_path = get_ast_path() + "/@"+ name_balise +"." + std::to_string(output_index++);

                    register_output(current_fname, output_name, output_path);

                    push_ast_path(output_path);

                    nbTab++;
                    out() << repeat("\t", nbTab);
                    if(is_actuator){
                        writeAttribute("xsi:type","chips.outputs.physical:"+dft+"_output");
                    }else{
                        writeAttribute("xsi:type","chips.outputs.logical:"+dft+"_output");
                    }
                    out() << "\n" << repeat("\t", nbTab);
                    writeAttribute("name",output_name);
                    out() << ">\n";
                    nbTab--;

                    out() << repeat("\t", nbTab) << "<expression\n";

                    for(auto expression : outp->get_expressions()){
                        std::visit([&](auto expr) {

                            using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

                            if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>>) {
                                // std::cerr << "OUTPUT BOOL EXPR" << std::endl;
                                binary_boolean_visit(*expr);
                            } else {
                                // std::cerr << "OUTPUT ARITH" << std::endl;
                                arithmetic_visit(*expr);
                            }

                            if(!only_one_child(*expr)){
                                out() << "</expression>\n";
                            }

                        }, expression);
                        break;
                    }

                    outputs_to_register.push_back({output_name, output_path, "output:"+dft});

                    pop_ast_path(output_path);
                    out() << repeat("\t", nbTab) << "</" << name_balise << ">\n";
                }, output);

                
            }
        }

		template<dataflow_type dft, expression_env expenv>
		void handle_binary_expression(rvalue<dft,expenv>* left, rvalue<dft,expenv>* right, const std::string& type){
			writeAttribute("xsi:type",get_op_prefix(expenv)+dft_to_string(dft)+":"+type);
			out() << ">\n";
		
			out() << repeat("\t", --nbTab) << "<left_operand\n";
			nbTab++;
			out() << repeat("\t", ++nbTab);
		
			if(left){
				// std::cerr << "left->accept()" << std::endl;
				arithmetic_visit(*left);
			}
		
			if(left && !only_one_child(*left)){
				out() << repeat("\t", nbTab) << "</left_operand>\n";
			}
		
			out() << repeat("\t", nbTab) << "<right_operand\n";
			nbTab++;
			out() << repeat("\t", ++nbTab);
		
			if(right){
				// std::cerr << "right->accept()" << std::endl;
				arithmetic_visit(*right);
			} 
		
			if(right && !only_one_child(*right)){
				out() << repeat("\t", nbTab) << "</right_operand>\n";
			}
		}

		template<dataflow_type dft, expression_env expenv>
		void handle_binary_boolean(rvalue<dft,expenv>* left, rvalue<dft,expenv>* right, const std::string& type){
			if(type == "and" || type == "or"){
				writeAttribute("xsi:type", get_op_prefix(expenv)+"bool:"+type);
			}else{
				writeAttribute("xsi:type", get_op_prefix(expenv)+"bool:"+type+"_"+dft_to_string(dft));
			}
			
			
			out() << ">\n" << repeat("\t", nbTab) << "<left_operand\n" << repeat("\t", nbTab);
		
			if(left){
				// std::cerr << "left->accept()" << std::endl;
				binary_boolean_visit(*left);
			}
		
			if(left && !only_one_child(*left)){
				out() << repeat("\t", nbTab) << "</left_operand>\n";
			}
		
			out() << repeat("\t", nbTab) << "<right_operand\n" << repeat("\t", nbTab);
		
			if(right){
				// std::cerr << "right->accept()" << std::endl;
				binary_boolean_visit(*right);
			}
		
			if(right && !only_one_child(*right)){
				out() << repeat("\t", nbTab) << "</right_operand>\n";
			}
		}

		template<dataflow_kind dfk, dataflow_type dft>
		void handle_feeding_statement(feeding_statement<dfk, dft>& node){
			out() << repeat("\t", nbTab);
			writeAttribute("xsi:type", statement_type("feeding_"+dfk_to_string<dfk>()+"_"+dft_to_string<dft>(), StatementFamily::System));
		
			eater<dfk, dft>& eat = node.get_eater();
			feeder<dfk, dft>* feed = node.get_feeder();
		
			visit(eat);
			visit(*feed);
		}
		
        template<dataflow_type dft, expression_env expenv>
        bool only_one_child(rvalue<dft,expenv>& node){
            if(dynamic_cast<direct<dft,expenv>*>(&node) ||  dynamic_cast<input*>(&node) || dynamic_cast<stop*>(&node) ||
               dynamic_cast<variable_contextual_expression<dft,expenv>*>(&node)){
                // std::cerr << "ONLY ONE CHILD" << std::endl;
                return true;
            }
            if(auto* var = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                // out() << "TAILLE DE VAR: " << var->get_index().size() << "\n";
                return var->get_index().empty();
            }
            if(auto* func = dynamic_cast<function<dft,expenv>*>(&node)){
                return func->get_parameters().empty();
            }
            // std::cerr << "NOT ONLY ONE CHILD" << std::endl;
            return false;
        }

        void dumpSymbolTable(){
            std::cout << "SYMBOL TABLE" << std::endl;
            for(const auto& [k, v] : m_symbol_table){
                std::cout << k << " (path: " << v.path << ", type:" << v.type << std::endl;
            }
            std::cout << "========PARAMETRE==========" << std::endl;
            for(const auto& [k1, v1] : function_parameters){
                for(const auto& [k2, v2] : v1){
                    std::cout << "fonction: " << k1 << " " << k2 << " " << v2 << std::endl; 
                }
            }
            std::cout << "========OUTPUTS==========" << std::endl;
            for(const auto& [k1, v1] : function_outputs){
                for(const auto& [k2, v2] : v1){
                    std::cout << "fonction: " << k1 << " " << k2 << " " << v2 << std::endl; 
                }
            }
            std::cout << "========CHANNELS==========" << std::endl;
            for(const auto& [k1, v1] : function_channels){
                for(const auto& [k2, v2] : v1){
                    std::cout << "fonction: " << k1 << " " << k2 << " " << v2 << std::endl; 
                }
            }
            std::cout << "==============" << std::endl;
        }

		//////////////////////////////////
		//////////////////////////////////
		//////////////////////////////////
		//////////////////////////////////
		// to implement visit methods 

		void visit(with_section&);

		void visit(init_section&);

		void visit(then_section&);
		
		void visit(collectiveops_section&);
		
		void visit(accumulator_definition&);

		void visit(object_definition&);
		
		void visit(logical_definition&);

		void visit(physical_definition&);
	
		void visit(channeled_output&);
	
		void visit(default_output&);
	
		void visit(target_output&);

		void visit(collective_function_definition&);

		template<dataflow_kind dfk, dataflow_type dft>
		void visit(function_parameter<dfk,dft>&);
		
		template<dataflow_type dft>
		void visit(collective_parameter<dft>&);
		
		template<dataflow_kind dfk, dataflow_type dft>
		void visit(function_output<dfk,dft>&);

		void visit(system_variable_block_expression<block_type::LOGICAL>&);
	
		void visit(system_variable_block_expression<block_type::PHYSICAL>&);
	
		void visit(system_variable_block_expression<block_type::OBJECT>&);

		template<dataflow_kind dfk, dataflow_type dft>
		void visit(eater<dfk,dft>&);

		template<dataflow_kind dfk, dataflow_type dft>
		void visit(feeder_block_expression<dfk,dft>&);

		void visit(channel_eater&);
	
		void visit(channel_feeder&);

		template<dataflow_kind dfk, dataflow_type dft>
		void visit(collective_cast<dfk,dft>&);

		template<dataflow_type dft, expression_env expenv> 
		void visit(direct<dft,expenv>&);

		template<dataflow_type dft, expression_env expenv> 
		void visit(class function<dft,expenv>&);
		
		template <dataflow_type dft, expression_env expenv>
		void visit(plus<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(minus<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(mult<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(chips::div<dft,expenv>&);

		template <expression_env expenv>
		void visit(chips::mod<expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(cast_as<dft,expenv>&);

		template <expression_env expenv, dataflow_type dft>
		void visit(gt<expenv,dft>&);

		template <expression_env expenv, dataflow_type dft>
		void visit(lt<expenv,dft>&);

		template <expression_env expenv, dataflow_type dft>
		void visit(geq<expenv,dft>&);

		template <expression_env expenv, dataflow_type dft>
		void visit(leq<expenv,dft>&);

		template <expression_env expenv>
		void visit(or_operator<expenv>&);

		template <expression_env expenv>
		void visit(and_operator<expenv>&);

		template <expression_env expenv>
		void visit(not_operator<expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(uminus_operator<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(eq<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(neq<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(variable_expression<dft,expenv>&);

		template <dataflow_type dft, expression_env expenv>
		void visit(variable_contextual_expression<dft,expenv>&);

		void visit(input&);

		void visit(stop&);

		void visit(preamble_section_node&);

		void visit(system_section_node&);

		void visit(program_node&);
		
		template<dataflow_type dft, statement_env stenv>
		void visit(dataflow_declaration<dft,stenv>&);

		template<dataflow_type dft, statement_env stenv> 
		void visit(dataflow_assignment<dft,stenv>&);

		template<statement_env stenv> 
		void visit(if_section<stenv>&);

		template<statement_env stenv> 
		void visit(else_section<stenv>&);

		template<statement_env stenv>
		void visit(if_statement<stenv>&);

		template<statement_env stenv>
		void visit(if_else_statement<stenv>&);

		template<statement_env stenv, dataflow_type dft>
		void visit(foreach_statement<stenv,dft>&);

		template<block_type bt>
		void visit(block_foreach_statement<bt>&);

		template<block_type bt>
		void visit(block_declaration<bt>&);

		void visit(channel_plugging&);

		template<dataflow_kind dfk, dataflow_type dft>
		void visit(feeding_statement<dfk,dft>&);

		void visit(linking_statement&);

		template<node_element ne>
		void visit(node_element_declaration<ne>&);

		template<expression_env expenv> 
		void visit(array<expenv>&);

		template<dataflow_type dft> 
		void visit(dataflow_primitive_variable<dft>&);

		template<dataflow_type dft> 
		void visit(contextual_variable<dft>&);

		template<dataflow_type dft> 
		void visit(dataflow_collective_variable<dft>&);

		template<block_type bt> 
		void visit(block_variable<bt>&);

		template<dataflow_type dft> 
		void visit(dataflow_system_variable<dft>&);
	};
}
