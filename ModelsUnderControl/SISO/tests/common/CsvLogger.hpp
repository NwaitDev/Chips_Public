#ifndef CSV_LOGGER_HPP
#define CSV_LOGGER_HPP

#include <fstream>
#include <string>

class CsvLogger {
public:
    CsvLogger(const std::string& filename) {
        file.open(filename);
        file << "time,target,measure,command,proportional,integral,derivative,error\n";
    }

    ~CsvLogger() {
        if (file.is_open())
            file.close();
    }

    void log(float t, float target, float measure, float proportional, float integral, float derivative, float command) {
        file << t << ","
             << target << ","
             << measure << ","
             << command << ","
             << proportional << ","
             << integral << ","
             << derivative << ","
             << (target - measure) << "\n";
    }

private:
    std::ofstream file;
};

#endif
