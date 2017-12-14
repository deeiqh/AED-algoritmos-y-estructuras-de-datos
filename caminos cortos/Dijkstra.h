#ifndef DIJKSTRA
#define DIJKSTRA

#include <iostream>
#include "Grafo.h"
#include <list>
#include "fib_heap/Fib_heap.h"
#include <vector>
#include <climits>
#include <algorithm>

using D = int;
using W = int;
#define MAX 1000

W* dijkstra(Grafo<D, W> grafo, D fuente,int n, W** matriz);

#endif
