#include <iostream>

void my_print(const char *message, int &adata){
  std::cout << "Someone says: " << message << " with data=" << adata << std::endl;
}
