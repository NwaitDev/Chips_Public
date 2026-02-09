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

void closeStream(CppOutStream stream) {
    stream->flush(); // Dernière sécurité
    stream->close();
    delete stream;
}