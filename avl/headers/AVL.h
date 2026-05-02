#ifndef BYNARYAVL
#define BYNARYAVL

#include<string>
#include<queue>

class AVL{
private:
    struct Node{
        int val;
        int height;
        Node* right;
        Node* left;
    
        Node();
        Node(int v);
        Node(int v, int h);
    };

public:
    Node* head;

public:
    AVL();
    AVL(const AVL& other);
    ~AVL();

    AVL& operator=(const AVL& other);
    bool operator==(const AVL& other);
    bool operator!=(const AVL& other);

    int minimo();
    int maximo();
    int altura(); 
    int cardinalidad();

    bool pertenece(const int& val);
    bool esVacio();
    bool esAVL();

    void insertar(const int& val);
    void borrar(const int& val);
    void clear();

    std::string inOrder();
    std::string preOrder();
    std::string postOrder();
    std::string levelOrder();
    std::string print();
    
    private:
    bool igualdad(Node* node, Node* other);
    bool pertenece(Node* node, const int& val);
    bool esAVL(Node* node, int* min, int* max);
    Node* copiar(Node* other);

    int cardinalidad(Node* node);
    Node* minimo(Node* node);
    Node* maximo(Node* node);
    
    void clear(Node* node);

    Node* insertar(Node* node, const int& val);
    Node* borrar(Node* node, const int& val);

    int height(Node* node);
    int getBalance(Node* node);
    Node* rightRotation(Node* node);
    Node* leftRotation(Node* node);
    Node* rebalance(Node* node);
    
    std::string inOrder(Node* node);
    std::string preOrder(Node* node);
    std::string postOrder(Node* node);
    
    int pow(int num, int x);
    int max(int a, int b);
};

#endif