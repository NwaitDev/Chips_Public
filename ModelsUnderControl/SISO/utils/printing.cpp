#include "printing.hpp"
#include <string>

CppOutStream openStream(std::string filename) {
    std::string fullname = filename + ".csv";
    return new std::ofstream(fullname);
}

void printInStream(CppOutStream stream, std::string s) {
    *stream << s << " ";
}

void printInStream(CppOutStream stream, int n) {
    *stream << n << " ";
}

void printInStream(CppOutStream stream, double f) {
    *stream << f << " ";
}

void printClapLineInStream(
    CppOutStream stream,
    int time,
    double sound,
    int r,
    int g,
    int b,
    double command
) {
    *stream << time << "," << sound << "," << r << "," << g << "," << b << "," << command << "\n";
}

void closeStream(CppOutStream stream) {
    stream->flush();
    stream->close();
    delete stream;
}