#include <iostream>
#include "unordered_map.h"
using namespace std;

int main(){
  unorderedMap<int> mapa(5);
  mapa.add("hoila",10);
  mapa.erase("hoila");
  mapa.print();
}