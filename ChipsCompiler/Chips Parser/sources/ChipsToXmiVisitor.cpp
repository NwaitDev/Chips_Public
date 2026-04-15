#include "ChipsToXmiVisitor.hpp"
#include "ast_definitions.hpp"

#include "ast_builder_details.hpp"

#define UNUSED(x) (void)(x)



namespace chips {

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

void ChipsToXmiVisitor::visit(program_node& node){
    auto preamble = node.get_preamble();
    auto system = node.get_system();
    std::cerr << "PREAMBLE SIZE: " << preamble.get_definitions().size() << std::endl;
    std::cerr << "SYSTEM SIZE: " << system.get_statements().size() << std::endl;
    if(!preamble.get_definitions().empty()){
        out() << repeat("\t", nbTab) << "<preamble>\n";
        nbTab++;
        preamble.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</preamble>\n";
    }
    if(!system.get_statements().empty()){
        out() << repeat("\t", nbTab) << "<system>\n";
        nbTab++;
        system.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</system>\n";
    }
}

void ChipsToXmiVisitor::visit(system_section_node& node){
    out() << "<!-- TODO -->\n";
}

void ChipsToXmiVisitor::visit(preamble_section_node& node){
    for(auto definition : node.get_definitions()){
        out() << repeat("\t", nbTab) << "<definitions\n";
        if(auto* logical = std::get_if<logical_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "logical";
        }else if(auto* physical = std::get_if<physical_definition*>(&definition)){
            nbTab++;
            if(*physical){
                std::cout << ast_builder_detail::type_name(std::any{physical}.type()) << std::endl;
                (*physical)->accept(*this);
            }
            nbTab--;

        }else if(auto* object = std::get_if<object_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "object";
        }else if(auto* collective = std::get_if<collective_function_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "collective";
        }
        out() << repeat("\t", nbTab) << "</definitions>\n";
    }
}

void ChipsToXmiVisitor::visit(physical_definition& node){

    // Enregistrer la définition physique dans la table des symboles
    // Le chemin est : //@preamble/@definitions.X (déterminé par le contexte d'appel)
    register_variable(node.get_name(), get_ast_path(), "physical");

    // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
    int def_index = 0;
    std::string path = get_ast_path();
    size_t pos = path.rfind("@definitions.");
    if(pos != std::string::npos){
        try{
            def_index = std::stoi(path.substr(pos + 13));
        }catch(...){
            def_index = 0;
        }
    }

    // Register the definition in the definitions table
    register_definition(node.get_name(), "physical", get_ast_path(), def_index);
    m_current_definition = node.get_name();

    std::cerr << "[DEBUG] Physical definition '" << node.get_name() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    nbTab++;
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", "definitions:physical_definition");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", node.get_name());
    out() << ">\n";
    nbTab--;

    // Enregistrer les paramètres (sensors, actuators, etc.) dans la table des symboles
    int sensor_index = 0;
    for(auto& param : node.get_sensors()){
        if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::INT);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                sensor_index++;
            }
        }else if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::FLOAT);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                sensor_index++;
            }
        }else if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::BOOL);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                sensor_index++;
            }
        }
    }

    auto with = node.get_with_section();
    if(!with.get_statements().empty()){
        push_ast_path("/@with");
        out() << repeat("\t", nbTab) << "<with>\n";
        nbTab++;
        with.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</with>\n";
        pop_ast_path("/@with");
    }
}

