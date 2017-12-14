#ifndef GRAFO
#define GRAFO

#include <iostream>
#include <list>

using namespace std;

template <class D, class W> 
class Arista;

template <class D, class W> 
class Vertice
{
public:
	D dato;
	list<Arista<D,W>>	aristas;
public:
   Vertice(){};
   Vertice(D d) {dato = d;};
   bool operator==(const Vertice &v){
      return dato == v.dato;
   }
};

template <class D, class W>
class Arista
{
public:
   W peso;
   Vertice<D, W>* destino;
public:
   Arista(W w){ peso = w; destino = NULL;};   
};

template <class D, class W>
class Grafo
{
public:
   list<Vertice<D,W>> g;
public:
   Grafo(){};
   void add_vertice(D v1){
      g.push_back(Vertice<D,W>(v1));
   };
   void add_arista(D v1, D v2, W ar){      
      auto p = find(g.begin(), g.end(), Vertice<D,W>(v1));
      auto q = find(g.begin(), g.end(), Vertice<D,W>(v2));
      if(p!=g.end() && q!=g.end()){
         auto arista = Arista<D,W>(ar);
         arista.destino = &(*q);
         p -> aristas.push_back(arista);
      }
   };   
};

#endif










