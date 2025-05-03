#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <list>


struct table_t maketable(const int size){
    struct table_t t;
    t.data = std::list<int>();
    t.size = size;
    t.nb_current = 0;
    return t;
}



void resizetable(struct table_t& self, const int size){
    while(self.size >= (size_t) size){
        if(self.nb_current==self.size){
            self.data.pop_front();
            self.nb_current--;
        }
        self.size--;
    }
    self.size = size;
}

void puttable(struct table_t& self, const int value){
    if (self.nb_current >= (size_t)self.size) {
        self.data.pop_front();
        self.nb_current--;
    }
    self.data.push_back(value);
    self.nb_current++;
}

bool findtable(struct table_t& self, const int element){
    bool ret = false;
    std::list<int>::iterator current = self.data.begin();
    while (current!=self.data.end() && !ret) {
        if (*current == element) {
            ret = true;
        }else{
            std::advance(current,1);
        }
    }
    if (ret) {
        self.data.erase(current);
        self.data.push_back(element);
    }
    return ret;
}





struct rand_t makerand(const int seed, const int a, const int b){
    struct rand_t rnd;
    rnd.seed = (unsigned int)seed;
    rnd.a=a;
    rnd.b = b;
    return rnd;
}

struct rand_t updaterand(struct rand_t rnd){
    rand_t next = {(unsigned int)(rnd.seed*rnd.a + rnd.b) ,rnd.a, rnd.b};
    return next;
}

int getinrand(struct rand_t rnd, const int lower_bound, const int upper_bound){
    assert(upper_bound>lower_bound);
    return lower_bound + rnd.seed%(upper_bound-lower_bound+1);
}