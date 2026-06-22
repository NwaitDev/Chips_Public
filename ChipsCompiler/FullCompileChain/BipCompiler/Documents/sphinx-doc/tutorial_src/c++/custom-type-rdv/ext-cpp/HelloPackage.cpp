#include <iostream>
#include "HelloPackage.hpp"

void print_data( int id, my_custom_type &adata){
  std::cout << "Data for: " << id << " = " << adata.x
	    << "," << adata.y << std::endl;
}

void init_data(int id, my_custom_type &adata){
  adata.x = id * 2;
  adata.y = id * 8;
}
