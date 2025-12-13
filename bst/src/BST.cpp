#include "BST.h"
using namespace std;

BST::BST() : head(nullptr){};

BST::BST(const BST& other) : head(nullptr){
  head = copiarArbol(head, other.head);
}

Node* BST::copiarArbol(Node* node, Node* other){
  if(other){
    node = new Node(other->val);
    node->right = copiarArbol(node->right, other->right);
    node->left = copiarArbol(node->left, other->left);
  }

  return node;
}

BST::~BST(){
  clear(head);
}

int BST::minimo(){
  Node* node = minimo(head);
  return node->val;
}

Node* BST::minimo(Node* node){
  while(node->left){
    node = node->left;
  }

  return node;
}

size_t BST::altura(){
  return altura(head);
}

size_t BST::altura(Node* node){
  if(!node) return 0;

  return 1 + max(altura(node->right), altura(node->left));
}

int BST::max(int a, int b){
  if(a > b) return a;
  return b;
}

void BST::insertar(int val){
  head = insertar(head, val);
}

Node* BST::insertar(Node* node, int val){
  if(!node){
    Node* newNode = new Node(val);
    return newNode;
  }
  else if(node->val > val){
    node->left = insertar(node->left, val);
  }else if(node->val < val){
    node->right = insertar(node->right, val);
  }

  return node;
}

void BST::borrar(int val){
  head = borrar(head, val);
}

Node* BST::borrar(Node* node, int val){
  if(!node){
    return node;
  }

  if(node->val > val){
    node->left = borrar(node->left, val);
  }else if(node->val < val){
    node->right = borrar(node->right, val);
  }else{
    if(!node->left){
      Node* temp = node->right;
      delete node;
      return temp;
    }
    if(!node->right){
      Node* temp = node->left;
      delete node;
      return temp;
    }
    Node* min = minimo(node->right);
    node->val = min->val;
    node->right = borrar(node->right,min->val); //OJO
  }
  return node;
}

int BST::cardinalidad(){
  return cardinalidad(head);
}

int BST::cardinalidad(Node* node){
  if(!node) return 0;

  return cardinalidad(node->left) + 1 + cardinalidad(node->right);
}

void BST::clear(){
  if(head){
    clear(head->right);
    clear(head->left);
  }
  head = nullptr;
}

void BST::clear(Node* node){
  if(!node) return;

  clear(node->right);
  clear(node->left);
  delete node;
}

string BST::print(){
  const size_t h = altura();
  const size_t a = pow(2,h);
  vector<string> matriz(h*a);
  for(int i{}; i < h; i++){
    for(int j{}; j < a; j++){
      matriz[i * a + j] = " ";
    }
  }

  modificarMatriz(matriz,head,0,0,a,a);

  string res = "";
  for(int i{}; i < h; i++){
    for(int j{}; j < a; j++){
      res += matriz[i * a + j];
    }
    res += '\n';
  }

  return res;
}

size_t BST::pow(int num, int x){
  size_t res = 1;
  for(int i{}; i < x; i++){
    res *= num;
  }
  return res;
}

void BST::modificarMatriz(vector<string>& m, Node* node, int h, int l, int r, int a){
  if(!node) return;

  int mid = (l+r)/2;
  m[h * a + mid] = to_string(node->val);
  modificarMatriz(m,node->right,h+1,mid,r, a);
  modificarMatriz(m,node->left,h+1,l,mid, a);
  return;
}


