#include <iostream>
using namespace std;

struct Node{
  int val;
  Node* next;
};

class LinkedList{
private:
  Node* head;  // Puntero al primer nodo de la lista
  Node* tail;  // Puntero al último nodo de la lista

public:
  Node* getHead() const {return head;}
  Node* getTail() const {return tail;}

  // Constructor por defecto: inicializa lista vacía (head y tail nulos)
  LinkedList() : head(nullptr), tail(nullptr) {}

  // Constructor de copia (deep copy): crea una copia profunda de otra lista
  LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr){
    Node* current = other.head;
    while(current != nullptr){
      insertAtTail(current->val);  // Copiar valor nodo por nodo al final
      current = current->next;
    }
  }

  // Operador de asignación (deep copy)
  LinkedList& operator=(const LinkedList& other) {
    if (this == &other) return *this;  // Evitar autoasignación

    clearList();  // Liberar memoria actual para evitar fugas

    Node* current = other.head;
    while (current != nullptr) {
      insertAtTail(current->val);  // Copiar nodo por nodo
      current = current->next;
    }

    return *this;  // Devuelve referencia al objeto actual para encadenar asignaciones
  }

  // Inserta un nuevo nodo al inicio de la lista
  void insertAtHead(const int& value){
    Node* newNode = new Node{value,head};  // Nuevo nodo apunta al antiguo head
    head = newNode;                        // Actualiza head al nuevo nodo

    if(tail == nullptr) tail = newNode;  // Si lista estaba vacía, tail apunta también al nuevo nodo
  }

  // Inserta un nuevo nodo al final de la lista
  void insertAtTail(const int& value){
    Node* newNode = new Node{value,nullptr};  // Nuevo nodo apunta a nullptr porque será el último
    
    if(head == nullptr){
      head = newNode;  // Si la lista estaba vacía, head apunta al nuevo nodo
    }else{
      tail->next = newNode;  // El antiguo tail apunta al nuevo nodo
    }
    tail = newNode;  // Actualiza tail al nuevo nodo
  }  

  // Elimina el nodo al inicio de la lista
  void deleteHead(){
    if(head == nullptr) return;  // Si lista vacía, no hace nada

    Node* nextNode = head->next;  // Guarda el siguiente nodo

    if(nextNode == nullptr){
      tail = nullptr;  // Si solo había un nodo, tail queda nulo también
    }
    delete head;  // Libera memoria del nodo antiguo
    head = nextNode;  // Actualiza head
  }

  // Elimina el nodo al final de la lista
  void deleteTail() {
    if (head == nullptr) return; // Lista vacía, nada que hacer

    // Caso especial: solo un nodo
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
      return;
    }

    // Caso general: más de un nodo
    Node* current = head;
    while (current->next != tail) { // Buscar el penúltimo nodo
      current = current->next;
    }

    delete tail;          // Libera el último nodo
    tail = current;       // Actualiza tail al penúltimo nodo
    tail->next = nullptr; // El nuevo tail no apunta a nada
  }

  // Elimina el primer nodo que tenga el valor dado
  void deleteNodeByValue(const int& value){
    if (head == nullptr) return; // Lista vacía, no hace nada

    if (head == tail) {           // Lista con un solo nodo
      if(head->val != value) return;  // Valor no coincide, nada que borrar

      delete head;
      head = nullptr;
      tail = nullptr;
      return;
    }

    // Caso donde el valor está en el head
    if (head->val == value) {
      Node* temp = head;
      head = head->next;
      delete temp;
      if (head == nullptr) tail = nullptr; // Si quedó vacía actualiza tail
      return;
    }

    // Caso general: recorrer la lista buscando el valor
    Node* current = head;

    while(current->next != nullptr){
      if(current->next->val == value){
        Node* temp = current->next; // Nodo a eliminar (para llentoiberar memoria)
        current->next = temp->next; // Saltear el nodo eliminado

        if(temp == tail){
          tail = current;  // Actualizar tail si borramos el último nodo
        }
        delete temp;  // Liberar memoria
        return;
      }
      current = current->next;
    }
  }

  // Busca un valor en la lista (búsqueda lineal)
  bool linearSearch(const int& value) const{
    Node* current = head;
    while(current != nullptr){
      if(current->val == value) return true;
      current = current->next;
    }
    return false;
  }

  // Devuelve la cantidad de nodos en la lista
  int size() const{
    int cont = 0;
    Node* current = head;
    while(current != nullptr){
      current = current->next;
      cont++;
    }
    return cont;
  }

  void reverse() {
    tail = head; // El antiguo head será el nuevo tail

    Node* current = head; // Puntero que recorre la lista nodo por nodo
    Node* prev = nullptr; // Puntero al nodo anterior (inicia en nullptr porque el nuevo tail apuntará a nullptr)
    Node* nextNode = nullptr; // Puntero temporal para guardar el siguiente nodo antes de romper el enlace

    while (current != nullptr) {
      nextNode = current->next; // Guardamos el siguiente nodo antes de modificar el puntero

      current->next = prev; // Invertimos el enlace: ahora apunta al nodo anterior

      prev = current; // Avanzamos prev para que apunte al nodo actual
      current = nextNode; // Avanzamos current para seguir recorriendo la lista
    }

    head = prev; // Al final, prev apunta al nuevo head de la lista
  }

  Node* middleFirstHalf(){
    if(!head) return nullptr; // Si la lista está vacía, no hay nodo medio

    Node* slow = head;        // Puntero lento, avanzará de 1 en 1
    Node* fast = head->next;  // Puntero rápido, empieza adelantado para favorecer el primer nodo en listas pares

    while (fast != nullptr && fast->next != nullptr){ // Mientras fast y el siguiente no sean nulos
      fast = fast->next->next; // Avanza dos pasos con el puntero rápido
      slow = slow->next;       // Avanza un paso con el puntero lento
    }
    return slow; // Devuelve el nodo medio (primero de los dos si la lista es par)
  }

  Node* middleSecondHalf(){
    Node* slow = head;        // Puntero lento, avanza de 1 en 1
    Node* fast = head;        // Puntero rápido, empieza desde el mismo nodo que slow

    while (fast != nullptr && fast->next != nullptr){ // Mientras no se pase del final
      fast = fast->next->next; // Avanza dos pasos con el puntero rápido
      slow = slow->next;       // Avanza un paso con el puntero lento
    }
    return slow; // Devuelve el nodo medio (segundo de los dos si la lista es par)
  }

  bool isCicle(){
    Node* slow = head;  // Puntero lento que avanza de 1 en 1
    Node* fast = head;  // Puntero rápido que avanza de 2 en 2

    while(fast && fast->next){ // Mientras fast no llegue al final de la lista
      slow = slow->next;     // Avanza slow un paso
      fast = fast->next->next; // Avanza fast dos pasos

      if(fast == slow) return true; // Si se encuentran, hay un ciclo
    }
    
    return false; // Si salimos del while, no hay ciclo
  }

  Node* nodoDesdeElFinal(const int k){
    Node* slow = head;
    Node* fast = head;

    for (size_t i = 0; i < k && fast != nullptr; i++)
      fast = fast->next;

    while(fast != nullptr){
      slow = slow->next;
      fast = fast->next;
    }

    return slow;
  }

  // Imprime la lista en formato "val1 -> val2 -> ... -> nullptr"
  void printList() const{
    Node* current = head;
    while(current != nullptr){
      cout << current->val << " -> ";
      current = current->next;
    }
    cout << "nullptr" << endl;
  }

  // Elimina todos los nodos de la lista liberando memoria
  void clearList(){
    Node* current = head;
    while(current != nullptr){
      Node* nextNode = current->next;
      delete current;
      current = nextNode;        
    }
    head = nullptr;  // Después de borrar todo, head y tail apuntan a nullptr
    tail = nullptr;
  }

  // Destructor: libera la memoria al destruir la lista
  ~LinkedList(){
    clearList();
  }
};