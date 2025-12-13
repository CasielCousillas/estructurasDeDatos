#include <iostream>
#include "BST.h"
using namespace std;

int main(){
  BST b;

  b.insertar(10);
  b.insertar(5);
  b.insertar(15);
  b.insertar(7);
  b.insertar(4);
  b.insertar(14);
  b.insertar(16);

  string matriz = b.print();

  cout << matriz;

  return 0;
}
