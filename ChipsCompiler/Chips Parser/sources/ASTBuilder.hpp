#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "ChipsBaseVisitor.h"
#include "ast_base.hpp"
#include "ast_lrxvalues.hpp"

#include <any>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include "cxxabi.h"

using namespace chips;


namespace ast_builder_detail {

    // Nom de type lisible pour les messages d'erreur
    inline std::string type_name(const std::type_info& ti) {
        int status;
        char* d = abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status);
        std::string r = (status == 0 && d) ? d : ti.name();
        free(d);
        return r;
    }

    // ── try_extract ───────────────────────────────────────────────────────────
    // Tente de récupérer shared_ptr<rvalue<DFT,EXPENV>> depuis un std::any.
    // Retourne nullptr si le type ne correspond pas.
    //
    // Pourquoi plusieurs tentatives ?
    //   std::any_cast est exact : il ne fait aucun upcast automatique.
    //   Un any{ shared_ptr<direct<INT,PRIM>> } ne se cast PAS vers
    //   shared_ptr<rvalue<INT,PRIM>> directement. Il faut tenter le type
    //   concret stocké puis upcast via static_pointer_cast.
    //   On utilise any_cast<T*> (pas de copie) pour les essais.
    template<dataflow_type DFT, expression_env EXPENV>
    std::shared_ptr<rvalue<DFT, EXPENV>> try_extract(const std::any& a) {

        // extraction des opérateurs où les opérandes ne sont que des numériques
        if constexpr(DFT != dataflow_type::BOOL){
            std::cout << "DFT != BOOL -> true" << std::endl;
            if(auto* p = std::any_cast<std::shared_ptr<direct<DFT,EXPENV>>>(&a)){
                std::cout << "direct" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<plus<DFT,EXPENV>>>(&a)){
                std::cout << "plus" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<minus<DFT,EXPENV>>>(&a)){
                std::cout << "minus" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<mult<DFT,EXPENV>>>(&a)){
                std::cout << "mult" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<chips::div<DFT,EXPENV>>>(&a)){
                std::cout << "div" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }

            if constexpr(DFT == dataflow_type::INT)
                if(auto* p = std::any_cast<std::shared_ptr<mod<EXPENV>>>(&a)){
                    std::cout << "mod" << std::endl;
                    return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
                }
        }

        // extractation des opérateurs qui sont de type booléens
        if constexpr(DFT == dataflow_type::BOOL){
            if(auto* p = std::any_cast<std::shared_ptr<direct<DFT,EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<lt<EXPENV, dataflow_type::INT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<lt<EXPENV, dataflow_type::FLOAT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<leq<EXPENV, dataflow_type::INT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<leq<EXPENV, dataflow_type::FLOAT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<gt<EXPENV, dataflow_type::INT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<gt<EXPENV, dataflow_type::FLOAT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<geq<EXPENV, dataflow_type::INT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<geq<EXPENV, dataflow_type::FLOAT>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
        }

        

        // Fallback : le any contient déjà shared_ptr<rvalue<DFT,EXPENV>>
        std::cout << "before any_cast of try_extract fallback" << std::endl;
        if (auto* p = std::any_cast<std::shared_ptr<rvalue<DFT,EXPENV>>>(&a))
            return *p;
        return nullptr;
    }

    // ── extract_as_node ───────────────────────────────────────────────────────
    // Helper global : extrait un shared_ptr<ast_node> depuis n'importe quel
    // std::any retourné par un visiteur, sans connaître le type template.
    // Utilisé par main.cpp (et tout code appelant externe).
    //
    // IMPORTANT — quelles combinaisons lister ici :
    //   Seulement celles réellement PRODUITES par les visiteurs du builder.
    //   Ajouter une ligne ici uniquement quand un visiteur produit ce type.
    //
    // BOOL exclu : plus<BOOL,*> est invalide (ChipsOperandToAstNumericType
    //   n'a pas de spécialisation BOOL — intentionnel, + n'est pas défini sur bool).
    //
    // SYSTEM exclu : rvalue<dft,SYSTEM> hérite de feeder<LOGICAL,dft> qui est
    //   incomplet ici (défini dans ast_system_specific.hpp, non inclus par ASTBuilder).
    inline std::shared_ptr<ast_node> extract_as_node(const std::any& a) {
        std::cout << "extract_as_node()" << std::endl;
        if(!a.has_value())
            return nullptr;

        #define TRY_UPCAST(DFT, EXPENV)                                     \
            if (auto p = try_extract<DFT, EXPENV>(a))                       \
                return std::static_pointer_cast<ast_node>(p);               \

        TRY_UPCAST(dataflow_type::INT,   expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::INT, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::INT, expression_env::SYSTEM)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::SYSTEM)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::SYSTEM)

        #undef TRY_UPCAST

        throw std::runtime_error(
            "extract_as_node : type inconnu dans le std::any : "
            + type_name(a.type())
            + ". Ajouter la combinaison dans extract_as_node si un nouveau "
              "visiteur produit ce type (sauf BOOL et SYSTEM, voir commentaire).");
    }

    // ── dispatch_numeric_binary ───────────────────────────────────────────────
    // Reçoit two std::any (résultats de sous-visiteurs).
    // Pour chaque combinaison numérique (DFT x EXPENV) :
    //   1. Tente try_extract sur left
    //   2. Si succès, tente le MÊME type sur right
    //      → succès : construit le nœud via Builder et retourne
    //      → échec  : erreur de type (les deux opérandes doivent être identiques)
    //   3. Si left ne correspond pas : combinaison suivante
    //
    // BOOL et SYSTEM exclus pour les mêmes raisons que extract_as_node.
    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_numeric_binary(
        const std::any& left_any,
        const std::any& right_any,
        const char* op_name)
    {
        std::cout << "dispatch_numeric_binary()" << std::endl;
        #define TRY_BINARY(DFT, EXPENV)                                         \
        {                                                                        \
            auto l = try_extract<DFT, EXPENV>(left_any);                        \
            if (l) {                                                             \
                auto r = try_extract<DFT, EXPENV>(right_any);                   \
                if (!r) {                                                        \
                    throw std::runtime_error(                                    \
                        std::string(op_name) + " : erreur de type — "           \
                        "operande gauche et droit incompatibles. "              \
                        "Les deux operandes doivent avoir le meme type. "       \
                        "Utilisez cast_as pour convertir explicitement.");       \
                }                                                                \
                return Builder<DFT, EXPENV>::build(std::move(l), std::move(r)); \
            }                                                                    \
        }

        TRY_BINARY(dataflow_type::INT,   expression_env::PRIMITIVE)
        TRY_BINARY(dataflow_type::FLOAT, expression_env::PRIMITIVE)
        TRY_BINARY(dataflow_type::INT, expression_env::COLLECTIVE)
        TRY_BINARY(dataflow_type::FLOAT, expression_env::COLLECTIVE)
        TRY_BINARY(dataflow_type::INT, expression_env::SYSTEM)
        TRY_BINARY(dataflow_type::FLOAT, expression_env::SYSTEM)

        #undef TRY_BINARY

        throw std::runtime_error(
            std::string(op_name) + " : type non valide pour un operateur numerique "
            "(BOOL non supporte, seuls INT et FLOAT sont valides).");
    }

    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_numeric_unary(
        const std::any& right_any,
        const char* op_name){
            std::cout << "dispatch_numeric_unary()" << std::endl;
            std::cout << type_name(right_any.type()) << std::endl;
            #define TRY_UNARY(DFT, EXPENV)                                         \
            {                                                                        \
                auto r = try_extract<DFT, EXPENV>(right_any);                   \
                if (!r) {                                                        \
                    throw std::runtime_error(                                    \
                        std::string(op_name) + " : erreur de type — "           \
                        "operande gauche et droit incompatibles. "              \
                        "Les deux operandes doivent avoir le meme type. "       \
                        "Utilisez cast_as pour convertir explicitement.");       \
                }                                                                \
                return Builder<DFT, EXPENV>::build(std::move(r)); \
            }

            TRY_UNARY(dataflow_type::INT,   expression_env::PRIMITIVE)
            TRY_UNARY(dataflow_type::FLOAT, expression_env::PRIMITIVE)
            TRY_UNARY(dataflow_type::INT, expression_env::COLLECTIVE)
            TRY_UNARY(dataflow_type::FLOAT, expression_env::COLLECTIVE)
            TRY_UNARY(dataflow_type::INT, expression_env::SYSTEM)
            TRY_UNARY(dataflow_type::FLOAT, expression_env::SYSTEM)

            #undef TRY_UNARY

            throw std::runtime_error(
                std::string(op_name) + " : type non valide pour un operateur numerique "
                "(BOOL non supporte, seuls INT et FLOAT sont valides).");
        }

    // ── Builders par opérateur ────────────────────────────────────────────────
    // Pour ajouter un opérateur : écrire un Builder + un visiteur d'une ligne.

    template<dataflow_type DFT, expression_env EXPENV>
    struct PlusBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            std::cout << "PlusBuilder.build()" << std::endl;
            return std::make_shared<plus<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct SubBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<minus<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct NegateBuilder {
        static std::any build(std::shared_ptr<rvalue<DFT,EXPENV>> r){
            std::cout << "negateBuilder()" << std::endl;
            if constexpr(DFT == dataflow_type::FLOAT){
                auto zero = std::make_shared<direct<DFT,EXPENV>>(0.0);
                return std::make_shared<minus<DFT,EXPENV>>(std::move(zero), std::move(r));
            }
            if constexpr(DFT == dataflow_type::INT){
                auto zero = std::make_shared<direct<DFT,EXPENV>>(0);
                return std::make_shared<minus<DFT,EXPENV>>(std::move(zero), std::move(r));
            }
            auto zero = std::make_shared<direct<DFT,EXPENV>>(0);
            return std::make_shared<minus<DFT,EXPENV>>(std::move(zero), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct MultBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<mult<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct DivBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<chips::div<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct ModBuilder;

    template<expression_env EXPENV>
    struct ModBuilder<dataflow_type::INT,EXPENV> {
        static std::any build(
            std::shared_ptr<rvalue<dataflow_type::INT, EXPENV>> l,
            std::shared_ptr<rvalue<dataflow_type::INT, EXPENV>> r)
        {
            return std::make_shared<mod<EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct LTBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<lt<EXPENV,DFT>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct LEQBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<leq<EXPENV,DFT>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct GTBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<gt<EXPENV,DFT>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct GEQBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<geq<EXPENV,DFT>>(std::move(l), std::move(r));
        }
    };

} // namespace ast_builder_detail

class ASTBuilder : public ChipsBaseVisitor {
    public:

    // Fonction pour tester
    std::any visitProgram(ChipsParser::ProgramContext* ctx) override {
        std::cout<< "nb preambles" <<ctx->preamble().size()<<std::endl;
        return std::any(NULL);
    }

    // expr
    std::any visitLT(ChipsParser::LTContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LTBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "LT");
    }

    std::any visitLEQ(ChipsParser::LEQContext* ctx) override {
        // INT
        auto left_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_int && right_int)
            return std::make_shared<leq<expression_env::PRIMITIVE, dataflow_type::INT>>(left_int, right_int);

        // FLOAT
        auto left_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_float && right_float)
            return std::make_shared<leq<expression_env::PRIMITIVE, dataflow_type::FLOAT>>(left_float, right_float);

        throw std::runtime_error("LEQ : opérandes doivent être INT ou FLOAT (même type)");
    }

    std::any visitGT(ChipsParser::GTContext* ctx) override {
        // INT
        auto left_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_int && right_int)
            return std::make_shared<gt<expression_env::PRIMITIVE, dataflow_type::INT>>(left_int, right_int);

        // FLOAT
        auto left_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_float && right_float)
            return std::make_shared<gt<expression_env::PRIMITIVE, dataflow_type::FLOAT>>(left_float, right_float);

        throw std::runtime_error("GT : opérandes doivent être INT ou FLOAT (même type)");
    }

    std::any visitGEQ(ChipsParser::GEQContext* ctx) override {
        // INT
        auto left_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_int && right_int)
            return std::make_shared<geq<expression_env::PRIMITIVE, dataflow_type::INT>>(left_int, right_int);

        // FLOAT
        auto left_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if (left_float && right_float)
            return std::make_shared<geq<expression_env::PRIMITIVE, dataflow_type::FLOAT>>(left_float, right_float);

        throw std::runtime_error("GEQ : opérandes doivent être INT ou FLOAT (même type)");
    }

    std::any visitEQ(ChipsParser::EQContext* ctx) override {
        // INT
        auto left_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_int && right_int)
            return std::make_shared<eq<dataflow_type::INT, expression_env::PRIMITIVE>>(left_int, right_int);

        // FLOAT
        auto left_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_float && right_float)
            return std::make_shared<eq<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(left_float, right_float);

        // BOOL
        auto left_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_bool && right_bool)
            return std::make_shared<eq<dataflow_type::BOOL, expression_env::PRIMITIVE>>(left_bool, right_bool);

        throw std::runtime_error("EQ : opérandes doivent être INT, FLOAT ou  BOOL (même type)");
    }

    std::any visitNEQ(ChipsParser::NEQContext* ctx) override {
        // INT
        auto left_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_int = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_int && right_int)
            return std::make_shared<neq<dataflow_type::INT, expression_env::PRIMITIVE>>(left_int, right_int);

        // FLOAT
        auto left_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_float = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_float && right_float)
            return std::make_shared<neq<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(left_float, right_float);

        // BOOL
        auto left_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_bool && right_bool)
            return std::make_shared<neq<dataflow_type::BOOL, expression_env::PRIMITIVE>>(left_bool, right_bool);

        throw std::runtime_error("NEQ : opérandes doivent être INT, FLOAT ou  BOOL (même type)");
    }

    std::any visitAND(ChipsParser::ANDContext* ctx) override {
        auto left_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_bool && right_bool)
            return std::make_shared<and_operator<expression_env::PRIMITIVE>>(left_bool, right_bool);

        throw std::runtime_error("AND : opérandes doivent être BOOL (même type)");
    }

    std::any visitOR(ChipsParser::ORContext* ctx) override {
        auto left_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr0()));
        auto right_bool = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(visit(ctx->expr()));
        if(left_bool && right_bool)
            return std::make_shared<or_operator<expression_env::PRIMITIVE>>(left_bool, right_bool);

        throw std::runtime_error("OR : opérandes doivent être BOOL (même type)");
    }


    std::any visitPLUS(ChipsParser::PLUSContext* ctx) override {
        // std::cout << "visitPLUS()" << std::endl;
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "PLUS");
    }

    std::any visitSUB(ChipsParser::SUBContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "SUB");
    }

    std::any visitNegate(ChipsParser::NegateContext* ctx) override {
        std::cout << "visitNegate" << std::endl;
        return ast_builder_detail::dispatch_numeric_unary<ast_builder_detail::NegateBuilder>(
            visit(ctx->expr1()), "Negate");
    }


    std::any visitMULT(ChipsParser::MULTContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::MultBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "MULT");
    }

    std::any visitDIV(ChipsParser::DIVContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::DivBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "DIV");
    }

    std::any visitMOD(ChipsParser::MODContext* ctx) override {
        auto left = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr2()));
        auto right = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr1()));
        if (!left || !right) {
            throw std::runtime_error("MOD : opérandes doivent être des entiers (INT/PRIMITIVE)");
        }
        return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::PRIMITIVE>::build(left, right);
    }

    // atom
    std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx) override {
        std::cout << "visitIntLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(std::stoll(ctx->INT()->getText()));
    }

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) override {
        std::cout << "visitFloatLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(std::stod(ctx->FLOAT()->getText()));
    }

    std::any visitBoolLiteral(ChipsParser::BoolLiteralContext* ctx) override {
        std::string text = ctx->BOOL()->getText();
        bool value = (text == "true");
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(value);
    }

    std::any visitParens(ChipsParser::ParensContext* ctx) override {
        auto result = visit(ctx->expr());

        // Essayez pour INT, FLOAT, BOOL
        if (auto v = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);
        else if (auto v = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);
        else if (auto v = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);

        return result;
    }

    // pass to children
    std::any visitPassExpr0(ChipsParser::PassExpr0Context* ctx) override {
        return visit(ctx->expr0());
    }

    std::any visitPassExpr1(ChipsParser::PassExpr1Context* ctx) override {
        return visit(ctx->expr1());
    }

    std::any visitPassExpr2(ChipsParser::PassExpr2Context* ctx) override {
        return visit(ctx->expr2());
    }

    private:

        void print_any_type(const std::any& a){
            std::cout << "Type: " << a.type().name();
            int status;
            char* demangled = abi::__cxa_demangle(a.type().name(), 0, 0, &status);
            if(status == 0 && demangled){
                std::cout << " (" << demangled << ")";
                free(demangled);
            }
            std::cout << std::endl;
        }
};

#endif