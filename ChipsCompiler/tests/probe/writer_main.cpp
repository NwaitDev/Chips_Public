#include "writer.hpp"
#include <iostream>

int main()
{
    int failures = 0;
    for (double v : {3.0, 1e20, 1e-7, -0.25, 0.1, 1.7e308})
    {
        const std::string text = chips_probe_literal(v);
        if (text.find_first_of("eE") != std::string::npos || chips_parse_literal<double>(text, "float", "literal") != v)
        {
            std::cerr << "float literal mismatch: " << v << " written as " << text << "\n";
            ++failures;
        }
    }
    for (std::string instance : {"w1", "sys.w[2]"})
    {
        chips_int a({3}), i({1}), m({2, 2});
        chips_bool b({1});
        chips_float f({1}), g({1});
        init_writer(a, b, f, g, i, m, instance, 0);
        for (int tick = 1; tick <= 4; ++tick)
            then_writer(a, b, f, g, i, m, instance, tick);
    }
    return failures;
}
