#include <fstream>
#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ChipsLexer.h"
#include "ChipsParser.h"
#include "CodeGenListener.h"

int main()
{
    std::string input = 
"logical SimulationPhysique(float y, float u, float perturbation)init{int i=0; int[3] three = range(three);int[2][3] six=range(2,3);for l in six[1]{i=1;}for j in zeros(10){i=j;} for k in three{i=k;}}then{} -> simulation((0.9 * y) + (0.1 * u * 10.) - perturbation) logical Compute(float tension) init {  int t = 0;    float test_tension = 5.;    float test_perturbation = 0.;}then{    if(t > 0){        test_tension = tension;    }    t = t + 1;    if((t >= 30) && (t < 60)){        test_perturbation = 0.5;    }else{        test_perturbation = 0.;    }} -> perturbation(test_perturbation)-> tension(test_tension)object Broadcast with {}spread() spreadTension among Broadcast {}-> @(input)-> default(input)system {    int horizon = 20;    float target = 5.;    float a = 0.9;    float b = 1.;    float utest_min = 0.;    float utest_max = 1.;    float ytest_safetest_min = 4.;    float ytest_safetest_max = 100;    Compute compute;    MPCController ctrl;    SimulationPhysique simulate;    Broadcast broadcaster;    link compute to broadcaster;    ctrl.targetValue(target);    ctrl.a(a);    ctrl.b(b);    ctrl.N(horizon);    ctrl.utest_min(utest_min);    ctrl.utest_max(utest_max);    ctrl.ytest_safetest_min(ytest_safetest_min);    ctrl.ytest_safetest_max(ytest_safetest_max);    ctrl.currentValue((spreadTension) compute.tension);    simulate.y((spreadTension) compute.tension);    simulate.u(ctrl.correction);    simulate.perturbation(compute.perturbation);    compute.tension(simulate.simulation);}";

    antlr4::ANTLRInputStream inputStream(input);

    ChipsLexer lexer(&inputStream);

    antlr4::CommonTokenStream tokens(&lexer);

    ChipsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.program();

    std::cout << tree->toStringTree(&parser) << std::endl;

    // Generate C++ functions from each function's init_section / then_section.
    std::ofstream out("generated_functions.cpp");
    if (!out)
    {
        std::cerr << "Failed to open output file for writing." << std::endl;
        return 1;
    }

    CodeGenListener listener(tokens, out);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    out.close();

    std::cout << "Generated code written to generated_functions.cpp" << std::endl;

    return 0;
}
