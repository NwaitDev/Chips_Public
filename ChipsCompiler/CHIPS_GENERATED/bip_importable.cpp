#include "bip_importable.hpp"

//--------------------------------------------------------------------------------
//Definitions generated from chips sources
//--------------------------------------------------------------------------------

const char *const chips_diag::source_file = "/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/additioner.chips";

void init_addi([[maybe_unused]] chips_int& a_in, [[maybe_unused]] chips_int& b_in, [[maybe_unused]] chips_int& ticks_inner, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(2, 5);
    ticks_inner = chips_int{0};
}

void then_addi([[maybe_unused]] chips_int& a_in, [[maybe_unused]] chips_int& b_in, [[maybe_unused]] chips_int& ticks_inner, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(4, 5);
    ticks_inner = ticks_inner + chips_int{1};
    chips_diag::at(5, 3);
    chips_reset(out_out, a_in + b_in);
}

void init_consumer([[maybe_unused]] chips_int& data_in)
{
    chips_diag::function_scope chips_function_scope_guard;
}

void then_consumer([[maybe_unused]] chips_int& data_in)
{
    chips_diag::function_scope chips_function_scope_guard;
}

chips_int int_init_ctx(const std::string &ctx_name)
{
    throw std::invalid_argument("int_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

chips_float float_init_ctx(const std::string &ctx_name)
{
    throw std::invalid_argument("float_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

chips_bool bool_init_ctx(const std::string &ctx_name)
{
    throw std::invalid_argument("bool_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

