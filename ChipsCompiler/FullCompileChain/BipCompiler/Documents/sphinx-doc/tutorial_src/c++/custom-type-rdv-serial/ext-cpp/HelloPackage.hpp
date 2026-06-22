#ifndef HP_HPP
#define HP_HPP

#include <iostream>

struct __my_custom_type;

struct __my_custom_type {
  int x,y;
  friend std::ostream& operator<<(std::ostream &o, const struct __my_custom_type &value);
};

typedef struct __my_custom_type my_custom_type;

void print_data(int id, my_custom_type &adata);
void init_data(int id, my_custom_type &adata);

#endif
