#include "bip_importable.hpp"

//--------------------------------------------------------------------------------
//Definitions generated from chips sources
//--------------------------------------------------------------------------------

const char *const chips_diag::source_file = "/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/Drone.chips";

void init_Drone([[maybe_unused]] chips_float& dt_in, [[maybe_unused]] chips_float& u_in, [[maybe_unused]] chips_float& DRAG_COEFF_inner, [[maybe_unused]] chips_float& GRAVITY_inner, [[maybe_unused]] chips_float& KP_inner, [[maybe_unused]] chips_float& altitude_inner, [[maybe_unused]] chips_float& altitude_max_inner, [[maybe_unused]] chips_float& m_inner, [[maybe_unused]] chips_float& prevError_inner, [[maybe_unused]] chips_float& velocity_inner, [[maybe_unused]] chips_float& update_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(2, 5);
    m_inner = chips_float{0.2};
    chips_diag::at(3, 5);
    altitude_inner = chips_float{0.};
    chips_diag::at(4, 5);
    altitude_max_inner = chips_float{0.};
    chips_diag::at(5, 5);
    velocity_inner = chips_float{0.};
    chips_diag::at(6, 5);
    prevError_inner = chips_float{0.};
    chips_diag::at(7, 5);
    GRAVITY_inner = chips_float{9.81};
    chips_diag::at(8, 5);
    KP_inner = chips_float{0.29};
    chips_diag::at(9, 5);
    DRAG_COEFF_inner = chips_float{0.8};
}

void then_Drone([[maybe_unused]] chips_float& dt_in, [[maybe_unused]] chips_float& u_in, [[maybe_unused]] chips_float& DRAG_COEFF_inner, [[maybe_unused]] chips_float& GRAVITY_inner, [[maybe_unused]] chips_float& KP_inner, [[maybe_unused]] chips_float& altitude_inner, [[maybe_unused]] chips_float& altitude_max_inner, [[maybe_unused]] chips_float& m_inner, [[maybe_unused]] chips_float& prevError_inner, [[maybe_unused]] chips_float& velocity_inner, [[maybe_unused]] chips_float& update_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(11, 5);
    chips_float radian = chips_make_shaped<double>(0.0, {});
    radian = ((chips_float{2.} * chips_float{3.14159265358979323846}) / chips_float{60.});
    chips_diag::at(12, 5);
    chips_float K = chips_make_shaped<double>(0.0, {});
    K = chips_float{4.} * KP_inner * radian * radian;
    chips_diag::at(13, 5);
    chips_float Fp = chips_make_shaped<double>(0.0, {});
    Fp = K * u_in * u_in;
    chips_diag::at(14, 5);
    chips_float drag = chips_make_shaped<double>(0.0, {});
    drag = DRAG_COEFF_inner * velocity_inner;
    chips_diag::at(15, 5);
    chips_float a = chips_make_shaped<double>(0.0, {});
    a = (Fp / m_inner) - GRAVITY_inner - (drag / m_inner);
    chips_diag::at(16, 5);
    velocity_inner = velocity_inner + a * dt_in;
    chips_diag::at(17, 5);
    altitude_inner = altitude_inner + velocity_inner * dt_in;
    chips_diag::at(18, 5);
    if (altitude_inner < chips_float{0.})
    {
        chips_diag::at(19, 9);
        altitude_inner = chips_float{0.};
        chips_diag::at(20, 9);
        velocity_inner = chips_float{0.};
    }
    chips_diag::at(22, 5);
    if (altitude_max_inner < altitude_inner)
    {
        chips_diag::at(23, 9);
        altitude_max_inner = altitude_inner;
    }
    else
    {
        chips_diag::at(25, 9);
        altitude_max_inner = altitude_max_inner;
    }
    chips_diag::at(27, 3);
    chips_reset(update_out, altitude_inner);
}

void init_PID([[maybe_unused]] chips_float& current_in, [[maybe_unused]] chips_float& dt_in, [[maybe_unused]] chips_float& target_in, [[maybe_unused]] chips_float& derivative_inner, [[maybe_unused]] chips_float& integral_inner, [[maybe_unused]] chips_float& kd_inner, [[maybe_unused]] chips_float& ki_inner, [[maybe_unused]] chips_float& kp_inner, [[maybe_unused]] chips_float& maxOutput_inner, [[maybe_unused]] chips_float& minOutput_inner, [[maybe_unused]] chips_float& prevError_inner, [[maybe_unused]] chips_float& proportional_inner, [[maybe_unused]] chips_float& correction_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(30, 5);
    prevError_inner = chips_float{0.};
    chips_diag::at(31, 5);
    proportional_inner = chips_float{0.};
    chips_diag::at(32, 5);
    integral_inner = chips_float{0.};
    chips_diag::at(33, 5);
    derivative_inner = chips_float{0.};
    chips_diag::at(34, 5);
    kp_inner = chips_float{1.5};
    chips_diag::at(35, 5);
    ki_inner = chips_float{0.6};
    chips_diag::at(36, 5);
    kd_inner = chips_float{0.0};
    chips_diag::at(37, 5);
    minOutput_inner = chips_float{0.0};
    chips_diag::at(38, 5);
    maxOutput_inner = chips_float{15.0};
}

void then_PID([[maybe_unused]] chips_float& current_in, [[maybe_unused]] chips_float& dt_in, [[maybe_unused]] chips_float& target_in, [[maybe_unused]] chips_float& derivative_inner, [[maybe_unused]] chips_float& integral_inner, [[maybe_unused]] chips_float& kd_inner, [[maybe_unused]] chips_float& ki_inner, [[maybe_unused]] chips_float& kp_inner, [[maybe_unused]] chips_float& maxOutput_inner, [[maybe_unused]] chips_float& minOutput_inner, [[maybe_unused]] chips_float& prevError_inner, [[maybe_unused]] chips_float& proportional_inner, [[maybe_unused]] chips_float& correction_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at(40, 5);
    chips_float error = chips_make_shaped<double>(0.0, {});
    error = target_in - current_in;
    chips_diag::at(41, 5);
    chips_float p_out = chips_make_shaped<double>(0.0, {});
    p_out = kp_inner * error;
    chips_diag::at(42, 5);
    proportional_inner = error;
    chips_diag::at(43, 5);
    integral_inner = integral_inner + error * dt_in;
    chips_diag::at(44, 5);
    chips_float i_out = chips_make_shaped<double>(0.0, {});
    i_out = ki_inner * integral_inner;
    chips_diag::at(45, 5);
    derivative_inner = chips_float{0.};
    chips_diag::at(46, 5);
    if (dt_in > chips_float{0.})
    {
        chips_diag::at(47, 9);
        derivative_inner = (error - prevError_inner) / dt_in;
    }
    chips_diag::at(49, 5);
    chips_float d_out = chips_make_shaped<double>(0.0, {});
    d_out = kd_inner * derivative_inner;
    chips_diag::at(50, 5);
    chips_float rawCorrection = chips_make_shaped<double>(0.0, {});
    rawCorrection = p_out + i_out + d_out;
    chips_diag::at(51, 5);
    chips_float saturated = chips_make_shaped<double>(0.0, {});
    saturated = static_cast<chips_float>((imax(static_cast<chips_int>((minOutput_inner)), imin(static_cast<chips_int>((rawCorrection)), static_cast<chips_int>((maxOutput_inner))))));
    chips_diag::at(52, 5);
    prevError_inner = error;
    chips_diag::at(53, 3);
    chips_reset(correction_out, saturated);
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

