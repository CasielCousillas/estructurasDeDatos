#include <iostream>
#include "linkedList.h"
using std::cout,std::endl,std::string;

int main(){
  Node* newNode = new Node{10,nullptr,nullptr};
  DoubleLinkedList list;
  DoubleLinkedList list2;
  list.addHead(1);
  list.addTail(2);
  list.addTail(3);
  list.addHead(4);
  list2 = list;
  std::string aux = list2.toString();
  cout << aux << endl;
}