#ifndef HP_HPP
#define HP_HPP

typedef struct {
  int x,y;
} my_custom_type;

void print_data(int id, my_custom_type &adata);
void init_data(int id, my_custom_type &adata);

#endif
