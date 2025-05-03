#include "../ChipsADS.hpp"

//////// C-Style dataflow resolution function
// to allow recursive expression construction
// without creating dataflow default constructor
// (constraint kept to restrain the

namespace chips_ads {

    dataflow_t number_resolution(expression_t *left_child, expression_t *right_child) {
        if ((left_child->get_dataflow().get_df_type() == INT_DF) &&
            (right_child->get_dataflow().get_df_type() == INT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(INT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        if ((left_child->get_dataflow().get_df_type() == FLOAT_DF) &&
            (right_child->get_dataflow().get_df_type() == FLOAT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(FLOAT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        if ((left_child->get_dataflow().get_df_type() == INT_DF) &&
            (right_child->get_dataflow().get_df_type() == INT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(INT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        if (((left_child->get_dataflow().get_df_type() == INT_DF) &&
            (right_child->get_dataflow().get_df_type() == FLOAT_DF)) ||
            ((left_child->get_dataflow().get_df_type() == FLOAT_DF) &&
            (right_child->get_dataflow().get_df_type() == INT_DF))) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(FLOAT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t number_resolution(expression_t *child) {
        if (child->get_dataflow().get_df_type() == INT_DF) {
            return dataflow_t(INT_DF, child->get_dataflow().get_dimension());
        }
        if (child->get_dataflow().get_df_type() == FLOAT_DF) {
            return dataflow_t(FLOAT_DF,
                                        child->get_dataflow().get_dimension());
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t int_resolution(expression_t *left_child,
                                        expression_t *right_child) {
        if ((left_child->get_dataflow().get_df_type() == INT_DF) &&
            (right_child->get_dataflow().get_df_type() == INT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(INT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t bool_resolution(expression_t *left_child, expression_t *right_child) {
        if ((left_child->get_dataflow().get_df_type() == BOOL_DF) &&
            (right_child->get_dataflow().get_df_type() == BOOL_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(BOOL_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t cast_resolution(EXPRESSION_TYPE type, expression_t *child) {
        switch (type) {
            case CAST_TO_INT_EXP:
                return dataflow_t(INT_DF, child->get_dataflow().get_dimension());
            case CAST_TO_FLOAT_EXP:
                return dataflow_t(FLOAT_DF, child->get_dataflow().get_dimension());
            case CAST_TO_BOOL_EXP:
                return dataflow_t(BOOL_DF, child->get_dataflow().get_dimension());
            default:
                throw chips_exception("Cannot cast with such expression type");
                break;
        }
    }

    dataflow_t bool_resolution(expression_t *child) {
        if (child->get_dataflow().get_df_type() == BOOL_DF) {
            return dataflow_t(BOOL_DF, child->get_dataflow().get_dimension());
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t same_df_resolution(expression_t *left_child, expression_t *right_child) {
        if ((left_child->get_dataflow().get_df_type() == BOOL_DF) &&
            (right_child->get_dataflow().get_df_type() == BOOL_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(BOOL_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        if ((left_child->get_dataflow().get_df_type() == INT_DF) &&
            (right_child->get_dataflow().get_df_type() == INT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(INT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        if ((left_child->get_dataflow().get_df_type() == FLOAT_DF) &&
            (right_child->get_dataflow().get_df_type() == FLOAT_DF)) {
            if (left_child->get_dataflow().get_dimension() ==
                right_child->get_dataflow().get_dimension()) {
            return dataflow_t(FLOAT_DF,
                                        left_child->get_dataflow().get_dimension());
            }
        }
        throw chips_exception("Unhandled dataflow combination for this operator");
    }

    dataflow_t name_resolution(full_context &ctx, std::string name) {

        COMPILE_STATE state = ctx.get_state();

        if (state == IN_PURE) {
            if (!ctx.get_pure(ctx.get_attr()).exists(name)) {
            throw chips_exception("no variable with " + name + " name in " +
                                    ctx.get_attr());
            } else {
            return dataflow_t(
                ctx.get_pure(ctx.get_attr()).get_df_of(name));
            }
        }

        if (state == IN_PHYSICAL) {
            if (!ctx.get_physical(ctx.get_attr()).exists(name)) {
            throw chips_exception("no variable with " + name + " name in " +
                                    ctx.get_attr());
            } else {
            return dataflow_t(
                ctx.get_physical(ctx.get_attr()).get_df_of(name));
            }
        }

        if (state == IN_VIRTUAL) {
            if (!ctx.get_virtual(ctx.get_attr()).exists(name)) {
            throw chips_exception("no variable with " + name + " name in " +
                                    ctx.get_attr());
            } else {
            return dataflow_t(
                ctx.get_virtual(ctx.get_attr()).get_df_of(name));
            }
        }

        throw chips_exception("Couldn't resolve dataflow for " + name + "\n");
    }

    dataflow_t function_call_resolution(full_context &ctx, std::string name, std::vector<expression_t> elist) {
        switch (ctx.get_state()) {
            case CONFIGURING:
                throw chips_exception("unimplemented yet");
            case DEFINING:
                throw chips_exception("Something must be wrong with the parser, can't call "
                                    "a function in the defining context");
            case IN_PURE:
            case IN_PHYSICAL:
            case IN_VIRTUAL:
                return ctx.get_pure(name).get_outputs().at(0).get_dataflow();
                break;
        }
    }

    //////// General dataflow resolution function

    dataflow_t dataflow_resolution(
        full_context &ctx, EXPRESSION_TYPE type, std::string *name,
        expression_t *left_child, expression_t *right_child,
        dataflow_t *value, std::vector<expression_t> *elist) {

    switch (type) {
            // binary dataflow resolution
        case PLUS_EXP:
        case MINUS_EXP:
        case TIMES_EXP:
        case DIV_EXP:
            return number_resolution(left_child, right_child);
        case MOD_EXP:
            return int_resolution(left_child, right_child);
        case AND_EXP:
        case OR_EXP:
            return bool_resolution(left_child, right_child);
        case EQ_EXP:
        case NEQ_EXP:
            return same_df_resolution(left_child, right_child);
        case GT_EXP:
        case LT_EXP:
        case GEQ_EXP:
        case LEQ_EXP:
            return dataflow_t(
                BOOL_DF, number_resolution(left_child, right_child).get_dimension());

            // unary dataflow resolution
        case NOT_EXP:
            return bool_resolution(left_child);
        case U_MINUS_EXP:
            return number_resolution(left_child);
        case CAST_TO_INT_EXP:
        case CAST_TO_FLOAT_EXP:
        case CAST_TO_BOOL_EXP:
            return cast_resolution(type, left_child);

            // named dataflow resolution
        case IDENT_EXP:
            return name_resolution(ctx, *name);
        case OBJ_PHY_ATTR_EXP:
            throw chips_exception(
                "object physical attribute type resolution unimplemented yet");

        case OBJ_VIRT_IN_EXP:
        case OBJ_VIRT_OUT_EXP:
            throw chips_exception("configurational expression not handled yet");

            // function dataflow resolution
        case FCALL_EXP:
            return function_call_resolution(ctx, *name, *elist);
            // litteral dataflow resolution
        case INT_EXP:
        case FLOAT_EXP:
        case BOOL_EXP:
            return *value;
        default:
            throw chips_exception("unknown expression type");
        }
    }

    // Expression constructor
    expression_t::expression_t(
        full_context &ctx,
        EXPRESSION_TYPE type,
        std::string *name,
        expression_t *left_child,
        expression_t *right_child,
        dataflow_t *value,
        std::vector<expression_t> *elist)
    : type(type), 
    df(dataflow_resolution(ctx, type, name, left_child, right_child, value, elist)) 
    {}

} // namespace chips_ads
