#include "reader.hpp"

int main()
{
    chips_int a({3}), i({1}), m({2, 2});
    chips_bool b({1});
    chips_float f({1}), g({1});
    init_reader(a, b, f, g, i, m, "w1", 0);
    for (int tick = 1; tick <= 4; ++tick)
        then_reader(a, b, f, g, i, m, "w1", tick);
}
