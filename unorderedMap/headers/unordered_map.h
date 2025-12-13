#ifndef UNORDERED_MAP
#define UNORDERED_MAP

#include <string>
#include <utility>

using std::string;

//chequera el tema de colisiones, de manera lineal primero.

template<typename value>
class unorderedMap{
  private:
    std::pair<string,value>* buckle;
    size_t size = 0;

  public:
    unorderedMap(const size_t& n){
      this->buckle = new std::pair<string,value>[n];
      this->size = n;
    }

    // para chequeqr si esta ocupado, me fijo si el par es ("",0)
    void add(const string& clave, value val){
      size_t indice = hash(clave);
      buckle[indice].first = clave;
      buckle[indice].second = val;
    }

    void erase(string clave){
      size_t indice = hash(clave);
      buckle[indice].first = "";
      buckle[indice].second = 0;
    }

    void print(){
      for(size_t i = 0; i < size; i++){
       std::cout << buckle[i].first << ' ' << buckle[i].second << '\n';
      }
    }

    ~unorderedMap(){
      delete[] buckle;
    }
  
  private:
    size_t hash(const string& clave){
      size_t res = 0;
      size_t i = 0;
      while(clave[i] != '\n'){
        res += clave[i];
        i++;
      }
      return res % this->size;
    }
};

#endif