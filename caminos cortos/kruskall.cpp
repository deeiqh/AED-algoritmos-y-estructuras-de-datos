#include "kruskall.h"

bool no_hay_ciclo(pair< W, pair<D,D> > arista,
                  vector< set<D> > &conjuntos);
Grafo<D, W> kruskall(const Grafo<D, W> &grafo)
{
   Grafo<D, W> mst;
   int num_aristas = 0;
   
   //el heap contendra las aritas, key tendra pesos y vertices,
   //pero se ordenara por pesos
   Fib_heap<pair< W, pair<D,D> >> heap;
   
   //llenamos el heap con las aristas
   //de paso colocamos los vertices en el mst
   for(auto it = grafo.g.begin(); it != grafo.g.end(); it++){      
      for(auto it2 = (it->aristas).begin(); it2!=(it->aristas).end(); 
      it2++){
         //insertamos el par: (peso) y (vertice origen, vert dest)
         pair<D,D> par_vertices(it->dato,it2->destino->dato); 
         pair< W, pair<D,D> >fib_nodo(it2->peso,par_vertices);         
         heap.insert(fib_nodo);    
         num_aristas++;
      }
      mst.add_vertice(it->dato);
   }
   pair< W, pair<D,D> > arista;
   //para averiguar si hay ciclo se agruparan los vértices
   //que sean parte de un camino en conjuntos, si ambos vertices
   //de la arista pertenecen al conjunto sera un ciclo
   vector< set<D> > conjuntos;
   int c = 0;
   while(c <= num_aristas){
      arista = (heap.min)->data.key;
      heap.extract_min(); 
      if(no_hay_ciclo(arista,conjuntos)){
         mst.add_arista(
         arista.second.first, arista.second.second, arista.first
         );
         c++;
      }cerr << c << " ";
   }
      
   return mst;
}


bool no_hay_ciclo(pair< W, pair<D,D> > arista,
                  vector< set<D> > &conjuntos)
{
   //vertices 1 y 2  
   D v1 = arista.second.first;
   D v2 = arista.second.second; 
   for(auto it = conjuntos.begin(); it != conjuntos.end(); it++){
      if(it->find(v1) != it->end() && it->find(v2) != it->end()){
         return false;
      }
      if(it->find(v1)!= it->end() && it->find(v2)== it->end()){
         it->insert(v2);
         return true;
      }
      if(it->find(v2)!= it->end() && it->find(v1)== it->end()){
         it->insert(v1);
         return true;
      }
   }
   
   set<D> nuevo_conjunto;
   nuevo_conjunto.insert(v1);
   nuevo_conjunto.insert(v2);
   conjuntos.push_back(nuevo_conjunto);
   return true;

}










