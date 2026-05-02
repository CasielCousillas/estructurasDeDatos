#include "AVL.h"
using namespace std;

AVL::Node::Node() : val(0) , height(1), right(nullptr), left(nullptr){};
AVL::Node::Node(int v) : val(v), height(1) , right(nullptr) , left(nullptr){};
AVL::Node::Node(int v, int h) : val(v), height(h) , right(nullptr) , left(nullptr){};

//----------------------Constructores y Destructor----------------------------//

AVL::AVL() : head(nullptr){};

AVL::AVL(const AVL& other) : head(nullptr){
  this->head = copiar(other.head);
}

AVL::~AVL(){
  clear(head);
}

//----------------------Operators----------------------------//

AVL& AVL::operator=(const AVL& other){
  if(this == &other) return *this;

  clear();

  this->head = copiar(other.head);

  return *this;
}

bool AVL::operator==(const AVL& other){
  return  igualdad(head, other.head);
}

bool AVL::operator!=(const AVL& other){
  return !igualdad(head, other.head);
}

//----------------------Funciones de datos----------------------------//

int AVL::minimo(){
  if(!head) return 0;

  Node* node = minimo(head);
  return node->val;
}

int AVL::maximo(){
  if(!head) return 0;

  Node* node = maximo(head);
  return node->val;
}

int AVL::altura(){
  return (head) ? head->height : -1;
}

int AVL::cardinalidad(){
  return cardinalidad(head);
}

//----------------------Funciones de Control---------------------------//

bool AVL::pertenece(const int& val){
  return pertenece(head, val);
}

bool AVL::esVacio(){
  return !head;
}

bool AVL::esAVL(){
  return esAVL(head, nullptr, nullptr);
}

//----------------------Funciones de Comportamiento----------------------------//

void AVL::insertar(const int& val){
  head = insertar(head, val);
}

void AVL::borrar(const int& val){
  head = borrar(head, val);
}

void AVL::clear(){
  clear(head);
  head = nullptr;
}

//----------------------Funciones de Print----------------------------//

std::string AVL::inOrder(){
  return inOrder(head);
}

std::string AVL::preOrder(){
  return preOrder(head);
}

std::string AVL::postOrder(){
  return postOrder(head);
}

std::string AVL::levelOrder(){
  if(!head) return "";

  queue<Node*> cola;
  cola.push(head);

  string res = "";
  while(!cola.empty()){
    Node* aux = cola.front();
    cola.pop();

    res += to_string(aux->val) + ';';
    if(aux->left) cola.push(aux->left);
    if(aux->right) cola.push(aux->right);
  }

  return res;
}
// No me disgusta pero el tema de los espacios es muy parche
// Si hay elementos con muchos caracters corren los niveles haciendo que sean dificiles de leer
std::string AVL::print(){
  if(!head) return "";
  int h = altura()-1;
  int a = pow(2,h);
  string res = "";

  queue<Node*> q;
  q.push(head);

  while(!q.empty()){
    int lenght = q.size();
    string espacios(a, ' ');
    string espacios2 = "";
    if(a != 1) espacios2 = (a-1, ' ');
    a /= 2;

    for(int i = 0; i < lenght; i++){
      Node* node = q.front();
      q.pop();

      if(node){
        res += espacios + to_string(node->val) + espacios2;
        q.push(node->left);
        q.push(node->right);
      }
      else{
        res += espacios + espacios2;
      }
    }
    res += '\n';
  }

  return res;
}

//----------------------Funciones Auxiliares----------------------------//

AVL::Node* AVL::copiar(Node* other){
  if(!other) return nullptr;

  Node* node = new Node(other->val);
  node->right = copiar(other->right);
  node->left = copiar(other->left);

  return node;
}

bool AVL::igualdad(Node* node, Node* other){
  if(!node && !other) return true;
  if(!node || !other) return false;

  return (node->val == other->val) && igualdad(node->left, other->left) && igualdad(node->right, other->right);
}

//---------------------------//

AVL::Node* AVL::minimo(Node* node){
  if(node->left)
    node = minimo(node->left);

  return node;
}

AVL::Node* AVL::maximo(Node* node){
  if(node->right)
    node = maximo(node->right);

  return node;
}

int AVL::cardinalidad(Node* node){
  if(!node) return 0;

  return cardinalidad(node->left) + 1 + cardinalidad(node->right);
}

//---------------------------//

bool AVL::pertenece(Node* node, const int& val){
  if(!node)
  return false;

  if(node->val > val)
  return pertenece(node->left,val);

  if(node->val < val)
  return pertenece(node->right,val);

  return true;
}

bool AVL::esAVL(Node* node, int* min, int* max){
  if(!node) return true;

  if(min && node->val <= *min ||
     max && node->val >= *max ||
     -1 > getBalance(node) > 1) {
      return false;
    }

  return esAVL(node->left, min, &node->val) && esAVL(node->right, &node->val, max);
}

//---------------------------//

AVL::Node* AVL::insertar(Node* node, const int& val){
  if(!node){
    Node* newNode = new Node(val);
    return newNode;
  }
  else if(node->val > val){
    node->left = insertar(node->left, val);
  }else if(node->val < val){
    node->right = insertar(node->right, val);
  }

  node->height = 1 + max(height(node->left), height(node->right));

  return rebalance(node);
}

AVL::Node* AVL::borrar(Node* node, const int& val){
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
    node->right = borrar(node->right,min->val);
  }

  node->height = 1 + max(height(node->left), height(node->right));

  return rebalance(node);
}

void AVL::clear(Node* node){
  if(!node) return;

  clear(node->right);
  clear(node->left);
  delete node;
}

//---------------------------//

int AVL::height(Node* node){
  if (!node)
    return 0;

  return node->height;
}

int AVL::getBalance(Node* node){
  return height(node->left) - height(node->right);
}

AVL::Node* AVL::rightRotation(Node* x){
  Node* y = x->left;
  x->left = y->right;
  y->right = x;

  x->height = 1 + max(height(x->left), height(x->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return y;
}

AVL::Node* AVL::leftRotation(Node* x){
  Node* y = x->right;
  x->right = y->left;
  y->left = x;

  x->height = 1 + max(height(x->left), height(x->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return y;
}

AVL::Node* AVL::rebalance(Node* node){
  if(getBalance(node) > 1){
    if(getBalance(node->left) < 0)
      node->left = leftRotation(node->left);

    node = rightRotation(node);
  }else if(getBalance(node) < -1){
    if(getBalance(node->right) > 0)
      node->right = rightRotation(node->right);

    node = leftRotation(node);
  }

  return node;
}

//---------------------------//

std::string AVL::inOrder(Node* node){
  if(!node) return "";

  return inOrder(node->left) +  to_string(node->val) + ';' + inOrder(node->right);
}

std::string AVL::preOrder(Node* node){
  if(!node) return "";

  return to_string(node->val) + ';' + preOrder(node->left) + preOrder(node->right);
}

std::string AVL::postOrder(Node* node){
  if(!node) return "";

  return postOrder(node->left) + postOrder(node->right) + to_string(node->val) + ';';
}

//---------------------------//

int AVL::pow(int num, int x){
  size_t res = 1;
  for(int i{}; i < x; i++){
    res *= num;
  }
  return res;
}

int AVL::max(int a, int b){
  if(a > b) return a;
  return b;
}

//---------------------------//