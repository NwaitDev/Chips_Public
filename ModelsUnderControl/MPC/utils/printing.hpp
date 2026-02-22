#ifndef __PRINTING_HPP__
#define __PRINTING_HPP__
#include <fstream>
#include <string>

typedef std::ofstream* CppOutStream;

CppOutStream openStream(std::string filename);
void printInStream(CppOutStream stream, std::string s);
void printInStream(CppOutStream stream, int n);
void printInStream(CppOutStream stream, double f);
void closeStream(CppOutStream stream);

#endif