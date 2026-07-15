#include "printing.hpp"

void emptyFile(std::string filename){
    std::ofstream myfile;
    myfile.open (filename);
    myfile.close();
}

CppOutStream openStream(std::string filename){
    std::ofstream myfile;
    myfile.open (filename,std::ios_base::app);
    return myfile;
}

void openLogger(const std::string& filename){
    logger.open(filename, std::ios_base::out);
}

void writeLogger(const std::string& txt){
    logger << txt;
}
void writeLogger(const int& x){
    logger << x;
}
void writeLogger(const double& x){
    logger << x;
}
void writeLogger(const chips_float& x){
    logger << std::get<0>(x);
}

void loggerTime(const chips_float& x){
    t = x;
}
void loggerTarget(const chips_float& x){target = x;}
void loggerMeasure(const chips_float& x){measure=x;}
void loggerCommand(const chips_float& x){command=x;}
void loggerProportional(const chips_float& x){proportional=x;}
void loggerIntegral(const chips_float& x){integral=x;}
void loggerDerivative(const chips_float& x){derivative=x;}
void loggerError(const chips_float& x){error=x;}

void writeAll(){
    if(std::get<0>(target) == 0.0) return;
         logger << std::get<0>(t) << ","
             << std::get<0>(target) << ","
             << std::get<0>(measure) << ","
             << std::get<0>(command) << ","
             << std::get<0>(proportional) << ","
             << std::get<0>(integral) << ","
             << std::get<0>(derivative) << ","
             << (std::get<0>(target) - std::get<0>(measure)) << "\n";
}

void closeLogger(){
    if(logger.is_open()){
        logger.close();
    }
}

void printInStream(CppOutStream& outputstream, std::string txt){
    outputstream << txt;
}

void printfBIP(std::string txt){
    std::cout << " " << txt;
}

void printInStream(CppOutStream& outputstream, int n){
    outputstream << n;
}

void printfBIP(int n){
    std::cout << " " << n;
}

void printInStream(CppOutStream& outputstream, double x){
    outputstream << x;
}

void printfBIP(double x){
    std::cout << " " << x;
}

void printInStream(CppOutStream& outputstream, chips_float& x){
    outputstream << std::get<0>(x);
}

void printfBIP(chips_float& x){
    std::cout << " " << std::get<0>(x);
}

void closeStream(CppOutStream& outputstream){
    outputstream.close();
}
    