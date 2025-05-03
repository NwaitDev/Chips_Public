#ifndef __FILESTUFF_H__
#define __FILESTUFF_H__

#include <string>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief opens a file, appends a string to that file and closes it.
 * 
 * @param txt_to_write the string to write into the file
 * @param filename the name of the file to write in
 */
void owritec(std::string txt_to_write, std::string filename);


void append(std::string& first, std::string second);


void append(std::string& first, int second);

void append(std::string& first, double second);

inline void clearstr(std::string& str){str.erase(str.begin(),str.end());str.shrink_to_fit();};

#endif // __FILESTUFF_H__
