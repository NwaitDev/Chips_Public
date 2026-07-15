#include "base.hpp"
#include <cassert>
#include <cstdlib>
#include <tuple>
#include <vector>

chips_float init_float(double value){
    return std::make_tuple(value, 0);
}

double chips_float_to_float(chips_float& value){
    return std::get<0>(value);
}

void assign(chips_int& lhs, const  int& rhs){
    std::get<0>(lhs) = rhs;
    std::get<1>(lhs) = 0;
}
void assign(chips_int& lhs,  const collective_int& rhs){
    if(std::get<1>(rhs) == REGULAR){
        std::get<0>(lhs) = std::get<0>(rhs);
        std::get<1>(lhs) = 0;
    }
}
void assign(chips_int& lhs,  const chips_int& rhs){
    std::get<0>(lhs) = std::get<0>(rhs); 
    std::get<1>(lhs) = std::get<1>(rhs); 
}
void assign(collective_int& lhs,  const chips_int& rhs){
    std::get<0>(lhs) = std::get<0>(rhs);
    std::get<1>(lhs) = REGULAR;
}
void tick(chips_int& a){
    std::get<1>(a)++;
}
int operator + (const chips_int& a, const int& b) {
    return std::get<0>(a) + b;
};

int operator - (const chips_int& a, const int& b) {
    return std::get<0>(a) - b;
};

int operator - (const chips_int& a) {
    return - std::get<0>(a);
};

bool operator != (const chips_int& a, const int& b) {
    return std::get<0>(a) != b;
};

bool operator < (const chips_int& a, const int& b) {
    return std::get<0>(a) < b;
};

void assign(chips_float& lhs,  const double& rhs){
    std::get<0>(lhs) = rhs;
    std::get<1>(lhs) = 0;
}

void assign(chips_float &lhs, const collective_float &rhs)
{
    if(std::get<1>(rhs) == REGULAR){
        std::get<0>(lhs) = std::get<0>(rhs);
        std::get<1>(lhs) = 0;
    }
}
void assign(chips_float& lhs,  const chips_float& rhs){
    std::get<0>(lhs) = std::get<0>(rhs); 
    std::get<1>(lhs) = std::get<1>(rhs); 
}
void assign(collective_float& lhs, const  chips_float& rhs){
    std::get<0>(lhs) = std::get<0>(rhs);
    std::get<1>(lhs) = REGULAR;
}

void assign(chips_bool& lhs, const  bool& rhs){
    std::get<0>(lhs) = rhs;
    std::get<1>(lhs) = 0;
}
void assign(chips_bool& lhs,  const collective_bool& rhs){
    if(std::get<1>(rhs) == REGULAR){
        std::get<0>(lhs) = std::get<0>(rhs);
        std::get<1>(lhs) = 0;
    }
}
void assign(chips_bool& lhs, const  chips_bool& rhs){
    std::get<0>(lhs) = std::get<0>(rhs); 
    std::get<1>(lhs) = std::get<1>(rhs); 
}
void assign(collective_bool& lhs,  const chips_bool& rhs){
    std::get<0>(lhs) = std::get<0>(rhs);
    std::get<1>(lhs) = REGULAR;
}

void assign(chips_intarray& lhs,  const intarray& rhs){
    std::get<0>(lhs).resize(rhs.size());
    for(size_t i = 0; i<rhs.size();++i){
        std::get<0>(lhs)[i] = rhs[i];
    }
    std::get<1>(lhs) = 0;
}
void assign(chips_intarray& lhs,  const collective_intarray& rhs){
    if(std::get<1>(rhs) == REGULAR){
        std::get<0>(lhs).resize(std::get<0>(rhs).size());
        for(size_t i = 0; i<std::get<0>(rhs).size();++i){
            std::get<0>(lhs)[i] = std::get<0>(rhs)[i];
        }
        std::get<1>(lhs) = 0;
    }
}
void assign(chips_intarray& lhs, const  chips_intarray& rhs){
    std::get<0>(lhs).resize(std::get<0>(rhs).size());
    for(size_t i = 0; i<std::get<0>(rhs).size();++i){
        std::get<0>(lhs)[i] = std::get<0>(rhs)[i];
    }
    std::get<1>(lhs) = std::get<1>(rhs);
}

void assign(collective_intarray& lhs,  const chips_intarray& rhs){
    std::get<0>(lhs).resize(std::get<0>(rhs).size());
    for(size_t i = 0; i<std::get<0>(rhs).size();++i){
        std::get<0>(lhs)[i] = std::get<0>(rhs)[i];
    }
    std::get<1>(lhs) = REGULAR;
}

