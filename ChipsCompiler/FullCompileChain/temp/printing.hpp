#ifndef __PRINTING_HPP__
#define __PRINTING_HPP__

#include <fstream>
#include <string>
#include "base.hpp"
#include <iostream>

using CppOutStream = std::ofstream;

static std::ofstream logger;
static chips_float t;
static chips_float target;
static chips_float measure;
static chips_float command;
static chips_float proportional;
static chips_float integral;
static chips_float derivative;
static chips_float error;

inline std::ostream& operator << ( std::ostream& os, const CppOutStream& rhs ) {
    os << (rhs.is_open() ? "an instanciated file stream" : "no_file file_stream");
    return os;
}

void emptyFile(std::string filename);

CppOutStream openStream(std::string filename);

void openLogger(const std::string& filename);

void loggerTime(const chips_float& x);
void loggerTarget(const chips_float& x);
void loggerMeasure(const chips_float& x);
void loggerCommand(const chips_float& x);
void loggerProportional(const chips_float& x);
void loggerIntegral(const chips_float& x);
void loggerDerivative(const chips_float& x);
void loggerError(const chips_float& x);
void writeAll();

void writeLogger(const std::string& txt);
void writeLogger(const int& x);
void writeLogger(const double& x);
void writeLogger(const chips_float& x);

void closeLogger();

void printInStream(CppOutStream& outputstream, std::string txt);

void printfBIP(std::string txt);

void printInStream(CppOutStream& outputstream, int n);

void printfBIP(int n);

void printInStream(CppOutStream& outputstream, double x);

void printfBIP(double x);

void printInStream(CppOutStream& outputstream, chips_float& x);

void printfBIP(chips_float& x);

void closeStream(CppOutStream& outputstream);

#endif // __PRINTING_H__