#include "linkedList.h"
#include <string>

DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr) {}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr){
  Node* current = other.head;
  while(current != nullptr){
    addTail(current->val);
    current = current->next;
  }
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& other){ //Devuelvo una & para evitar copias y permitir asignaciones multiples.
  if(this == &other) return *this; //Evito autoasignaciones

  clear();

  Node* current = other.head;
  while(current != nullptr){
    addTail(current->val);
    current = current->next;
  }

  return *this;
} 

size_t DoubleLinkedList::longitud(){
  size_t cont = 0;
  Node* current = head;

  while(current != nullptr) 
    cont++;
    current = current->next;

  return cont;
}

void DoubleLinkedList::addHead(int val){
  Node* newNode = new Node{val,head,nullptr};
  if(head != nullptr) head->prev = newNode; 
  head = newNode;

  if(tail == nullptr) tail = newNode;  
}

void DoubleLinkedList::addTail(int val){
  Node* newNode = new Node{val,nullptr,tail};
  if(tail != nullptr) tail->next = newNode;
  tail = newNode;

  if(head == nullptr) head = newNode;
}

void DoubleLinkedList::deleteNode(size_t i){
  if(head == nullptr) return;

  Node* current = head;
  
  while(i > 0 && current->next != nullptr){
    i--;
    current = current->next;
  }

  if(current == head) {
    if(current->next != nullptr) current->next->prev = current->prev;
    else tail = nullptr;
    head = head->next;
  }
  else if (current == tail) {
    current->prev->next = current->next;
    tail = tail->prev;
  }else{
    current->prev->next = current->next;
    current->next->prev = current->prev;
  }

  delete current;
}

Node* DoubleLinkedList::obtain(size_t i){
  if(head == nullptr) return nullptr;

  Node* current = head;

  while(i > 0 && current->next != nullptr){
    i--;
    current = current->next;
  }

  return current;
}

void DoubleLinkedList::reemplazarNodo(size_t i, Node* newNode){
  if(head == nullptr) return;

  Node* current = head;

  while(i > 0 && current->next != nullptr){
    i--;
    current = current->next;
  }

  if(current == head) {
    if(current->next != nullptr) current->next->prev = newNode;
    else tail = newNode;
    head = newNode;
  }
  else if (current == tail) {
    current->prev->next = newNode;
    tail = newNode;
  }else{
    current->prev->next = newNode;
    current->next->prev = newNode;
  }
  newNode->next = current->next;
  newNode->prev = current->prev;
  
  delete current;
}

std::string DoubleLinkedList::toString(){
  std::string res = "[";
  Node* current = head;

  while(current != nullptr){
    res += std::to_string(current->val);
    if(current->next != nullptr) res += ',';
    current = current->next;
  }
  res += ']';

  return res;
};

void DoubleLinkedList::clear(){
  Node* current = head;

  while(current != nullptr){
    Node* nextNode = current->next;
    delete current;
    current = nextNode;
  }
  head = nullptr;
  tail = nullptr;
}

DoubleLinkedList::~DoubleLinkedList(){
  clear();
}