#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "ChipsBaseVisitor.h"
#include "forward_declarations.hpp"
#include "ast_lrxvalues.hpp"

#include <any>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include "cxxabi.h"

using namespace chips;

// ─────────────────────────────────────────────────────────────────────────────
// Stratégie de stockage :
//   Les visit* stockent le shared_ptr<ConcreteType> CONCRET dans le std::any.
//   Ex: visitIntLiteral  → any{ shared_ptr<direct<INT,PRIM>> }
//       visitPLUS        → any{ shared_ptr<plus<INT,PRIM>>   }
//
//   Cela préserve le type template exact à travers tout l'arbre.
//   Pour en extraire un shared_ptr<ast_node>, on utilise extract_as_node()
//   qui dispatche sur tous les types concrets connus.
// ─────────────────────────────────────────────────────────────────────────────

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
        if (auto* p = std::any_cast<std::shared_ptr<direct<DFT,EXPENV>>>(&a))
            return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
        if (auto* p = std::any_cast<std::shared_ptr<plus<DFT,EXPENV>>>(&a))
            return std::static_pointer_cast<rvalue<DFT,EXPENV>>(*p);
        // Fallback : le any contient déjà shared_ptr<rvalue<DFT,EXPENV>>
        if (auto* p = std::any_cast<std::shared_ptr<rvalue<DFT,EXPENV>>>(&a))
            return *p;
        return nullptr;
    }

    // ── extract_as_node ───────────────────────────────────────────────────────
    // Helper global : extrait un shared_ptr<ast_node> depuis n'importe quel
    // std::any retourné par un visiteur, sans connaître le type template.
    // Utilisé par main.cpp (et tout code appelant externe).
    //
    // Dispatche sur toutes les combinaisons (DFT x EXPENV) connues.
    // Lance std::runtime_error si aucune ne correspond.
    // extract_as_node ne couvre que les combinaisons réellement produites
    // par les visiteurs du builder :
    //
    // • BOOL exclu : plus<BOOL,*> est invalide — ChipsOperandToAstNumericType
    //   n'a pas de spécialisation BOOL (intentionnel : + n'est pas défini sur bool).
    //
    // • SYSTEM exclu : rvalue<dft,SYSTEM> hérite de feeder<LOGICAL,dft> qui est
    //   incomplet ici (défini dans ast_system_specific.hpp, non inclus par ASTBuilder).
    //   De plus, les atomes littéraux sont toujours PRIMITIVE.
    //
    // Ajouter une ligne ici si un futur visiteur produit une nouvelle combinaison.
    inline std::shared_ptr<ast_node> extract_as_node(const std::any& a) {
        #define TRY_UPCAST(DFT, EXPENV)                                     \
            if (auto p = try_extract<DFT, EXPENV>(a))                       \
                return std::static_pointer_cast<ast_node>(p);

        TRY_UPCAST(dataflow_type::INT,   expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::INT,   expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::COLLECTIVE)

        #undef TRY_UPCAST

        throw std::runtime_error(
            "extract_as_node : type inconnu dans le std::any : "
            + type_name(a.type())
            + ". Si un nouveau visiteur produit BOOL ou SYSTEM, "
              "ajouter la combinaison dans extract_as_node.");
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
    // BOOL exclu car +, -, *, / ne sont pas définis sur les booléens.
    template<template<dataflow_type, expression_env> class Builder>
    std::any dispatch_numeric_binary(
        const std::any& left_any,
        const std::any& right_any,
        const char* op_name)
    {
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
        TRY_BINARY(dataflow_type::INT,   expression_env::COLLECTIVE)
        TRY_BINARY(dataflow_type::FLOAT, expression_env::COLLECTIVE)
        TRY_BINARY(dataflow_type::INT,   expression_env::SYSTEM)
        TRY_BINARY(dataflow_type::FLOAT, expression_env::SYSTEM)

        #undef TRY_BINARY

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
            return std::make_shared<plus<DFT,EXPENV>>(std::move(l), std::move(r));
        }
    };

} // namespace ast_builder_detail


// ─────────────────────────────────────────────────────────────────────────────
// ASTBuilder
// ─────────────────────────────────────────────────────────────────────────────

class ASTBuilder : public ChipsBaseVisitor {
public:

    std::any visitProgram(ChipsParser::ProgramContext* ctx) override {
        return visit(ctx->expr());
    }

    // ── Opérateurs binaires ───────────────────────────────────────────────────

    std::any visitPLUS(ChipsParser::PLUSContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "PLUS");
    }

    // ── Atomes ───────────────────────────────────────────────────────────────

    std::any visitIntLiteral(ChipsParser::IntLiteralContext* ctx) override {
        return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(
            std::stoll(ctx->INT()->getText()));
    }

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext* ctx) override {
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
            std::stod(ctx->FLOAT()->getText()));
    }

    // ── Pass-through ─────────────────────────────────────────────────────────

    std::any visitPassExpr0(ChipsParser::PassExpr0Context* ctx) override {
        return visit(ctx->expr0());
    }
    std::any visitPassExpr1(ChipsParser::PassExpr1Context* ctx) override {
        return visit(ctx->expr1());
    }
    std::any visitPassExpr2(ChipsParser::PassExpr2Context* ctx) override {
        return visit(ctx->expr2());
    }
};

#endif