bool is_fresh( const chips_int& c){
    return std::get<1>(c) == 0;
}
bool is_fresh( const chips_float& c){
    return std::get<1>(c) == 0;
}
bool is_fresh( const chips_bool& c){
    return std::get<1>(c) == 0;
}
bool is_fresh( const chips_intarray& c){
    return std::get<1>(c) == 0;
}

collective_int cpy(const collective_int& toBeAssigned){
    return collective_int{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

collective_bool cpy(const collective_bool& toBeAssigned){
    return collective_bool{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}
collective_float cpy(const collective_float& toBeAssigned){
    return collective_float{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

collective_intarray cpy(const collective_intarray& toBeAssigned){
    collective_intarray ret;
    std::get<1>(ret) = std::get<1>(toBeAssigned);
    std::get<0>(ret) = std::vector<int>(std::get<0>(toBeAssigned));
    return ret;
}

intarray zeros(const int& dim1){
    intarray out = std::vector<int>(dim1);
    for(size_t i = 0; i<(size_t)dim1; ++i){
        out[i] = 0;
    }
    return out;
}

intarray range(const int& upto){
    intarray out = std::vector<int>(upto);
    for(size_t i = 0; i<(size_t)upto; ++i){
        out[i] = i;
    }
    return out;
}

bool are_copies(const intarray& a, const intarray& b){
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i=0; i<a.size(); ++i) {
        if(a[i]!=b[i]){
            return false;
        }
    }
    return true;
}


bool are_copies(const collective_intarray& a, const collective_intarray& b){
    if(std::get<1>(a)!=std::get<1>(b)){
        return false;
    }
    return are_copies(std::get<0>(a),std::get<0>(b));
}
bool are_copies(const intarray& a, const collective_intarray& b){
    if(STOP == std::get<1>(b)){
        return false;
    }
    return are_copies(a,std::get<0>(b));
}

bool are_copies(const collective_intarray& a, const intarray& b){
    if(STOP == std::get<1>(a)){
        return false;
    }
    return are_copies(b,std::get<0>(a));
}


collective_int make(const int& value){
    return std::make_tuple(value, REGULAR);
}
collective_float make(const double& value){
    return std::make_tuple(value, REGULAR);
}
collective_bool make(const bool& value){
    return std::make_tuple(value, REGULAR);
}
collective_intarray make(const intarray& value){
    return std::make_tuple(value, REGULAR);
}

bool are_copies(const collective_int& a, const collective_int& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}
bool are_copies(const collective_int& a, const int& b){
    return ((std::get<1>(a) == REGULAR) && (std::get<0>(a) == b));
}
bool are_copies(const int& a, const collective_int& b){
    return are_copies(b,a);
}

bool are_copies(const collective_float& a, const collective_float& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}
bool are_copies(const collective_bool& a, const collective_bool& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}


double randomdouble(){
	return (double)rand() / RAND_MAX;
}

chips_float operator+(const chips_float& a, const chips_float& b) {
    return std::make_tuple(std::get<0>(a) + std::get<0>(b), 0);
}

chips_float operator+(const chips_float& a, const double& b) {
    return std::make_tuple(std::get<0>(a) + b, 0);
}

chips_float operator+(const double& a, const chips_float& b) {
    return std::make_tuple(a + std::get<0>(b), 0);
}

chips_float operator-(const chips_float& a, const chips_float& b) {
    return std::make_tuple(std::get<0>(a) - std::get<0>(b), 0);
}

chips_float operator-(const chips_float& a, const double& b) {
    return std::make_tuple(std::get<0>(a) - b, 0);
}

chips_float operator-(const double& a, const chips_float& b) {
    return std::make_tuple(a - std::get<0>(b), 0);
}

chips_float operator*(const chips_float& a, const chips_float& b) {
    return std::make_tuple(std::get<0>(a) * std::get<0>(b), 0);
}

chips_float operator*(const chips_float& a, const double& b) {
    return std::make_tuple(std::get<0>(a) * b, 0);
}

chips_float operator*(const double& a, const chips_float& b) {
    return std::make_tuple(a * std::get<0>(b), 0);
}

chips_float operator/(const chips_float& a, const chips_float& b) {
    return std::make_tuple(std::get<0>(a) / std::get<0>(b), 0);
}

chips_float operator/(const chips_float& a, const double& b) {
    return std::make_tuple(std::get<0>(a) / b, 0);
}

chips_float operator/(const double& a, const chips_float& b) {
    return std::make_tuple(a / std::get<0>(b), 0);
}

chips_float operator-(const chips_float& a) {
    return std::make_tuple(-std::get<0>(a), std::get<1>(a));
}


bool operator<(const chips_float& a, const chips_float& b){
    return std::get<0>(a) < std::get<0>(b);
}

chips_float max(const chips_float& a, const double& b){
    if(std::get<0>(a) >= b){
        return a;
    }
    return std::make_tuple(b, 0);
}
