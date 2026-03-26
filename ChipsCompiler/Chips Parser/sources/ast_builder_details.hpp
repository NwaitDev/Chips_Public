#ifndef AST_BUILDER_DETAILS
#define AST_BUILDER_DETAILS

#include "ChipsBaseVisitor.h"
#include "ast_base.hpp"
#include "ast_program.hpp"
#include "ast_lrxvalues.hpp"
#include "ast_statements.hpp"
#include "ast_variables.hpp"

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
            // std::cout << "DFT != BOOL -> true" << std::endl;
            if(auto* p = std::any_cast<std::shared_ptr<direct<DFT,EXPENV>>>(&a)){
                // std::cout << "direct" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<plus<DFT,EXPENV>>>(&a)){
                // std::cout << "plus" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<minus<DFT,EXPENV>>>(&a)){
                // std::cout << "minus" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<uminus_operator<DFT,EXPENV>>>(&a)){
                // std::cout << "uminus" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<mult<DFT,EXPENV>>>(&a)){
                // std::cout << "mult" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }
            if(auto* p = std::any_cast<std::shared_ptr<chips::div<DFT,EXPENV>>>(&a)){
                // std::cout << "div" << std::endl;
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            }

            if(auto* p = std::any_cast<std::shared_ptr<cast_as<DFT,EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if constexpr(DFT == dataflow_type::INT)
                if(auto* p = std::any_cast<std::shared_ptr<mod<EXPENV>>>(&a)){
                    // std::cout << "mod" << std::endl;
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

            if(auto* p = std::any_cast<std::shared_ptr<eq<dataflow_type::INT, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<eq<dataflow_type::FLOAT, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<eq<dataflow_type::BOOL, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<neq<dataflow_type::INT, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<neq<dataflow_type::FLOAT, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
            if(auto* p = std::any_cast<std::shared_ptr<neq<dataflow_type::BOOL, EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<and_operator<EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<or_operator<EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);

            if(auto* p = std::any_cast<std::shared_ptr<not_operator<EXPENV>>>(&a))
                return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
        }

        

        // Fallback : le any contient déjà shared_ptr<rvalue<DFT,EXPENV>>
        // std::cout << "before any_cast of try_extract fallback" << std::endl;
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
        // std::cout << "extract_as_node()" << std::endl;
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

        // dataflow_declaration DEFINITION
        if(auto* p = std::any_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>*>(p),
                [](ast_node*){}
            );
        if(auto* p = std::any_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>*>(p),
                [](ast_node*){}
            );
        if(auto* p = std::any_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>*>(p),
                [](ast_node*){}
            );

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
    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_numeric_binary(
        const std::any& left_any,
        const std::any& right_any,
        const char* op_name)
    {
        // std::cout << "dispatch_numeric_binary()" << std::endl;
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
    std::any dispatch_boolean_binary(
        const std::any& left_any,
        const std::any& right_any,
        const char* op_name)
    {
        
        #define TRY_BINARY(EXPENV)                                         \
        {                                                                        \
            auto l = try_extract<dataflow_type::BOOL, EXPENV>(left_any);         \
            if (l) {                                                             \
                auto r = try_extract<dataflow_type::BOOL, EXPENV>(right_any);    \
                if (!r) {                                                        \
                    throw std::runtime_error(                                    \
                        std::string(op_name) + " : erreur de type — "           \
                        "operande gauche et droit incompatibles. "              \
                        "Les deux operandes doivent avoir le meme type. "       \
                        "Utilisez cast_as pour convertir explicitement.");       \
                }                                                                \
                std::cout<<"builder !!!\n";\
                return Builder<dataflow_type::BOOL, EXPENV>::build(std::move(l), std::move(r)); \
            }                                                                    \
        }

        TRY_BINARY(expression_env::PRIMITIVE)
        TRY_BINARY(expression_env::COLLECTIVE)
        TRY_BINARY(expression_env::SYSTEM)

        #undef TRY_BINARY

        #define ITSAWHAT(DFT,EXPENV,TXT) \
        if(try_extract<DFT, EXPENV>(left_any)) throw std::runtime_error(TXT);

        ITSAWHAT(dataflow_type::FLOAT,expression_env::PRIMITIVE,"Its a float");
        ITSAWHAT(dataflow_type::FLOAT,expression_env::COLLECTIVE,"Its a float");
        ITSAWHAT(dataflow_type::FLOAT,expression_env::SYSTEM,"Its a float");
        ITSAWHAT(dataflow_type::INT,expression_env::PRIMITIVE,"Its a int");
        ITSAWHAT(dataflow_type::INT,expression_env::COLLECTIVE,"Its a int");
        ITSAWHAT(dataflow_type::INT,expression_env::SYSTEM,"Its a int");
        
        #undef ITSAWHAT

        throw std::runtime_error(
            std::string(op_name) + " : type non valide pour un booleen "
            "(INT et FLOAT non supportes, seul BOOL est valide).");
    }

    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_binary(
        const std::any& left_any,
        const std::any& right_any,
        const char* op_name){
            // std::cout << "dispatch_numeric_binary()" << std::endl;
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
            TRY_BINARY(dataflow_type::BOOL, expression_env::PRIMITIVE)
            TRY_BINARY(dataflow_type::INT, expression_env::COLLECTIVE)
            TRY_BINARY(dataflow_type::FLOAT, expression_env::COLLECTIVE)
            TRY_BINARY(dataflow_type::BOOL, expression_env::COLLECTIVE)
            TRY_BINARY(dataflow_type::INT, expression_env::SYSTEM)
            TRY_BINARY(dataflow_type::FLOAT, expression_env::SYSTEM)
            TRY_BINARY(dataflow_type::BOOL, expression_env::SYSTEM)

            #undef TRY_BINARY

            throw std::runtime_error(
                std::string(op_name) + " : type non valide pour un operateur comparaison.");
        }

    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_numeric_unary(
        const std::any& right_any,
        const char* op_name){
            // std::cout << "dispatch_numeric_unary()" << std::endl;
            // std::cout << type_name(right_any.type()) << std::endl;
            #define TRY_UNARY(DFT, EXPENV)                                         \
            {                                                                        \
                auto r = try_extract<DFT, EXPENV>(right_any);                   \
                if (r) {                                                        \
                    return Builder<DFT, EXPENV>::build(std::move(r)); \
                }                                                                \
            }                                                                   \

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

    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_boolean_unary(
        const std::any& right_any,
        const char* op_name){
            // std::cout << "dispatch_numeric_unary()" << std::endl;
            // std::cout << type_name(right_any.type()) << std::endl;
            #define TRY_UNARY(DFT, EXPENV)                                         \
            {                                                                        \
                auto r = try_extract<DFT, EXPENV>(right_any);                   \
                if (r) {                                                        \
                    return Builder<DFT, EXPENV>::build(std::move(r)); \
                }                                                                \
            }                                                                   \

            TRY_UNARY(dataflow_type::BOOL,   expression_env::PRIMITIVE)
            TRY_UNARY(dataflow_type::BOOL, expression_env::COLLECTIVE)
            TRY_UNARY(dataflow_type::BOOL, expression_env::SYSTEM)

            #undef TRY_UNARY

            throw std::runtime_error(
                std::string(op_name) + " : type non valide pour un operateur comparaison unaire.");
        }

    // ── Builders par opérateur ────────────────────────────────────────────────
    // Pour ajouter un opérateur : écrire un Builder + un visiteur d'une ligne.

    template<dataflow_type DFT, expression_env EXPENV>
    struct PlusBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            // std::cout << "PlusBuilder.build()" << std::endl;
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
            // std::cout << "negateBuilder()" << std::endl;
            return std::make_shared<uminus_operator<DFT,EXPENV>>(std::move(r));
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

    template<dataflow_type DFT, expression_env EXPENV>
    struct EQBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<eq<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct NEQBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<neq<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct ANDBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<and_operator<EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct ORBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> l,
            std::shared_ptr<rvalue<DFT,EXPENV>> r)
        {
            return std::make_shared<or_operator<EXPENV>>(std::move(l), std::move(r));
        }
    };

    template<dataflow_type DFT, expression_env EXPENV>
    struct NOTBuilder {
        static std::any build(
            std::shared_ptr<rvalue<DFT,EXPENV>> o)
        {
            return std::make_shared<not_operator<EXPENV>>(std::move(o));
        }
    };

} // namespace ast_builder_detail


#endif