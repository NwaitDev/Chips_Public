#include <fstream>
#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ChipsLexer.h"
#include "ChipsParser.h"
#include "CodeGenListener.h"


void cppGenerated_file(const char* dstPath)
{
    std::string input = "logical SimulationPhysique(float y, float u, float perturbation)init{int i=0; int[3] three = range(3);int[2][3] six=range(2,3);for l in six[1]{i=1;}for j in zeros(10){i=j;} for k in three{i=k;}}then{} -> simulation((0.9 * y) + (0.1 * u * 10.) - perturbation) logical Compute(float tension) init {  int t = 0;    float test_tension = 5.;    float test_perturbation = 0.;}then{    if(t > 0){        test_tension = tension;    }    t = t + 1;    if((t >= 30) && (t < 60)){        test_perturbation = 0.5;    }else{        test_perturbation = 0.;    }} -> perturbation(test_perturbation)-> tension(test_tension)object Broadcast with {}spread() spreadTension among Broadcast {}-> @(input)-> default(input)system {    int horizon = 20;    float target = 5.;    float a = 0.9;    float b = 1.;    float utest_min = 0.;    float utest_max = 1.;    float ytest_safetest_min = 4.;    float ytest_safetest_max = 100;    Compute compute;    MPCController ctrl;    SimulationPhysique simulate;    Broadcast broadcaster;    link compute to broadcaster;    ctrl.targetValue(target);    ctrl.a(a);    ctrl.b(b);    ctrl.N(horizon);    ctrl.utest_min(utest_min);    ctrl.utest_max(utest_max);    ctrl.ytest_safetest_min(ytest_safetest_min);    ctrl.ytest_safetest_max(ytest_safetest_max);    ctrl.currentValue((spreadTension) compute.tension);    simulate.y((spreadTension) compute.tension);    simulate.u(ctrl.correction);    simulate.perturbation(compute.perturbation);    compute.tension(simulate.simulation);}";

    antlr4::ANTLRInputStream inputStream(input);

    ChipsLexer lexer(&inputStream);

    antlr4::CommonTokenStream tokens(&lexer);

    ChipsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.program();

    std::ofstream out(dstPath);
    if (!out)
    {
        std::cerr << "Failed to open output file for writing." << std::endl;
        exit(1);
    }
    CodeGenListener listener(tokens, out);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    out.close();
}


void copy_file(const char* srcPath, const char* dstPath)
{
    std::ifstream src(srcPath, std::ios::binary);
    std::ofstream dst(dstPath, std::ios::binary);
    const std::size_t bufSize = 65536;
    std::vector<char> buf(bufSize);

    while (src) {
        src.read(buf.data(), static_cast<std::streamsize>(bufSize));
        std::streamsize n = src.gcount();
        if (n > 0) dst.write(buf.data(), n);
    }
}

void append_file(const char* srcPath, const char* dstPath)
{
    std::ifstream src(srcPath, std::ios::binary);
    std::ofstream dst(dstPath, std::ios::binary | std::ios::app);
    const std::size_t bufSize = 65536;
    std::vector<char> buf(bufSize);

    while (src) {
        src.read(buf.data(), static_cast<std::streamsize>(bufSize));
        std::streamsize n = src.gcount();
        if (n > 0) dst.write(buf.data(), n);
    }
}


int main()
{
    copy_file("../src/cppHeaderAutoInclude.hpp", "bip_importable.cpp");
    cppGenerated_file("generated_functions.cpp");
    append_file("generated_functions.cpp","bip_importable.cpp");
    std::cout << "Generated code written to bip_importable.cpp" << std::endl;

    return 0;
}
