#include <iostream>
#include "Grafo.h"
#include "Dijkstra.h"
#include <list>
#include "fib_heap/Fib_heap.h"
#include <vector>
#include <algorithm>
#include "kruskall.h"

using namespace std;
using D = int;
using W = int;
#define MAX 1000

int main()
{   
   Grafo<D, W> grafo;
   grafo.add_vertice(0);
   grafo.add_vertice(1);
   grafo.add_vertice(2);
   grafo.add_vertice(3);
   grafo.add_vertice(4);
   grafo.add_arista(0, 1, 1);
   grafo.add_arista(0, 2, 5);
   grafo.add_arista(0, 3, 3);
   grafo.add_arista(0, 4, 100);
   grafo.add_arista(1, 4, 15);
   grafo.add_arista(1, 2, 8);
   grafo.add_arista(2, 3, 9);
   grafo.add_arista(3, 4, 2);
////////////////////////////////////// DIJKSTRA
   //definimos la matriz
   int n = grafo.g.size();   
   //   W matriz[n][n]{MAX};   
   W** matriz = new W*[n];   
   for(int i=0 ; i!= n; i++){   
      W* fila = new W[n];   
      matriz[i] = fila;
      for(int j=0 ; j!= n; j++){
         matriz[i][j] = MAX;           
      } 
   }
   
   //llenamos la matriz de rutas directas
   for(auto it = grafo.g.begin(); it != grafo.g.end(); it++){      
      for(auto it2 = (it->aristas).begin(); it2!=(it->aristas).end(); 
      it2++){
         matriz[it->dato][it2->destino->dato] = it2->peso; 
      }
   }
   
   D fuente = 0;
   W* distancias;
   distancias = dijkstra(grafo, fuente, n, matriz);
   
   cout << "\nRutas Mínimas:\n";
   cout << "Nodo fuente: " << fuente << '\n';
   cout << "Valor de rutas más corta a:\n";
   for(int i=0; i< n ; i++){
      if(i != fuente)
         cout << i << " = " << distancias[i] << '\n';
   }
////////////////////////////////////// KRUSKALL
   Grafo<D, W> mst_k;
   mst_k = kruskall(grafo);
   //impresion del mst
   cout << "Kruskall: \n";
   /*
   cerr << "MST: \n";
   for(auto it = grafo.g.begin(); it != grafo.g.end(); it++){    
      cout << it->dato << " -> ";
      for(auto it2 = (it->aristas).begin(); it2!=(it->aristas).end(); 
      it2++){
         cout << "("<< it2->peso <<")" << it2->destino->dato << " ";
      }
      cout << '\n';
   }*/

   return 0;
}
