#include "filestuff.hpp"


void owritec(std::string txt_to_write, std::string filename){
    std::ofstream myfile;
    myfile.open (filename,std::ios_base::app);
    myfile << txt_to_write << std::endl;
    myfile.close();
}

void append(std::string& first, std::string second){
    first.append(second);
}
void append(std::string& first, int second){
    first.append(std::to_string(second));
}
void append(std::string& first, double second){
    first.append(std::to_string(second));
}