void ChipsToXmiVisitor::visit(with_section& node){
    for(auto& statement : node.get_statements()){
        out() << repeat("\t", nbTab) << "<statements\n";
        if(auto* if_stt = std::get_if<node_statement<recurring_statement::IF>*>(&statement)){
            out() << ("<!-- TODO IF NODE XMI -->\n");
        }else if(auto* foreach = std::get_if<node_statement<recurring_statement::FOREACH>*>(&statement)){
            out() << ("<!-- TODO FOREACH NODE XMI-->\n");
        }else if(auto* channel = std::get_if<node_element_declaration<node_element::CHANNEL>*>(&statement)){
            // out() << ("<!-- TODO CHANNEL NODE XMI-->\n");

            auto node_channel = *channel;

            std::string type_id = node_channel->get_variable();
            std::string name = node_channel->get_name();
            std::string type = statement_type("channel_declaration", StatementFamily::Node);

            // Enregistrer le channel dans la table des symboles
            // Le chemin du channel est juste get_ast_path() car on est déjà dans /@with/@statements.X
            register_variable(name, get_ast_path(), "channel");

            // Also register in the current definition if we're in one
            if (!m_current_definition.empty()) {
                register_definition_variable(m_current_definition, name, get_ast_path(), "channel");
            }

            std::cerr << "[DEBUG] Channel '" << name << "' enregistré avec le chemin: " << get_ast_path() << std::endl;

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type", type);
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("name", name+"_"+toLower(type_id));
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("type_identifier", type_id);
            out() << "/>\n";
            nbTab--;

        }else if(auto* ctx_int = std::get_if<node_element_declaration<node_element::CONTEXTUAL_INT>*>(&statement)){
            auto node_ctx = *ctx_int;

            std::string identifier = node_ctx->get_name();

            // Enregistrer le ctx dans la table des symboles
            // Le chemin du ctx est juste get_ast_path() car on est déjà dans /@with/@statements.X
            register_variable(identifier, get_ast_path(), "ctx");

            // Also register in the current definition if we're in one
            if (!m_current_definition.empty()) {
                register_definition_variable(m_current_definition, identifier, get_ast_path(), "ctx");
            }

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type", "contextual_int_declaration");
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("identifier", identifier);
            out() << "/>\n";
            // nbTab--;

            out() << repeat("\t", nbTab) << "<variable\n";
            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("name", identifier);
            out() << "/>\n"; 
            nbTab--;
            nbTab--;

        }else if(auto* ctx_float = std::get_if<node_element_declaration<node_element::CONTEXTUAL_FLOAT>*>(&statement)){
            out() << ("<!-- TODO CTX FLOAT NODE XMI-->\n");
        }else if(auto* ctx_bool = std::get_if<node_element_declaration<node_element::CONTEXTUAL_BOOL>*>(&statement)){
            out() << ("<!-- TODO CTX BOOL NODE XMI-->\n");
        }
    }
    out() << repeat("\t", nbTab) << "</statements>\n";
}

void ChipsToXmiVisitor::visit(logical_definition& node){
    out() << "<!-- TODO logical -->\n";
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

ChipsToXmiVisitor::StatementFamily ChipsToXmiVisitor::detect_statement_family() const
{
    const std::string &path = m_current_ast_path;

    if (path.find("/@system") != std::string::npos)
    {
        return StatementFamily::System;
    }
    if (path.find("/@operations") != std::string::npos)
    {
        return StatementFamily::Collective;
    }
    if (path.find("/@having") != std::string::npos)
    {
        return StatementFamily::Implementation;
    }
    if (path.find("/@with") != std::string::npos)
    {
        return StatementFamily::Node;
    }
    if (path.find("/@init") != std::string::npos || path.find("/@then") != std::string::npos)
    {
        return StatementFamily::Primitive;
    }

    return StatementFamily::Primitive;
}

std::string ChipsToXmiVisitor::statement_prefix(StatementFamily family) const
{
    if (family == StatementFamily::Auto)
    {
        family = detect_statement_family();
    }

    switch (family)
    {
    case StatementFamily::System:
        return "chips.statements.system";
    case StatementFamily::Node:
        return "chips.statements.node";
    case StatementFamily::Collective:
        return "chips.statements.collective";
    case StatementFamily::Implementation:
        return "chips.statements.implementation";
    case StatementFamily::Primitive:
    case StatementFamily::Auto:
    default:
        return "chips.statements.primitive";
    }
}

std::string ChipsToXmiVisitor::statement_type(const std::string &suffix, StatementFamily family) const
{
    return statement_prefix(family) + ":" + suffix;
}

void ChipsToXmiVisitor::report_semantic_error(const std::string &message)
{
    m_semantic_errors.push_back(message);
    std::cerr << "[SEMANTIC ERROR] " << message << std::endl;
}