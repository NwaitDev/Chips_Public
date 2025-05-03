#ifndef __BASE_H__
#define __BASE_H__

#include <cstddef>
#include <iostream>
#include <list>
#include <ostream>

struct table_t {
    size_t size;
    std::list<int> data;
    size_t nb_current;
};

struct table_t maketable(const int size);
void resizetable(struct table_t& self, const int new_size);
void puttable(struct table_t& self, const int value);
struct table_t copytable(struct table_t self);
bool findtable(struct table_t& self, const int element);

inline std::ostream& operator << ( std::ostream& os, const struct table_t& rhs ) {
    os << "[table_t("<<rhs.size<<") :";
    for( auto elem : rhs.data){
        os << elem <<" ";
    }
    os <<"]";
    return os;
}
inline void printtable(struct table_t t) { std::cout<<t;}

struct rand_t {
    unsigned int seed;
    int a,b;
};

struct rand_t makerand(const int, const int, const int);
struct rand_t updaterand(struct rand_t);
int getinrand(struct rand_t, const int, const int);




inline std::ostream& operator << ( std::ostream& os, const struct rand_t& rhs ) {
    os << "[rand_t (" <<rhs.a<<"* x +"<<rhs.b<<") : "<<rhs.seed<<"]";
    return os;
}

#endif // __BASE_H__
