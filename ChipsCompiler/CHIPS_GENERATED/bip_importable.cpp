#include "bip_importable.hpp"

//--------------------------------------------------------------------------------
//Definitions generated from chips sources
//--------------------------------------------------------------------------------

const char *const chips_diag::source_file = "/home/ohnoanna/Code/Chips_Public/ChipsCompiler/testfiles/autoincrement.chips";

void init_addi([[maybe_unused]] chips_int& a_in, [[maybe_unused]] chips_int& b_in, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
}

void then_addi([[maybe_unused]] chips_int& a_in, [[maybe_unused]] chips_int& b_in, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(2, 1);
    chips_reset(out_out, a_in + b_in);
}

void init_buffer([[maybe_unused]] chips_int& data_in, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
}

void then_buffer([[maybe_unused]] chips_int& data_in, [[maybe_unused]] chips_int& out_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(4, 42);
    chips_reset(out_out, data_in);
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

