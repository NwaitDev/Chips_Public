#include <exception>
#include <string>

class chips_exception : std::exception {
    std::string msg;
    const char* what() const throw()
    {
        return msg.c_str();
    }
    public:
    chips_exception(std::string msg) : msg(msg){}

    
};