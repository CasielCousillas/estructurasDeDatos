#ifndef BYNARY
#define BYNARY

#include<string>
#include<vector>
using namespace std;

struct Node{
  int val;
  Node* right;
  Node* left;

  public:
    Node() : val(0) , right(nullptr), left(nullptr){};
    Node(int v) : val(v) , right(nullptr) , left(nullptr){};
};

class BST{
  private:
    Node* head;

  public:
    BST();
    BST(const BST& other);
    ~BST();

    int minimo();
    int maximo();
    size_t altura();
    int cardinalidad();
    bool pertenece(int val);
    void insertar(int val);
    void borrar(int val);
    void clear();
    string print();
  
  private:
    Node* insertar(Node* node, int val);
    Node* borrar(Node* node, int val);
    Node* minimo(Node* node);
    Node* maximo(Node* node);
    size_t altura(Node* node);
    int cardinalidad(Node* node);
    Node* copiarArbol(Node* node, Node* other);
    void clear(Node* node);
    int max(int a, int b);
    void modificarMatriz(vector<string>& matriz, Node* node, int h, int l, int r, int a);
    size_t pow(int num, int x);
};

#endif