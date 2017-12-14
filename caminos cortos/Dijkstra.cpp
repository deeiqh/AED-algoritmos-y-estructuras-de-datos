#include "Dijkstra.h"

W* dijkstra(Grafo<D, W> grafo, D fuente,int n, W** matriz)
{   
   //aparte de los vectore s  y d, se tendrá un fib heap cuyos nodos tengan
   //los valores de d con su indices, ordenados por el valor
   
   //llenamos s
   int s[n]{0};
   W *d = new W[n];
   for(int i=0 ; i!= n; i++){
      d[i] = MAX;  
   }
   s[fuente] = 1;
   
   //llenamos d, desde la fuente
   for(int i=0 ; i!= n; i++){
      d[i] = matriz[fuente][i];  
   }
   //generamos el fib heap que permitira hallar el seleccionado en O(logn)
   Fib_heap<pair<W,D>> s_heap;
   //colocamos en el heap los datos de d[i] y de i, como un pair.
   for(int i=0 ; i!= n; i++){
         pair<W,D> fib_nodo(d[i],i);
         s_heap.insert(fib_nodo);    
   }
   
   int c = 1; // contador de seleccionados
   pair<W,D> se_pair;// el seleccionado, pero tomado del fib_heap
   D se; // indice de s y de d
   while(c < n){
      se_pair = (s_heap.min)->data.key;
      se = se_pair.second;
      s[se] = 1;
      s_heap.extract_min();
      c++;      
      int m;      
      //si d[i] cambia se hara agrega el nuevo camino corto al heap
      for(int i = 0; i<n; i++){
         if(s[i] == 0){
            m = d[i];
            if(matriz[se][i] != MAX){
               m = min(d[i], d[se]+matriz[se][i]);
            }
            if(m != d[i]){
               d[i] = m;
               s_heap.insert(pair<W,D>(d[i],i));   
            }
         }
      }
   }      
   return d;
}

