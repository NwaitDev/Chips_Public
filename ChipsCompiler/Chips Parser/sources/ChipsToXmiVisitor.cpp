#include "ChipsToXmiVisitor.hpp"
#include "ast_definitions.hpp"

#define UNUSED(x) (void)(x)



namespace chips {

    std::string expenv_to_string(expression_env env){
        switch(env){
            case expression_env::PRIMITIVE: return "primitive";
            case expression_env::COLLECTIVE: return "collective";
            case expression_env::SYSTEM: return "system";
        }
        return "unknown";
    }

    bool is_system_context(expression_env env){
        return env == expression_env::SYSTEM;
    } 

    std::string get_op_prefix(expression_env env){
        if(is_system_context(env)) return "chips.rvalues.datalow.operators.";
        return "chips.rvalues.primitive.operators.";
    }

    
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(mod<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(mod<" << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+"int:mod");
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dataflow_type::INT,expenv>*>(left) || 
       dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(left) ||
       dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dataflow_type::INT,expenv>*>(right) ||
       dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(right) ||
       dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(direct<dft, expenv>& node){
    UNUSED(node);
    std::cerr << "[DEBUG Visitor] visit(direct<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << ")" << std::endl;
    writeAttribute("            xsi:type","chips.rvalues."+expenv_to_string(expenv)+":direct_"+dft_to_string<dft>());
    out() << "\n";
    if constexpr(dft == dataflow_type::BOOL){
        writeAttribute("            value", node.get_value() ? "true" : "false");
    }else{
        writeAttribute("            value", std::to_string(node.get_value()));
    }
    
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(chips::div<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(div<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":div");
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(mult<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(mult<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":mult");
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(minus<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(minus<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":minus");
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(uminus_operator<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(uminus_operator<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":minus");
    out() << ">\n";
    
    auto right = node.get_rhs();

    out() << "              <left_operand\n";
    writeAttribute("                xsi:type", "chips.rvalues."+expenv_to_string(expenv)+":direct_"+dft_to_string<dft>());
    out() << "/>\n";


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(plus<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(plus<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":plus");
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(cast_as<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(cast_as<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":cast_as_"+dft_to_string<dft>());
    out() << ">\n";

    auto numeric = node.get_cast();
    out() << "            <numeric\n";

    if(numeric){
        // std::cerr << "arithmeric_visit (numeric)" << std::endl;

        if constexpr(dft == dataflow_type::INT){
            void* raw = dynamic_cast<void*>(numeric); // pointe vers l'objet réel
            auto* n = static_cast<rvalue<dataflow_type::FLOAT, expenv>*>(
                dynamic_cast<rvalue<dataflow_type::FLOAT, expenv>*>(
                    reinterpret_cast<rvalue<dataflow_type::FLOAT, expenv>*>(raw)
                )
            );
            arithmetic_visit(*n);
            if(dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(n)){
                out() << "/>\n";
            }else{
                out() << "              </numeric>\n";
            }
        }else if constexpr(dft == dataflow_type::FLOAT){
            void* raw = dynamic_cast<void*>(numeric); // pointe vers l'objet réel
            auto* n = static_cast<rvalue<dataflow_type::INT, expenv>*>(
                dynamic_cast<rvalue<dataflow_type::INT, expenv>*>(
                    reinterpret_cast<rvalue<dataflow_type::INT, expenv>*>(raw)
                )
            );
            arithmetic_visit(*n);
            if(dynamic_cast<direct<dataflow_type::INT,expenv>*>(n)){
                out() << "/>\n";
            }else{
                out() << "              </numeric>\n";
            }
        }
    }
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(gt<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(gt<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":gt_"+dft_to_string<dft>());
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(geq<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(geq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":geq_"+dft_to_string<dft>());
    out() << ">\n";
    
    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(lt<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(lt<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":lt_"+dft_to_string<dft>());
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(leq<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(leq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":leq_"+dft_to_string<dft>());
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(eq<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(neq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":eq_"+dft_to_string<dft>());
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        binary_boolean_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(neq<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(neq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+dft_to_string<dft>()+":neq_"+dft_to_string<dft>());
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        binary_boolean_visit(*left);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    } 

    if(dynamic_cast<direct<dft,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(or_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(or_operator<" << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+"bool:or");
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        binary_boolean_visit(*left);
    } 

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    } 

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(and_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(and_operator<" << expenv_to_string(expenv) << std::endl; 
    writeAttribute("            xsi:type", get_op_prefix(expenv)+"bool:and");
    out() << ">\n";

    auto left = node.get_lhs();
    auto right = node.get_rhs();

    out() << "              <left_operand\n";

    if(left){
        std::cerr << "left->accept()" << std::endl;
        binary_boolean_visit(*left);
    } 

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(left)){
        out() << "/>\n";
    }else{
        out() << "              </left_operand>\n";
    }


    out() << "              <right_operand\n";

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    } 

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(right)){
        out() << "/>\n";
    }else{
        out() << "              </right_operand>\n";
    }
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(not_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(not_operator<" << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+"bool:not");
    out() << ">\n";

    auto operand = node.get_lhs();

    out() << "              <operand\n";

    if(operand){
        binary_boolean_visit(*operand);
    }

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(operand)){
        out() << "/>\n";
    }else{
        out() << "              </operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(rvalue<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(rvalue<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    out() << "          <rvalue\n";

    if constexpr(dft != dataflow_type::BOOL){
        arithmetic_visit(node);
    }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
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
    }else if(auto* p = dynamic_cast<or_operator<expenv>*>(&node)){
        visit(*p);
    }else if(auto* p = dynamic_cast<and_operator<expenv>*>(&node)){
        visit(*p);
    }else if(auto* p = dynamic_cast<not_operator<expenv>*>(&node)){
        visit(*p);
    }

    if(auto* p = dynamic_cast<direct<dft,expenv>*>(&node)){
        // std::cerr << "cast rvalue -> direct" << std::endl;
        visit(*p);
    }

    out() << "          </rvalue>\n";
}

void ChipsToXmiVisitor::visit(ast_node& node){
    UNUSED(node);
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // out() << "    <!-- ast_node générique -->\n";

    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node))
        visit(*r);

    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
    //     visit(*pl);
    //TODO: regarder pour regler ce probleme
}


void ChipsToXmiVisitor::writeAttribute(const std::string& name, const std::string& value){
    std::string normalized = name;
    while (!normalized.empty() && (normalized.front() == ' ' || normalized.front() == '\t')){
        normalized.erase(normalized.begin());
    }

    if(normalized == "xsi:type"){
        ensure_namespace_for_type(value);
    }
    out() << " " << name << "=\"" << value << "\"";
}

void ChipsToXmiVisitor::ensure_namespace_for_prefix(const std::string& ns_prefix){
    if (ns_prefix.empty()){
        return;
    }

    std::string suffix = ns_prefix;
    if (suffix.rfind("chips.", 0) == 0){
        suffix = suffix.substr(6);
    }

    size_t pos = 0;
    while ((pos = suffix.find('.', pos)) != std::string::npos){
        suffix.replace(pos, 1, "/");
        pos++;
    }

    std::string url = suffix.empty() || suffix[0] != '/'
                          ? "http://chips/" + suffix
                          : "http://chips" + suffix;
    m_writer.add_namespace_if_needed(ns_prefix, url);
}

void ChipsToXmiVisitor::ensure_namespace_for_type(const std::string& type_value){
    size_t colon_pos = type_value.find(':');
    if (colon_pos == std::string::npos){
        return;
    }
    ensure_namespace_for_prefix(type_value.substr(0, colon_pos));
}