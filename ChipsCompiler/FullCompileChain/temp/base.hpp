#ifndef __BASE_H__
#define __BASE_H__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>

using intarray = std::vector<int>;

enum collective_optional{
    REGULAR,
    STOP
};

using collective_int = std::tuple<int, collective_optional>;
using collective_float = std::tuple<double, collective_optional>;
using collective_bool = std::tuple<bool, collective_optional>;
using collective_intarray = std::tuple<intarray, collective_optional>;

using chips_int = std::tuple<int,int>;
using chips_float = std::tuple<double,int>;
using chips_bool = std::tuple<bool,int>;
using chips_intarray = std::tuple<intarray,int>;

chips_float init_float(double value);

double chips_float_to_float(chips_float& value);


void assign(chips_int&, const int&);
void assign(chips_int&,  const collective_int&);
void assign(chips_int&, const  chips_int&);
void assign(collective_int&,  const chips_int&);
void tick(chips_int&);
bool is_fresh( const chips_int&);

int operator + (const chips_int& a, const int& b);

int operator - (const chips_int& a, const int& b);

int operator - (const chips_int& a);

bool operator != (const chips_int& a, const int& b);

bool operator < (const chips_int& a, const int& b);

void assign(chips_float&, const double&);
void assign(chips_float&,  const collective_float&);
void assign(chips_float&,  const chips_float&);
void assign(collective_float&,  const chips_float&);
bool is_fresh( const chips_float&);

void assign(chips_bool&, const  bool&);
void assign(chips_bool&, const  collective_bool&);
void assign(chips_bool&, const  chips_bool&);
void assign(collective_bool&, const  chips_bool&);
bool is_fresh( const chips_bool&);

void assign(chips_intarray&, const  intarray&);
void assign(chips_intarray&,  const collective_intarray&);
void assign(chips_intarray&,  const chips_intarray&);
void assign(collective_intarray&,  const chips_intarray&);
bool is_fresh( const chips_intarray&);


intarray zeros(const int& dim1);
intarray range(const int& upto);
bool are_copies(const intarray&, const intarray&);
bool are_copies(const collective_intarray&, const collective_intarray&);
bool are_copies(const intarray&, const collective_intarray&);
bool are_copies(const collective_intarray&, const intarray&);

collective_int cpy(const collective_int&);
collective_bool cpy(const collective_bool&);
collective_float cpy(const collective_float&);
collective_intarray cpy(const collective_intarray&);

collective_int make(const int&);
collective_float make(const double&);
collective_bool make(const bool&);
collective_intarray make(const intarray&);
bool are_copies(const collective_int&, const collective_int&);
bool are_copies(const collective_int&, const int&);
bool are_copies(const int&, const collective_int&);
bool are_copies(const collective_float&, const collective_float&);
bool are_copies(const collective_bool&, const collective_bool&);

inline std::ostream& operator << ( std::ostream& os, const chips_int& rhs ) {
    os << std::get<0>(rhs) <<"(age:"<<std::get<1>(rhs)<<')';
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const intarray& rhs ) {
    os << "[int_array("<<rhs.size()<<") :";
    for( size_t i = 0; i<rhs.size(); ++i){
        os << rhs.at(i) <<" ";
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const collective_int& rhs ) {
    os << "[collective int: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const collective_bool& rhs ) {
    os << "[collective bool: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const collective_float& rhs ) {
    os << "[collective float: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const collective_intarray& rhs ) {
    os << "[collective int_array: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        for( size_t i = 0; i<std::get<0>(rhs).size(); ++i){
            os << std::get<0>(rhs).at(i) <<" ";
        }
    }
    os <<"]";
    return os;
}

double randomdouble();

inline int asint(double f){return (int)f;}
inline double asfloat(int i){return (double)i;}
inline double floatIdentity(double f){return f;}
inline double intIdentity(int i){return i;}

chips_float operator+(const chips_float& a, const chips_float& b);
chips_float operator+(const chips_float& a, const double& b);
chips_float operator+(const double& a, const chips_float& b);

chips_float operator-(const chips_float& a, const chips_float& b);
chips_float operator-(const chips_float& a, const double& b);
chips_float operator-(const double& a, const chips_float& b);
chips_float operator-(const chips_float& a);

chips_float operator*(const chips_float& a, const chips_float& b);
chips_float operator*(const chips_float& a, const double& b);
chips_float operator*(const double& a, const chips_float& b);

chips_float operator/(const chips_float& a, const chips_float& b);
chips_float operator/(const chips_float& a, const double& b);
chips_float operator/(const double& a, const chips_float& b);

bool operator<(const chips_float& a, const chips_float& b);

chips_float max(const chips_float& a, const double& b);

#endif // __BASE_H__
