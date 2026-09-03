#ifndef FILTER_LOGGER_HPP
#define FILER_LOGGER_HPP

#include <fstream>
#include <string>

class FilterLogger{
private:
    std::ofstream file;

public:
    FilterLogger(const std::string& filename){
        file.open(filename);
        file << "t,raw,filtered\n";
    }

    ~FilterLogger(){
        if(file.is_open()){
            file.close();
        }
    }

    void log(float t, float raw, float filtered){
        file << t << ","
             << raw << ","
             << filtered << "\n";
    }
};

#endif