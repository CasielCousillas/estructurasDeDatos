#ifndef LINKEDLIST
#define LINKEDLIST

#include <string>

struct Node{
  int val;
  Node* next;
  Node* prev;
};

class DoubleLinkedList{
  private:
    Node* head;
    Node* tail;

  public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList& other);
    DoubleLinkedList& operator=(const DoubleLinkedList& other); 

    size_t longitud();
    void addHead(int val);
    void addTail(int val);
    void deleteNode(size_t i);
    Node* obtain(size_t i);
    void reemplazarNodo(size_t i, Node* newNode);

    DoubleLinkedList copie();
    std::string toString();
    void clear();

    ~DoubleLinkedList();
};

#endif